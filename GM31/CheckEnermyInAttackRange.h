#pragma once
#include"main.h"
#include<vector>
#include<memory>
#include"Node.h"
#include"Scene.h"
#include"manager.h"
#include"Player.h"


namespace BehaviorTree {

	class CheckEnermyInAttackRange : public Node
	{
	public:
		CheckEnermyInAttackRange(D3DXVECTOR3* pos) {
			m_pos = pos;

		}

		NodeState Evaluate()override {
			auto t = GetData("target");
			if (t == nullptr)
			{
				state = NodeState::FAILURE;
				return state;
			}
			auto targetPos = t->GetPos();
			auto direction = targetPos - *m_pos;
			float l = D3DXVec3Length(&direction);
			if (l <= GuardBT::attackRange) {
				state = NodeState::SUCCESS;
				return state;
			}

			state = NodeState::FAILURE;
			return state;
		}

	private:
		D3DXVECTOR3* m_pos;
		//GameObject* m_target;
	};
}

