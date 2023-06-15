#include "Player.h"
#include "Keyboard.h"
#include"manager.h"
#include"Scene.h"

void Player::Init()
{
	m_Model = std::make_unique<Model>();
	m_Model->Load("asset\\model\\torus.obj");	

	Renderer::CreatePixelShader(m_pPixelShader.ReleaseAndGetAddressOf(), "vertexLightingPS.cso");
	Renderer::CreateVertexShader(m_pVertexShader.ReleaseAndGetAddressOf(), m_pInputLayout.ReleaseAndGetAddressOf(), "vertexLightingVS.cso");

	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_speed = 0.1f;
	//material.Diffuse = { 0.6f,0.6f,0.8f,1.0f };
}

void Player::Uninit()
{
	m_Model->Unload();
}

void Player::Update()
{
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
		auto bullet = Manager::GetScene()->AddGameObj<Bullet>(1);
		bullet->SetPos(m_Position);
		bullet->SetVelocity(GetForward()*0.1f);
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

	m_Model->Draw();
}
