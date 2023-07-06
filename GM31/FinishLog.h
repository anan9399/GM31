#pragma once
#include"polygon2D.h"
#include"renderer.h"
#include"Sprite.h"
#include"BindableBase.h"
class FinishLog : public polygon2D
{

public:
	void Init() override 
	{
		auto pvs = std::make_shared<VertexShader>("unlitTextureVS.cso");
		auto fsize = pvs->Getfsize();
		auto buffer = pvs->GetBuffer();
		binds.push_back(std::move(pvs));

		binds.emplace_back(std::make_shared<InputLayout>(layout, buffer, fsize));
		binds.emplace_back(std::make_shared<PixelShader>("unlitTexturePS.cso"));


		AddComponent<Sprite>()->Init("asset\\texture\\finish1.png", m_Position, SCREEN_HEIGHT, SCREEN_WIDTH);
		m_Position = D3DXVECTOR3(300.0f, 300.0f, 0.0f);
		//AddComponent<Sprite>()->Init("asset\\texture\\field004.jpg",m_Position,2.0f,1.0f);

	}
};

