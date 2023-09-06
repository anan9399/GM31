#pragma once
#include "GameObject.h"
#include<string>

class polygon2D: public GameObject
{
protected:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>m_pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pPixelShader;
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

