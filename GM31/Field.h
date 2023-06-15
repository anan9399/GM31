#pragma once
#include"GameObject.h"

class Field : public GameObject
{
private:

	Microsoft::WRL::ComPtr <ID3D11Buffer> m_VertexBuffer;
	Microsoft::WRL::ComPtr <ID3D11ShaderResourceView> m_Texture;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>m_pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pPixelShader;
public:
	void Init() override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

};

