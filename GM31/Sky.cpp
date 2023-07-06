#include "Sky.h"
#include <random>
#include <iostream>
#include"BindableBase.h"
#include"Camera.h"
#include"manager.h"

void Sky::Init()
{
	m_model = std::make_unique<Model>();
	m_model->Load("asset\\model\\sky.obj");

	auto pvs = VertexShader::Resolve("unlitTextureVS.cso");
	auto fsize = pvs->Getfsize();
	auto buffer = pvs->GetBuffer();
	AddBind(std::move(pvs));
	AddBind(std::make_shared<InputLayout>(layout, "layout",buffer, fsize));

	AddBind(PixelShader::Resolve("unlitTexturePS.cso"));

	m_Scale = D3DXVECTOR3(100.0f, 100.0f, 100.0f);
	m_camera = Manager::GetScene()->GetGameObj<Camera>();

}

void Sky::Uninit()
{
}

void Sky::Update()
{
	m_Position = m_camera->GetPos();

}



void Sky::Draw()
{

	// マトリクス設定

	D3DXMatrixScaling(&m_scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&m_rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&m_trans, m_Position.x, m_Position.y, m_Position.z);
	m_world = m_scale * m_rot * m_trans;
	Renderer::SetWorldMatrix(&m_world);

	BindAll();

	m_model->Draw();
}
