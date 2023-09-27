#pragma once

class IState
{
public:
	virtual void OnEnter() {};
	virtual void OnUpdate() {};
	virtual void OnExit() {};

};