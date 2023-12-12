#pragma once
#include"Component.h"
#include<memory>
#include<vector>
#include<wrl.h>
#include"main.h"

class Shadow : public Component
{
private:

	Microsoft::WRL::ComPtr <ID3D11Buffer> m_VertexBuffer;
	Microsoft::WRL::ComPtr < ID3D11Buffer> m_IndexBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;

	D3DXVECTOR3 m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	std::vector<std::shared_ptr<class Bindable>> m_binds;


	int							m_numVertex = 0;
	int							m_numIndex = 0;
public:
	void Init() override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void SetPos(D3DXVECTOR3 pos) {
		m_Position = pos;
	}
	void SetScale(D3DXVECTOR3 scale) {
		m_Scale = scale;
	}
};

