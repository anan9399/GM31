#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include"Scene.h"
#include"Player.h"
#include<DirectXMath.h>


void Camera::Init()
{

	m_Position = D3DXVECTOR3(0.0f, 5.0f, -10.0f);
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}


void Camera::Uninit()
{

}


void Camera::Update()
{
	//std::shared_ptr<Scene> scene = Manager::GetScene();
	Player* player = Manager::GetScene()->GetGameObj<Player>();

	
	//m_Target = player->GetPos();
	//m_Position = m_Target + D3DXVECTOR3(0.0f, 5.0f, -10.0f);
	

	m_Target = player->GetPos() 
			+ player->GetRight() * 0.5f 
			+ D3DXVECTOR3(0.0f, 3.0f, 0.0f);
	m_Position = m_Target 
			- player->GetForward() * 6.0f
			+ D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	
	//m_Position = player->GetPos() + D3DXVECTOR3(0.0f, 1.0f, -0.5f);
	//m_Target = m_Position + player->GetForward();

}


void Camera::Draw()
{

	//ビューマトリクス設定
	//D3DXMATRIX viewMatrix;
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_ViewMatrix, &m_Position, &m_Target, &up);
	//DirectX::XMMATRIX
	//DirectX::XMVECTOR pos;
	/*DirectX::XMMatrixLookAtLH(pos, DirectX::XMVectorZero(),
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));*/

	Renderer::SetViewMatrix(&m_ViewMatrix);

	//プロジェクションマトリクス設定
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&projectionMatrix);


	//Renderer::SetCameraPosition(m_Position);

}
