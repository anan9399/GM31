#include "TitleLog.h"
#include "renderer.h"
#include "MyTimer.h"
#include"Sprite.h"
#include"BindableBase.h"

void TitleLog::Init()
{
	auto pvs = std::make_shared<VertexShader>("unlitTextureVS.cso");
	auto fsize = pvs->Getfsize();
	auto buffer = pvs->GetBuffer();
	m_binds.push_back(std::move(pvs));

	m_binds.emplace_back(std::make_shared<InputLayout>(layout, "layout",buffer, fsize));
	m_binds.emplace_back(std::make_shared<PixelShader>("unlitTexturePS.cso"));


	AddComponent<Sprite>()->Init("asset\\texture\\title.png", m_Position, SCREEN_HEIGHT, SCREEN_WIDTH);
	m_Position = D3DXVECTOR3(300.0f, 300.0f, 0.0f);
	//AddComponent<Sprite>()->Init("asset\\texture\\field004.jpg",m_Position,2.0f,1.0f);

}
