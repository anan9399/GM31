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
	//
	if (player != nullptr) {
		m_Target = player->GetPos()
			+ player->GetForward() * 0.5f
			+ D3DXVECTOR3(0.0f, 1.5f, 0.0f);
		m_Position = m_Target
			- player->GetForward() * 6.0f
			+ D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}
	
	/*m_Position = player->GetPos() + D3DXVECTOR3(0.0f, 1.0f, -0.5f);
	m_Target = m_Position + player->GetForward();*/


	//Shake
	m_ShakeOffset = sinf(m_ShakeTime * 1.5f) * m_ShakeAmplitude;
	m_ShakeTime++;
	m_ShakeAmplitude *= 0.6f;
}


void Camera::Draw()
{

	//ビューマトリクス設定
	//D3DXMATRIX viewMatrix;
	D3DXVECTOR3 position = m_Position + D3DXVECTOR3(0.0f, m_ShakeOffset, 0.0f);
	D3DXVECTOR3 target = m_Target + D3DXVECTOR3(0.0f, m_ShakeOffset, 0.0f);

	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_ViewMatrix, &position, &target, &up);


	//DirectX::XMMATRIX
	//DirectX::XMVECTOR pos;
	/*DirectX::XMMatrixLookAtLH(pos, DirectX::XMVectorZero(),
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));*/

	Renderer::SetViewMatrix(&m_ViewMatrix);

	//プロジェクションマトリクス設定

	D3DXMatrixPerspectiveFovLH(&m_ProjectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&m_ProjectionMatrix);


	Renderer::SetCameraPosition(m_Position);

}

bool Camera::CheckView(D3DXVECTOR3 pos)
{
	D3DXMATRIX vp, invvp;
	vp = m_ViewMatrix * m_ProjectionMatrix;
	D3DXMatrixInverse(&invvp, NULL, &vp);

	D3DXVECTOR3 vpos[4];
	D3DXVECTOR3 wpos[4];

	vpos[0] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vpos[1] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vpos[2] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vpos[3] = D3DXVECTOR3(1.0f, -1.0f, -1.0f);

	D3DXVec3TransformCoord(&wpos[0],&vpos[0],&invvp);
	D3DXVec3TransformCoord(&wpos[1],&vpos[1],&invvp);
	D3DXVec3TransformCoord(&wpos[2],&vpos[2],&invvp);
	D3DXVec3TransformCoord(&wpos[3],&vpos[3],&invvp);

	D3DXVECTOR3 v, v1, v2, n;
	v = pos - m_Position;

	{
		v1 = wpos[0] - m_Position;
		v2 = wpos[2] - m_Position;
		D3DXVec3Cross(&n, &v1, &v2);

		if (D3DXVec3Dot(&n, &v) < 0.0f)
		{
			return false;
		}

	}

	{
		v1 = wpos[1] - m_Position;
		v2 = wpos[3] - m_Position;
		D3DXVec3Cross(&n, &v1, &v2);

		if (D3DXVec3Dot(&n, &v) < 0.0f)
		{
			return false;
		}

	}


	return true;
}
