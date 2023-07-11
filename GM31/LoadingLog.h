#pragma once
#include"polygon2D.h"
#include"renderer.h"
#include"Sprite.h"
#include"BindableBase.h"

class LoadingLog : public polygon2D
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


		AddComponent<Sprite>()->Init("asset\\texture\\loading.jpg", m_Position, SCREEN_HEIGHT, SCREEN_WIDTH);
		m_Position = D3DXVECTOR3(300.0f, 300.0f, 0.0f);
		//AddComponent<Sprite>()->Init("asset\\texture\\field004.jpg",m_Position,2.0f,1.0f);

	}
};

