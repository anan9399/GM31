#pragma once
#include"IdleState.h"
#include"Player.h"
#include"Keyboard.h"
#include<math.h>
void IdleState::OnEnter()
{
	m_manager->GetPlayer()->SetAnimation("Idle");
}

void IdleState::OnUpdate()
{
	bool move = false;

	auto v = m_manager->GetPlayer()->m_velocity;
	// attenuate velocity 
	if (abs(m_manager->GetPlayer()->m_velocity.z) <= 0.1f) {
		m_manager->GetPlayer()->m_velocity.z =0.0f;
	}
	else {
		auto a = m_manager->GetPlayer()->m_velocity.z / 2.0f;
		m_manager->GetPlayer()->m_velocity.z *=0.8f;
	}
	// attenuate velocity 
	if (abs(m_manager->GetPlayer()->m_velocity.x) <= 0.1f) {
		m_manager->GetPlayer()->m_velocity.x = 0.0f;
	}
	else {
		m_manager->GetPlayer()->m_velocity.x *= 0.8f;
	}

	if (Keyboard::GetKeyPress('W')) {
		move = true;
	}
	if (Keyboard::GetKeyPress('S')) {
		move = true;
	}
	if (Keyboard::GetKeyPress('A')) {
		move = true;
	}
	if (Keyboard::GetKeyPress('D')) {
		move = true;
	}
	if (m_manager->GetPlayer()->isGround &&
		Keyboard::GetKeyTrigger(VK_SPACE)) {
		m_manager->TransitionState(PLAYERSTATE::Jump);
	}
	if (move) {
		m_manager->TransitionState(PLAYERSTATE::Move);
	}
}

void IdleState::OnExit()
{
}



void MoveState::OnEnter()
{
	m_manager->GetPlayer()->SetAnimation("Run");
}

void MoveState::OnUpdate()
{
	bool move = false;
	if (Keyboard::GetKeyPress('W')) {
		m_manager->GetPlayer()->m_velocity.z += 0.01f;
		move = true;
	}
	if (Keyboard::GetKeyPress('S')) {
		m_manager->GetPlayer()->m_velocity.z -= 0.01f;
		move = true;
	}
	if (Keyboard::GetKeyPress('A')) {
		m_manager->GetPlayer()->m_velocity.x -= 0.01f;
		move = true;
	}
	if (Keyboard::GetKeyPress('D')) {
		m_manager->GetPlayer()->m_velocity.x += 0.01f;
		move = true;
	}
	m_manager->SaturateVelocity(m_manager->GetPlayer()->m_velocity);


	if (m_manager->GetPlayer()->isGround &&
		Keyboard::GetKeyTrigger(VK_SPACE)) {
		m_manager->TransitionState(PLAYERSTATE::Jump);
		return;
	}

	if (!move) {
		m_manager->TransitionState(PLAYERSTATE::Idle);
	}

}

void MoveState::OnExit()
{
}


void JumpState::OnEnter()
{
	//m_manager->GetPlayer()->SetAnimation("Jump");
	m_manager->GetPlayer()->m_velocity = { 
		m_manager->GetPlayer()->m_velocity.x * 0.3f,
		0.3f ,
		m_manager->GetPlayer()->m_velocity.z * 0.3f, };
	m_manager->GetPlayer()->isGround = false;

}

void JumpState::OnUpdate()
{
	if (Keyboard::GetKeyPress('W')) {
		m_manager->GetPlayer()->m_velocity.z += 0.01f;
	}
	if (Keyboard::GetKeyPress('S')) {
		m_manager->GetPlayer()->m_velocity.z -= 0.01f;

	}
	if (Keyboard::GetKeyPress('A')) {
		m_manager->GetPlayer()->m_velocity.x -= 0.01f;

	}
	if (Keyboard::GetKeyPress('D')) {
		m_manager->GetPlayer()->m_velocity.x += 0.01f;
	}
	m_manager->SaturateVelocity(m_manager->GetPlayer()->m_velocity);


	if (m_manager->GetPlayer()->isGround) {
		m_manager->TransitionState(PLAYERSTATE::Idle);
	}
}

void JumpState::OnExit()
{
}
