#pragma once
#include"GameObject.h"

class ModelTree : public GameObject
{
private:

	static Microsoft::WRL::ComPtr <ID3D11Buffer> m_VertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;
public:
	static void Load();
	static void Unload();
	void Init() override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
};

