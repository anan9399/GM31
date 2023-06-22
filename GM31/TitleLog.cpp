#include "TitleLog.h"
#include "renderer.h"
#include "MyTimer.h"
#include"Sprite.h"

void TitleLog::Init()
{
	Renderer::CreatePixelShader(m_pPixelShader.ReleaseAndGetAddressOf(), "unlitTexturePS.cso");
	Renderer::CreateVertexShader(m_pVertexShader.ReleaseAndGetAddressOf(), m_pInputLayout.ReleaseAndGetAddressOf(), "unlitTextureVS.cso");


	AddComponent<Sprite>()->Init("asset\\texture\\field004.jpg", m_Position, SCREEN_HEIGHT, SCREEN_WIDTH);
	m_Position = D3DXVECTOR3(300.0f, 300.0f, 0.0f);
	//AddComponent<Sprite>()->Init("asset\\texture\\field004.jpg",m_Position,2.0f,1.0f);

}
