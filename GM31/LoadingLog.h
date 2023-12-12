#pragma once
#include"polygon2D.h"
#include"renderer.h"
#include"Sprite.h"
#include"BindableBase.h"

class LoadingLog : public GameObject
{

public:
	void Init() override
	{
		auto pvs = std::make_shared<VertexShader>("unlitTextureVS.cso");
		auto fsize = pvs->Getfsize();
		auto buffer = pvs->GetBuffer();
		AddBind(std::move(pvs));
		AddBind(std::make_shared<InputLayout>(layout, "layout", buffer, fsize));
		AddBind(std::make_shared<PixelShader>("unlitTexturePS.cso"));

		m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		AddComponent<Sprite>()->Init("asset\\texture\\loading.jpg", m_Position, SCREEN_HEIGHT/2, SCREEN_WIDTH/2);
	
		//AddComponent<Sprite>()->Init("asset\\texture\\field004.jpg",m_Position,20.0f,10.0f);

	}

	void Update()override {

		float speed = 1.0f;
		if (m_Position.x < 0) {
			speed = 1.0f;
		}
		else if (m_Position.x > SCREEN_WIDTH/2) {
			speed = -1.0f;
		}

	


		m_Position.x += speed;
		GameObject::Update();

	}

	void Draw() override
	{
		//ここにシェーダー関連の描画準備を追加
		for (auto b : m_binds) {
			b->Bind();
		}

		// マトリクス設定
		Renderer::SetWorldViewProjection2D();
		// マトリクス設定
		D3DXMATRIX world, scale, rot, trans;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
		world = scale * rot * trans;
		Renderer::SetWorldMatrix(&world);



		GameObject::Draw();
	}
};

