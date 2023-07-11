#include "Fade.h"
#include "renderer.h"
#include "MyTimer.h"
#include"Sprite.h"
#include"BindableBase.h"

void Fade::Init()
{

	auto pvs = std::make_shared<VertexShader>("unlitTextureVS.cso");
	auto fsize = pvs->Getfsize();
	auto buffer = pvs->GetBuffer();
	m_binds.push_back(std::move(pvs));
	m_binds.emplace_back(std::make_shared<InputLayout>(layout, "layout", buffer, fsize));
	m_binds.emplace_back(std::make_shared<PixelShader>("SolidColorPS.cso"));
	
	m_sprite = AddComponent<Sprite>();
	m_sprite->Init("asset\\texture\\black.png", m_Position, SCREEN_HEIGHT, SCREEN_WIDTH);
	

	m_Position = D3DXVECTOR3(300.0f, 300.0f, 0.0f);
}


void Fade::Uninit()
{
	//ここにシェーダーオブジェクトの解放を追加
	GameObject::Uninit();
}


void Fade::Update()
{
	GameObject::Update();
	if (!fadeOut) 
	{
		if (m_alpha >= 0.0f) {
			m_sprite->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, m_alpha));
			m_alpha -= 0.02f;
		}
	}
	else
	{
		if (m_alpha <= 1.0f) {
			m_sprite->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, m_alpha));
			m_alpha += 0.02f;
		}
		else {
			isFadeFinished = true;
		}
	}
}


void Fade::Draw()
{

	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//ここにシェーダー関連の描画準備を追加
	for (auto b : m_binds) {
		b->Bind();
	}


	GameObject::Draw();
}