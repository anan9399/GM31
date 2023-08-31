#include "EnemyCoward.h"
#include"GuardRunBT.h"

void EnemyCoward::Init()
{


	Enemy::Init();
}

void EnemyCoward::Update()
{
	if (m_guardBT != nullptr) {
		m_guardBT->Update();
	}
	else {
		m_guardBT = new BehaviorTree::GuardRunBT(this, m_waypoints);
	}
}
