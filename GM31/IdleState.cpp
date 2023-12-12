#pragma once
#include"IdleState.h"
#include"Player.h"
#include"Keyboard.h"
#include<math.h>
#include"Scene.h"
#include"manager.h"
#include"Camera.h"
void IdleState::OnEnter()
{
	m_manager->GetPlayer()->SetAnimation("Idle");
}

void IdleState::OnUpdate()
{
	bool move = false;

	auto v = m_manager->GetPlayer()->m_velocity;
	auto pQuaternion = &m_manager->GetPlayer()->m_Quaternion;
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

		D3DXQUATERNION quat = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
		D3DXQuaternionSlerp(pQuaternion, pQuaternion, &quat, 0.1f);
	}
	if (Keyboard::GetKeyPress('S')) {
		move = true;
		D3DXQUATERNION quat;
		D3DXVECTOR3 axis = { 0.0f,1.0f,0.0f };
		D3DXQuaternionRotationAxis(&quat, &axis, D3DX_PI);
		D3DXQuaternionSlerp(pQuaternion, pQuaternion, &quat, 0.1f);
	}
	if (Keyboard::GetKeyPress('A')) {
		move = true;


		D3DXQUATERNION quat;
		D3DXVECTOR3 axis = { 0.0f,1.0f,0.0f };
		D3DXQuaternionRotationAxis(&quat,&axis,-D3DX_PI/2);
		D3DXQuaternionSlerp(pQuaternion, pQuaternion, &quat, 0.1f);
		//m_manager->GetPlayer()->m_Quaternion = quat;
	}
	if (Keyboard::GetKeyPress('D')) {
		move = true;

		D3DXQUATERNION quat;
		D3DXVECTOR3 axis = { 0.0f,1.0f,0.0f };
		D3DXQuaternionRotationAxis(&quat, &axis, D3DX_PI / 2);

		D3DXQuaternionSlerp(pQuaternion, pQuaternion, &quat, 0.1f);
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
	auto pQuaternion = &m_manager->GetPlayer()->m_Quaternion;
	if (Keyboard::GetKeyPress('W')) {
		m_manager->GetPlayer()->m_velocity.z += 0.01f;
		D3DXQUATERNION quat = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
		D3DXQuaternionSlerp(pQuaternion, pQuaternion, &quat, 0.1f);
		move = true;
	}
	if (Keyboard::GetKeyPress('S')) {
		m_manager->GetPlayer()->m_velocity.z -= 0.01f;
		D3DXQUATERNION quat;
		D3DXVECTOR3 axis = { 0.0f,1.0f,0.0f };
		D3DXQuaternionRotationAxis(&quat, &axis, D3DX_PI);
		D3DXQuaternionSlerp(pQuaternion, pQuaternion, &quat, 0.1f);
		move = true;
	}
	if (Keyboard::GetKeyPress('A')) {
		m_manager->GetPlayer()->m_velocity.x -= 0.01f;
		D3DXQUATERNION quat;
		D3DXVECTOR3 axis = { 0.0f,1.0f,0.0f };
		D3DXQuaternionRotationAxis(&quat, &axis, -D3DX_PI / 2);
		D3DXQuaternionSlerp(pQuaternion, pQuaternion, &quat, 0.1f);
		move = true;
	}
	if (Keyboard::GetKeyPress('D')) {
		m_manager->GetPlayer()->m_velocity.x += 0.01f;
		D3DXQUATERNION quat;
		D3DXVECTOR3 axis = { 0.0f,1.0f,0.0f };
		D3DXQuaternionRotationAxis(&quat, &axis, D3DX_PI / 2);
		D3DXQuaternionSlerp(pQuaternion, pQuaternion, &quat, 0.1f);
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
		
		Manager::GetInstance().GetScene()->GetGameObj<Camera>()->Shake(1.0f);
	}
}

void JumpState::OnExit()
{
}
