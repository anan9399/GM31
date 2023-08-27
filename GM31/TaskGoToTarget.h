#pragma once
#include"main.h"
#include<vector>
#include<memory>
#include"Node.h"
#include"Scene.h"
#include"manager.h"
#include"Player.h"


namespace BehaviorTree {

	class TaskGoToTarget : public Node
	{
	public:
		TaskGoToTarget(D3DXVECTOR3* pos) {
			m_pos = pos;
	
		}

		NodeState Evaluate()override {
			auto t = GetData("target");
			auto targetPos = t->GetPos();
			auto direction = targetPos - *m_pos;
			float l = D3DXVec3Length(&direction);

			if (l > 0.01f) {
				D3DXVec3Normalize(&direction, &direction);
				if (m_pos->y <= 0.2f || m_pos->y >= 4.0f) {
					direction.y = 0.0f;
				}

				*m_pos -= direction * 0.05f;
			
				if (l > 30.0f) {
					ClearData("target");
					state = NodeState::FAILURE;
					return state;
				}
			}

			state = NodeState::RUNNING;
			return state;
		}

	private:
		D3DXVECTOR3* m_pos;
		//GameObject* m_target;
	};
}

