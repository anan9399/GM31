#pragma once
#include"Enemy.h"

namespace BehaviorTree {
	class GuardBT;
}


class EnemyCoward : public Enemy
{
public:
	void Init()override;
	void Update() override;
};

