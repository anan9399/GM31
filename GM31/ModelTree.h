#pragma once
#include"GameObject.h"

class ModelTree : public GameObject
{
private:

	Microsoft::WRL::ComPtr <ID3D11Buffer> m_VertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;
public:
	void Init() override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
};

