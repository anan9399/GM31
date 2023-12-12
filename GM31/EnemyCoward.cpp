#include "EnemyCoward.h"
#include"GuardRunBT.h"

std::unique_ptr<Model> EnemyCoward::m_model;

void EnemyCoward::Load()
{
	m_model = std::make_unique<Model>();
	m_model->Load("asset\\model\\torus.obj");
}

void EnemyCoward::UnLoad()
{
	m_model->Unload();
}


void EnemyCoward::Init()
{


	Enemy::Init();
}

void EnemyCoward::Update()
{
	if (m_guardBT != nullptr) {
		m_guardBT->Update();
	}
	else {
		m_guardBT = new BehaviorTree::GuardRunBT(this, m_waypoints);
	}
}

void EnemyCoward::Draw()
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
