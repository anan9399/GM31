#include "Player.h"
#include "Keyboard.h"
#include"manager.h"
#include"Scene.h"
#include"Box.h"
#include"Cylinder.h"
#include"audio.h"
#include"SuperBullet.h"
#include"Billboard.h"
#include"BindableBase.h"
#include"Shadow.h"
#include"Explosion.h"


void Player::Init()
{
	/*m_model = std::make_unique<Model>();
	m_model->Load("asset\\model\\torus.obj");	*/

	m_model = std::make_unique<AnimationModel>();
	m_model->Load("asset\\model\\Bot.fbx");	
	m_model->LoadAnimation("asset\\model\\Bot_Idle.fbx","Idle");
	m_model->LoadAnimation("asset\\model\\Bot_Run.fbx","Run");
	m_model->LoadAnimation("asset\\model\\Excited.fbx","Excited");
	animationName = "Run";

	m_Scale = { 0.015f,0.015f,0.015f };

	auto pvs = VertexShader::Resolve("AnimationVS.cso");
	auto fsize = pvs->Getfsize();
	auto buffer = pvs->GetBuffer();
	AddBind(std::move(pvs));
	AddBind(std::make_shared<InputLayout>(layout, "layout", buffer, fsize));
	AddBind(PixelShader::Resolve("pixelLightingPS.cso"));

	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_speed = 0.1f;
	//material.Diffuse = { 0.6f,0.6f,0.8f,1.0f };
	m_shotSE = AddComponent<Audio>();
	m_shotSE->Load("asset\\audio\\solid.wav");
	m_shaow = AddComponent<Shadow>();
	playerHP = 1;
}

void Player::Uninit()
{

	m_model->Unload();
	m_model.release();
	
	GameObject::Uninit();
}

void Player::Update()
{
	if (m_dead) {
		SetExplosion();
		SetDestory();
		return;
	}

	auto scene = Manager::GetScene();
	D3DXVECTOR3 oldPos = m_Position;

	//animationName = "Idle";
	if (Keyboard::GetKeyPress('W')) {
		animationName = "Run";
		m_Position += GetForward() * m_speed;
	}
	if (Keyboard::GetKeyPress('S')) {
		m_Position -= GetForward() * m_speed;
	}
	if (Keyboard::GetKeyPress('A')) {
		m_Position -= GetRight() * m_speed;
	}
	if (Keyboard::GetKeyPress('D')) {
		m_Position += GetRight() * m_speed;
	}	

	if (Keyboard::GetKeyPress('E')) {
		m_Rotation.y += m_speed;
	}	
	if (Keyboard::GetKeyPress('Q')) {
		m_Rotation.y -= m_speed;
	}

	//std::shared_ptr<Scene> scene = Manager::GetScene();
	if (Keyboard::GetKeyTrigger('F')) {	
		if (superBullet) {
			auto bullet = scene->AddGameObj<SuperBullet>(1);
			bullet->SetPos(m_Position);
			bullet->SetVelocity(GetForward() * 0.1f);
		}
		else {
			auto bullet = scene->AddGameObj<Bullet>(1);
			bullet->SetPos(m_Position);
			bullet->SetVelocity(GetForward() * 0.1f);
		}
		
		m_shotSE->Play(false);
	}

	if (isGround && Keyboard::GetKeyTrigger(VK_SPACE)) {
		m_velocity.y = 0.3f;
		isGround = false;
	}


	m_velocity.y -= 0.01f;
	m_Position += m_velocity;

	float groundHeight = 1.0f;
	
	// Cyliner
	auto cylinerColiders = scene->GetGameObjs<Cylinder>();
	for (auto& c : cylinerColiders) {
		D3DXVECTOR3 coliderPos = c->GetPos();
		D3DXVECTOR3 coliderScale = c->GetScale();

		D3DXVECTOR3 dir = m_Position - coliderPos;
		dir.y = 0.0f;
		float length = D3DXVec3Length(&dir);

		if (length < coliderScale.x + 1.0f
			&& m_Position.y < coliderPos.y + coliderScale.y
			&& m_Position.y >coliderPos.y - coliderScale.y
			) {
			if (m_Position.y < coliderPos.y + coliderScale.y - 0.5f) {
				m_Position.x = oldPos.x;
				m_Position.z = oldPos.z;
			}
			else {
				groundHeight = coliderPos.y + coliderScale.y;
			}
			break;
		}
	}

	// Box
	auto boxColiders = scene->GetGameObjs<Box>();
	for (auto& c : boxColiders) {
		D3DXVECTOR3 coliderPos = c->GetPos();
		D3DXVECTOR3 coliderScale = c->GetScale();

		if(	m_Position.x >coliderPos.x - coliderScale.x - 0.5f - 0.8f
			&& m_Position.x < coliderPos.x + coliderScale.x + 0.5f + 0.8f
			&& m_Position.z >coliderPos.z - coliderScale.z - 0.5f - 0.8f
			&& m_Position.z < coliderPos.z + coliderScale.z + 0.5f + 0.8f
			&& m_Position.y > coliderPos.y - coliderScale.y + 0.5f + 0.8f
			)
		{ 
			if (m_Position.y < coliderPos.y + coliderScale.y * 2.0f - 0.5f) 
			{
				m_Position.x = oldPos.x;
				m_Position.z = oldPos.z;
			}
			else 
			{
				groundHeight = coliderPos.y + coliderScale.y * 2.0f;
			}
			break;
		}

	}

	// Item
	auto item = scene->GetGameObjs<Billboard>();
	for (auto& c : item) {
		D3DXVECTOR3 itemPos = c->GetPos();
		D3DXVECTOR3 itemScale = c->GetScale();

		D3DXVECTOR3 dir = m_Position - itemPos;
		dir.y = 0.0f;
		float length = D3DXVec3Length(&dir);

		if (length < itemScale.x + 1.0f
			&& m_Position.y < itemPos.y + itemScale.y
			&& m_Position.y >itemPos.y - itemScale.y
			) {
			superBullet = true;
			c->SetDestory();
			break;
		}
	}

	if (m_Position.y <= groundHeight && m_velocity.y < 0.0f) {
		m_Position.y = groundHeight;
		m_velocity.y = 0.0f;
		isGround = true;
	}
	D3DXVECTOR3 shadowPos = { m_Position.x,groundHeight+0.001f,m_Position.z };
	m_shaow->SetPos(shadowPos);




	GameObject::Update();
}

void Player::Draw()
{

	// マトリクス設定
	
	D3DXMatrixScaling(&m_scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&m_rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&m_trans, m_Position.x, m_Position.y, m_Position.z);
	m_world = m_scale * m_rot * m_trans;
	m_matrix = m_world;
	Renderer::SetWorldMatrix(&m_world);

	BindAll();

	m_model->Update(animationName.c_str(), m_time);
	m_time++;

	m_model->Draw();
	GameObject::Draw();
}

void Player::Hurt()
{
	m_dead = true;
}

void Player::SetExplosion()
{
	auto explosion = Manager::GetScene()->AddGameObj<Explosion>(1);
	explosion->SetPos(m_Position);
}
