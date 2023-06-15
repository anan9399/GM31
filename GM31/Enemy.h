#pragma once
#include "Player.h"
class Enemy : public Player
{
public:
	void Init() override;
	void Update()override;
private:
	float m_range = 5.0f;
	float m_nowRange = 0.0f;
	float speed = 0.2f;
	bool moveRight = true;

};

