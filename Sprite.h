#pragma once
#include<wrl.h>
#include "main.h"
#include "Component.h"

class Sprite : public Component 
{
private:
	Microsoft::WRL::ComPtr < ID3D11Buffer> m_VertexBuffer;
	Microsoft::WRL::ComPtr < ID3D11ShaderResourceView> m_Texture;
	D3DXVECTOR3 m_pos, m_rotation, m_scale;
public:
	void Init(const char* TextureName,D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f),float height=1.0f,float width=1.0f);
	void Uninit() ;
	void Update() ;
	void Draw() ;

};