#pragma once
#include"GameObject.h"
#include "model.h"
#include<memory>

class Player;

class SuperBullet : public GameObject
{
private:
	D3DXMATRIX m_world, m_mScale, m_mRot, m_mTrans;
	static std::unique_ptr<Model> m_model;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>m_pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pPixelShader;

	D3DXVECTOR3 m_velocity;
	float m_life;
public:
	static void Load();
	static void UnLoad();

	void Init() override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void SetVelocity(D3DXVECTOR3 v) {
		m_velocity = v;
	}
private:
	void SetExplosion();
};

