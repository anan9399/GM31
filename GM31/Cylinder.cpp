#include "Cylinder.h"
#include"manager.h"
#include"Scene.h"
#include"BindableBase.h"
#include"Shadow.h"

void Cylinder::Init()
{
	m_model = std::make_unique<Model>();
	m_model->Load("asset\\model\\cylinder\\cylinder.obj");


	auto pvs = VertexShader::Resolve("vertexLightingVS.cso");
	auto fsize = pvs->Getfsize();
	auto buffer = pvs->GetBuffer();
	AddBind(std::move(pvs));
	AddBind(std::make_shared<InputLayout>(layout,"layout", buffer, fsize));
	AddBind(PixelShader::Resolve("vertexLightingPS.cso"));

	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_shadow = AddComponent<Shadow>();
	m_shadow->SetScale(D3DXVECTOR3(2.0f, 1.0f, 2.0f));
	//material.Diffuse = { 0.6f,0.6f,0.8f,1.0f };
}

void Cylinder::Uninit()
{
	m_model->Unload();
	GameObject::Uninit();
}

void Cylinder::Update()
{
	m_shadow->SetPos(D3DXVECTOR3(m_Position.x, 0.001f, m_Position.z));
	GameObject::Update();
}

void Cylinder::Draw()
{

	// マトリクス設定

	D3DXMatrixScaling(&m_scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&m_rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&m_trans, m_Position.x, m_Position.y, m_Position.z);
	m_world = m_scale * m_rot * m_trans;
	Renderer::SetWorldMatrix(&m_world);


	for (auto b : m_binds) {
		b->Bind();
	}


	m_model->Draw();
	GameObject::Draw();
}
