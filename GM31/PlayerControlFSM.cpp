#include "PlayerControlFSM.h"
#include"IdleState.h"
#include"Player.h"


PlayerControlFSM::PlayerControlFSM(Player* player)
{
	states[PLAYERSTATE::Idle] = new IdleState(this);
	states[PLAYERSTATE::Move] = new MoveState(this);
	states[PLAYERSTATE::Jump] = new JumpState(this);

	m_player = player;
	TransitionState(PLAYERSTATE::Idle);
}

void PlayerControlFSM::Update()
{
	currentState->OnUpdate();
}

void PlayerControlFSM::TransitionState(PLAYERSTATE type)
{
	if (currentState != nullptr) {
		currentState->OnExit(); 
	}
	currentState = states[type];
	currentState->OnEnter();
}

void PlayerControlFSM::SaturateVelocity(D3DXVECTOR3& velocity)
{
	if (velocity.x >= m_maxSpeed) {
		velocity.x = m_maxSpeed;
	}
	if (velocity.x < -m_maxSpeed) {
		velocity.x = -m_maxSpeed;
	}
	if (velocity.z >= m_maxSpeed) {
		velocity.z = m_maxSpeed;
	}
	if (velocity.z < -m_maxSpeed) {
		velocity.z = -m_maxSpeed;
	}
}

Player* PlayerControlFSM::GetPlayer()
{
	return m_player;
}
