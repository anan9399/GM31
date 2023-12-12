#pragma once
#include"IState.h"
#include"PlayerControlFSM.h"
class IdleState : public IState
{
public:
	IdleState(PlayerControlFSM *fsm) {
		m_manager = fsm;
	}

	void OnEnter()override;
	void OnUpdate()override;
	void OnExit()override;
private:
	PlayerControlFSM* m_manager;
	//PlayerParamater m_paramater;
};

class MoveState : public IState
{
public:
	MoveState(PlayerControlFSM *fsm) {
		m_manager = fsm;
	}
	void OnEnter()override;
	void OnUpdate()override;
	void OnExit()override;
private:
	PlayerControlFSM* m_manager;
	//PlayerParamater m_paramater;
};

class JumpState : public IState
{
public:
	JumpState(PlayerControlFSM *fsm) {
		m_manager = fsm;
	}
	void OnEnter()override;
	void OnUpdate()override;
	void OnExit()override;
private:
	PlayerControlFSM* m_manager;
	//PlayerParamater m_paramater;
};