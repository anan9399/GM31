#pragma once
#include"polygon2D.h"
#include"renderer.h"
#include"Sprite.h"

class FullScreen : public polygon2D
{
public:
	void Init()override {
		Renderer::CreatePixelShader(m_pPixelShader.ReleaseAndGetAddressOf(), "unlitTexturePS.cso");
		Renderer::CreateVertexShader(m_pVertexShader.ReleaseAndGetAddressOf(), m_pInputLayout.ReleaseAndGetAddressOf(), "unlitTextureVS.cso");


		AddComponent<Sprite>()->Init("asset\\texture\\field004.jpg", m_Position, SCREEN_HEIGHT, SCREEN_WIDTH);
		m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//AddComponent<Sprite>()->Init("asset\\texture\\field004.jpg",m_Position,2.0f,1.0f);
	}

	void Init(const char* name) {
		Renderer::CreatePixelShader(m_pPixelShader.ReleaseAndGetAddressOf(), "unlitTexturePS.cso");
		Renderer::CreateVertexShader(m_pVertexShader.ReleaseAndGetAddressOf(), m_pInputLayout.ReleaseAndGetAddressOf(), "unlitTextureVS.cso");


		AddComponent<Sprite>()->Init(name, m_Position, 720.0f, 1280.0f);
		m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//AddComponent<Sprite>()->Init("asset\\texture\\field004.jpg",m_Position,2.0f,1.0f);
	}


};