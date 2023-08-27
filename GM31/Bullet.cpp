#include "Bullet.h"
#include"manager.h"
#include"Scene.h"
#include"renderer.h"
#include"Enemy.h"
#include"Explosion.h"
#include"Cylinder.h"
#include"Box.h"
#include"Score.h"
#include"BindableBase.h"

std::unique_ptr<Model> Bullet::m_model;

void Bullet::Load()
{
	m_model = std::make_unique<Model>();
	m_model->Load("asset\\model\\sphere.obj");
}

void Bullet::UnLoad()
{
	m_model->Unload();
}

void Bullet::Init()
{
	m_Scale = D3DXVECTOR3(0.3f, 0.3f, 0.3f);
	m_velocity = D3DXVECTOR3(0.0f, 0.0f, 0.1f);

	auto pvs = VertexShader::Resolve("vertexLightingVS.cso");
	auto fsize = pvs->Getfsize();
	auto buffer = pvs->GetBuffer();
	AddBind(std::move(pvs));
	AddBind(std::make_shared<InputLayout>(layout, "layout", buffer, fsize));
	AddBind(PixelShader::Resolve("vertexLightingPS.cso"));

	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_life = 0.0f;
}

void Bullet::Uninit()
{
	
}

void Bullet::Update()
{
	m_Position += m_velocity;
	m_life += 0.1f;
	if (m_life > 10.0f) {
		SetExplosion();
		//消す予約
		SetDestory();

	}

	auto enemys = Manager::GetScene()->GetGameObjs<Enemy>();
	for (auto& e : enemys) {
		D3DXVECTOR3 enemyPos = e->GetPos();
		D3DXVECTOR3 direction = m_Position - enemyPos;
		if (D3DXVec3Length(&direction)<1.0f) {
			SetExplosion();
			SetDestory();
			e->SetDestory();
			Manager::GetScene()->GetGameObj<Score>()->AddCount(5);
			return;
		}
	}


	// Cyliner
	auto cylinerColiders = Manager::GetScene()->GetGameObjs<Cylinder>();
	for (auto& c : cylinerColiders) {
		D3DXVECTOR3 coliderPos = c->GetPos();
		D3DXVECTOR3 coliderScale = c->GetScale();
		D3DXVECTOR3 dir = m_Position - coliderPos;
		dir.y = 0.0f;
		float length = D3DXVec3Length(&dir);
		if (length < coliderScale.x + 1.0f
			&& m_Position.y < coliderPos.y + coliderScale.y
			&& m_Position.y >coliderPos.y - coliderScale.y) {
			SetExplosion();
			SetDestory();
			return;
		}
	}


	// Box
	auto boxColiders = Manager::GetScene()->GetGameObjs<Box>();
	for (auto& c : boxColiders) {
		D3DXVECTOR3 coliderPos = c->GetPos();
		D3DXVECTOR3 coliderScale = c->GetScale();

		if (m_Position.x > coliderPos.x - coliderScale.x 
			&& m_Position.x < coliderPos.x + coliderScale.x

			&& m_Position.y >coliderPos.y - coliderScale.y 
			&& m_Position.y < coliderPos.y + coliderScale.y

			&& m_Position.z >coliderPos.z - coliderScale.z 
			&& m_Position.z < coliderPos.z + coliderScale.z  )
		{
			SetExplosion();
			SetDestory();
			return;
		}
	}
}



void Bullet::Draw()
{

	// マトリクス設定

	D3DXMatrixScaling(&m_mScale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&m_mRot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&m_mTrans, m_Position.x, m_Position.y, m_Position.z);
	m_world = m_mScale * m_mRot * m_mTrans;
	Renderer::SetWorldMatrix(&m_world);

	BindAll();

	m_model->Draw();

}

void Bullet::SetExplosion()
{
	auto explosion = Manager::GetScene()->AddGameObj<Explosion>(1);
	explosion->SetPos(m_Position);
	//bullet->SetVelocity(GetForward() * 0.1f);
}
