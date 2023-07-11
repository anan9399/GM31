#pragma once
#include"GameObject.h"

class Fade : public GameObject
{
protected:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>m_pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pPixelShader;
	class Sprite* m_sprite;
	float m_alpha = 1.0f;
	bool fadeOut = false;
	bool isFadeFinished = false;
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void FadeOut() {
		fadeOut = true;
		m_alpha = 0.0f;
	}
	bool GetFadeFinished() {
		return isFadeFinished;
	}
};
