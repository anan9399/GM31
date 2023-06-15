#include "Enemy.h"
#include<random>
#include<iostream>
std::mt19937 rng({ std::random_device{}() });
std::uniform_real_distribution<float> xdist(0.0f, 0.3f);

void Enemy::Init()
{
	m_Model = std::make_unique<Model>();
	m_Model->Load("asset\\model\\torus.obj");

	Renderer::CreatePixelShader(m_pPixelShader.ReleaseAndGetAddressOf(), "vertexLightingPS.cso");
	Renderer::CreateVertexShader(m_pVertexShader.ReleaseAndGetAddressOf(), m_pInputLayout.ReleaseAndGetAddressOf(), "vertexLightingVS.cso");

	speed = xdist(rng);
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


