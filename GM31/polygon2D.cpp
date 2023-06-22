#include "polygon2D.h"
#include "renderer.h"
#include "MyTimer.h"
#include"Sprite.h"


void polygon2D::Init()
{
	

	Renderer::CreatePixelShader(m_pPixelShader.ReleaseAndGetAddressOf(), "unlitTexturePS.cso");
	Renderer::CreateVertexShader(m_pVertexShader.ReleaseAndGetAddressOf(), m_pInputLayout.ReleaseAndGetAddressOf(), "unlitTextureVS.cso");
	

	AddComponent<Sprite>()->Init("asset\\texture\\field004.jpg",m_Position,300.0f,300.0f);
	m_Position = D3DXVECTOR3(300.0f, 300.0f, 0.0f);
	//AddComponent<Sprite>()->Init("asset\\texture\\field004.jpg",m_Position,2.0f,1.0f);
}


void polygon2D::Uninit()
{
	//ここにシェーダーオブジェクトの解放を追加
	GameObject::Uninit();
}


void polygon2D::Update()
{
	GameObject::Update();

}


void polygon2D::Draw()
{

	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//ここにシェーダー関連の描画準備を追加
	Renderer::GetDeviceContext()->VSSetShader(m_pVertexShader.Get(), nullptr, 0u);
	Renderer::GetDeviceContext()->IASetInputLayout(m_pInputLayout.Get());
	Renderer::GetDeviceContext()->PSSetShader(m_pPixelShader.Get(), nullptr, 0u);




	GameObject::Draw();
}