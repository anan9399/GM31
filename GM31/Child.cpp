#include "Child.h"
#include <random>
#include <iostream>
#include"BindableBase.h"
#include "manager.h"
#include<DirectXMath.h>
#include"model.h"
#include"Player.h"
std::unique_ptr<Model> Child::m_model;

void Child::Load()
{
	m_model = std::make_unique<Model>();
	m_model->Load("asset\\model\\turtle.obj");
}

void Child::UnLoad()
{
	m_model->Unload();
}

void Child::Init()
{


	auto pvs = VertexShader::Resolve("vertexLightingVS.cso");
	auto fsize = pvs->Getfsize();
	auto buffer = pvs->GetBuffer();
	AddBind(std::move(pvs));
	AddBind(std::make_shared<InputLayout>(layout, "layout", buffer, fsize));
	AddBind(PixelShader::Resolve("vertexLightingPS.cso"));

	//speed = dx(rngE);
	//m_Position = D3DXVECTOR3(10.0f, 0.0f, 10.0f);



}

void Child::Uninit()
{
	GameObject::Uninit();
}

void Child::Update()
{
	
}

void Child::Draw()
{
	// マトリクス設定

	D3DXMatrixScaling(&m_scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&m_rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&m_trans, m_Position.x, m_Position.y, m_Position.z);
	m_world = m_scale * m_rot * m_trans * m_parent->GetMatrix();
	Renderer::SetWorldMatrix(&m_world);

	BindAll();

	m_model->Draw();
}


