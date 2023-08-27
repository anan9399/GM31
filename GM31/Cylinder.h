#pragma once
#include"GameObject.h"
#include<memory>
#include<vector>
#include"model.h"
class Scene;

class Cylinder : public GameObject
{
protected:

	D3DXMATRIX m_world, m_scale, m_rot, m_trans;
	std::unique_ptr<Model> m_model;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>m_pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pPixelShader;
	MATERIAL material;
	class Shadow* m_shadow;
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;



};
