#pragma once
#include "Player.h"

namespace BehaviorTree {
	class GuardBT;
}


class Enemy : public Player
{
	
public:
	static void Load();
	static void UnLoad();

	void Init() override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
	BehaviorTree::GuardBT* guardBT;
	static std::unique_ptr<Model> m_model;

	float m_range = 5.0f;
	float m_nowRange = 0.0f;
	float speed = 0.2f;
	bool moveRight = true;

};

