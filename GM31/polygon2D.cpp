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
	//�����ɃV�F�[�_�[�I�u�W�F�N�g�̉����ǉ�
	GameObject::Uninit();
}


void polygon2D::Update()
{
	GameObject::Update();

}


void polygon2D::Draw()
{

	// �}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	//�����ɃV�F�[�_�[�֘A�̕`�揀����ǉ�
	Renderer::GetDeviceContext()->VSSetShader(m_pVertexShader.Get(), nullptr, 0u);
	Renderer::GetDeviceContext()->IASetInputLayout(m_pInputLayout.Get());
	Renderer::GetDeviceContext()->PSSetShader(m_pPixelShader.Get(), nullptr, 0u);




	GameObject::Draw();
}