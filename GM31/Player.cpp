#include "Player.h"
#include "Keyboard.h"
#include"manager.h"
#include"Scene.h"
#include"Cylinder.h"
void Player::Init()
{
	m_model = std::make_unique<Model>();
	m_model->Load("asset\\model\\torus.obj");	

	Renderer::CreatePixelShader(m_pPixelShader.ReleaseAndGetAddressOf(), "vertexLightingPS.cso");
	Renderer::CreateVertexShader(m_pVertexShader.ReleaseAndGetAddressOf(), m_pInputLayout.ReleaseAndGetAddressOf(), "vertexLightingVS.cso");

	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_speed = 0.1f;
	//material.Diffuse = { 0.6f,0.6f,0.8f,1.0f };
}

void Player::Uninit()
{
	m_model->Unload();
}

void Player::Update()
{
	auto scene = Manager::GetScene();
	D3DXVECTOR3 oldPos = m_Position;

	if (Keyboard::GetKeyPress('W')) {
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
		auto bullet = scene->AddGameObj<Bullet>(1);
		bullet->SetPos(m_Position);
		bullet->SetVelocity(GetForward()*0.1f);
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
			&& m_Position.z < coliderPos.z + coliderScale.z + 0.5f + 0.8f)
		{ 
			if (m_Position.y < coliderPos.y + coliderScale.y * 2.0f - 0.5f) 
			{
				m_Position.x = oldPos.x;
				m_Position.z = oldPos.z;
			}
			else 
			{
				groundHeight = coliderPos.y + coliderScale.y * 2.0;
			}
			break;
		}

	}

	if (m_Position.y <= groundHeight && m_velocity.y < 0.0f) {
		m_Position.y = groundHeight;
		m_velocity.y = 0.0f;
		isGround = true;
	}
}

void Player::Draw()
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
