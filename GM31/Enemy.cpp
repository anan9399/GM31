#include "Enemy.h"
#include <random>
#include <iostream>
#include"BindableBase.h"
#include "manager.h"
#include<DirectXMath.h>

#include"GuardBT.h"

std::mt19937 rngE({ std::random_device{}() });
std::uniform_real_distribution<float> dx(0.0f, 0.3f);

std::unique_ptr<Model> Enemy::m_model;

void Enemy::Load()
{
	m_model = std::make_unique<Model>();
	m_model->Load("asset\\model\\torus.obj");
}

void Enemy::UnLoad()
{
	m_model->Unload();
}

void Enemy::Init()
{
	guardBT = new BehaviorTree::GuardBT(&m_Position);

	auto pvs = VertexShader::Resolve("vertexLightingVS.cso");
	auto fsize = pvs->Getfsize();
	auto buffer = pvs->GetBuffer();
	AddBind(std::move(pvs));
	AddBind(std::make_shared<InputLayout>(layout, "layout", buffer, fsize));
	AddBind(PixelShader::Resolve("vertexLightingPS.cso"));

	speed = dx(rngE);
	//m_Position = D3DXVECTOR3(0.0f, 1.0f, 1.0f);
	
}

void Enemy::Uninit()
{
	GameObject::Uninit();
}

void Enemy::Update()
{
	guardBT->Update();
	//m_Position = guardBT->GetPos();
	//auto player = Manager::GetScene()->GetGameObj<Player>();
	//D3DXVECTOR3 target = player->GetPos() - GetPos();
	//D3DXVec3Normalize(&target, &target);

	//m_Position += target * 0.03f;
	//D3DXVECTOR3 nowForward;
	//D3DXVec3Normalize(&nowForward, &GetForward());
	
	//auto rotateQuaternion = DirectX::XMVector3AngleBetweenVectors(nowForward, target);

	/*if (m_nowRange >= m_range) {
		moveRight = false;
	}
	if (m_nowRange <= -m_range) {
		moveRight = true;
	}

	m_nowRange += moveRight ? speed : -speed;
	m_Position += moveRight ? D3DXVECTOR3(speed, 0.0f, 0.0f) : D3DXVECTOR3(-speed, 0.0f, 0.0f);*/

}

void Enemy::Draw()
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


