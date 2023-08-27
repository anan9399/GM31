#pragma once
#include"main.h"
#include<vector>
#include<memory>

#include"Scene.h"
#include"manager.h"
#include"Player.h"


namespace BehaviorTree {

	class CheckEnermyInFOVRange : public Node
	{
	public:
		CheckEnermyInFOVRange(D3DXVECTOR3* pos) {
			m_pos = pos;
			m_target = Manager::GetInstance().GetScene()->GetGameObj<Player>();

		}

		NodeState Evaluate()override {
			auto t = GetData("target");
			if (t == nullptr)
			{
				auto distance = m_target->GetPos() - *m_pos;
				float l = D3DXVec3Length(&distance);

				if (l < 4.0f) {
					parent->parent->SetData("target", m_target);
					state = NodeState::SUCCESS;
					return state;
				}
				state = NodeState::FAILURE;
				return state;
			}

			state = NodeState::SUCCESS;
			return state;
		}

	private:
		D3DXVECTOR3* m_pos;
		GameObject* m_target;
	};
}

