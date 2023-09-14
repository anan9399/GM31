#pragma once
#include"GameObject.h"
#include<memory>
#include<vector>
#include"animationModel.h"
#include<string>

#include"Bullet.h"
class Scene;
class Audio;



enum PLAYER_STATE {
	PLAYER_STATE_GROUND,
	PLAYER_STATE_JUMP,

};

class Player : public GameObject
{
protected:

	D3DXMATRIX m_world, m_scale, m_rot, m_trans;
	std::unique_ptr<AnimationModel> m_model;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>m_pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pPixelShader;
	MATERIAL material;
	D3DXVECTOR3 m_velocity{};
	float m_speed;
	bool isGround = true;
	bool superBullet = false;
	Audio* m_shotSE;
	class Shadow* m_shaow;
	D3DMATRIX m_matrix;

	std::string m_animationName;
	std::string m_nextAnimationName;
	int m_time= 0;
	float m_blendRate = 0.0f;
	PLAYER_STATE m_state = PLAYER_STATE_GROUND;

private:

public:
	int playerHP;
	bool m_dead = false;

	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void Hurt()override;
	void SetExplosion();

	void UpdateGround();
	void UpdateJump();
	void SetAnimation(std::string animationName);
	D3DMATRIX GetMatrix() { return m_matrix; }


};

