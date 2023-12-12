#pragma once
#include"IState.h"
#include<unordered_map>
#include"main.h"
#include"renderer.h"
#include<memory>

class Player;
enum class PLAYERSTATE {
	Idle,
	Move,
	Jump,
};

class PlayerParamater {

};
class PlayerControlFSM
{
public:
	PlayerControlFSM(Player *player);
	void Update();
	void TransitionState(PLAYERSTATE type);
	void SaturateVelocity(D3DXVECTOR3 &velocity);
	Player* GetPlayer();

private:
	//PlayerParamater m_paramater;
	float m_maxSpeed = 0.2f;
	std::shared_ptr<IState>currentState = nullptr;
	std::unordered_map <PLAYERSTATE, std::shared_ptr<IState>> states;
	Player *m_player;
};

