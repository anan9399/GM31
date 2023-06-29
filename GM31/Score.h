#pragma once
#include "GameObject.h"


class Score : public GameObject
{
protected:
	Microsoft::WRL::ComPtr <ID3D11Buffer> m_VertexBuffer;
	Microsoft::WRL::ComPtr <ID3D11ShaderResourceView> m_Texture;

	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>m_pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pPixelShader;
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void AddCount(int count) {
		
		m_count += count;
	}
	int* GetCount() {
		
		return &m_count;
	}
private:
	//bool m_dirty = true;
	int m_count =0;
};

