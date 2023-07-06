#include "polygon2D.h"
#include "renderer.h"
#include "MyTimer.h"
#include"Sprite.h"
#include"BindableBase.h"

void polygon2D::Init()
{
	
	auto pvs = std::make_shared<VertexShader>("unlitTextureVS.cso");
	auto fsize = pvs->Getfsize();
	auto buffer = pvs->GetBuffer();
	m_binds.push_back(std::move(pvs));

	m_binds.emplace_back(std::make_shared<InputLayout>(layout, "layout", buffer, fsize));
	m_binds.emplace_back(std::make_shared<PixelShader>("unlitTexturePS.cso"));

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
	for (auto b : m_binds) {
		b->Bind();
	}


	GameObject::Draw();
}