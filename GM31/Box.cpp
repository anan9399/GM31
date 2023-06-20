#include "Box.h"
#include"manager.h"
#include"Scene.h"

void Box::Init()
{
	m_model = std::make_unique<Model>();
	m_model->Load("asset\\model\\box\\box.obj");

	Renderer::CreatePixelShader(m_pPixelShader.ReleaseAndGetAddressOf(), "vertexLightingPS.cso");
	Renderer::CreateVertexShader(m_pVertexShader.ReleaseAndGetAddressOf(), m_pInputLayout.ReleaseAndGetAddressOf(), "vertexLightingVS.cso");

	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//material.Diffuse = { 0.6f,0.6f,0.8f,1.0f };
}

void Box::Uninit()
{
	m_model->Unload();
}

void Box::Update()
{

}

void Box::Draw()
{

	// マトリクス設定

	D3DXMatrixScaling(&m_scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&m_rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&m_trans, m_Position.x, m_Position.y, m_Position.z);
	m_world = m_scale * m_rot * m_trans;
	Renderer::SetWorldMatrix(&m_world);


	Renderer::GetDeviceContext()->VSSetShader(m_pVertexShader.Get(), nullptr, 0u);
	Renderer::GetDeviceContext()->IASetInputLayout(m_pInputLayout.Get());
	Renderer::GetDeviceContext()->PSSetShader(m_pPixelShader.Get(), nullptr, 0u);

	m_model->Draw();
}
