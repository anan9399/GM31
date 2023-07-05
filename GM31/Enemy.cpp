#include "Enemy.h"
#include <random>
#include <iostream>
#include"BindableBase.h"

std::mt19937 rngE({ std::random_device{}() });
std::uniform_real_distribution<float> dx(0.0f, 0.3f);

void Enemy::Init()
{
	m_model = std::make_unique<Model>();
	m_model->Load("asset\\model\\torus.obj");

	auto pvs = std::make_shared<VertexShader>("vertexLightingVS.cso");
	auto fsize = pvs->Getfsize();
	auto buffer = pvs->GetBuffer();
	binds.push_back(std::move(pvs));
	binds.emplace_back(std::make_shared<InputLayout>(layout, buffer, fsize));
	binds.emplace_back(std::make_shared<PixelShader>("vertexLightingPS.cso"));

	speed = dx(rngE);
	//m_Position = D3DXVECTOR3(0.0f, 1.0f, 1.0f);
	
}

void Enemy::Update()
{
	/*if (m_nowRange >= m_range) {
		moveRight = false;
	}
	if (m_nowRange <= -m_range) {
		moveRight = true;
	}

	m_nowRange += moveRight ? speed : -speed;
	m_Position += moveRight ? D3DXVECTOR3(speed, 0.0f, 0.0f) : D3DXVECTOR3(-speed, 0.0f, 0.0f);*/

}


