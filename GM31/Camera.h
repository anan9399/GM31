#pragma once
#include"GameObject.h"

class Camera : public GameObject
{

private:
	D3DXVECTOR3	m_Target{};

	D3DXMATRIX m_ViewMatrix{};
	D3DXMATRIX m_ProjectionMatrix{};

	float m_ShakeAmplitude{};
	int m_ShakeTime{};
	float m_ShakeOffset{};

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void Shake(float amp) {
		m_ShakeAmplitude = amp;
	}

	D3DXMATRIX GetViewMartix() {
		return m_ViewMatrix;
	}

	bool CheckView(D3DXVECTOR3 pos);

};