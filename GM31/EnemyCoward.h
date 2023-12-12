#pragma once
#include"Enemy.h"

namespace BehaviorTree {
	class GuardBT;
}


class EnemyCoward : public Enemy
{
public:
	static void Load();
	static void UnLoad();

	void Init()override;
	void Update() override;
	void Draw() override;
private:
	static std::unique_ptr<Model> m_model;
};

