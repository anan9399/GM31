#pragma once
#include"main.h"
#include<vector>
#include<memory>
#include"Node.h"
#include"Scene.h"
#include"manager.h"
#include"Player.h"


namespace BehaviorTree {

	class TaskAttack : public Node
	{
	public:
		TaskAttack(GameObject* target) {
			m_gameObject = target;
		}

		NodeState Evaluate()override {
			auto t = GetData("target");
			/*
			// for multiple enermy
			if (t != m_target) {
				
			}
			*/
			m_attackCounter += 0.02;
			m_gameObject->RotateOne();

			if (m_attackCounter >= m_attackTime) {
				// attack
				D3DXVECTOR3 add = { 0.0f,2.0f,1.0f };
				//*m_pos += add;
				
				t->Hurt();

				m_attackCounter = 0.0f;
			}


			state = NodeState::RUNNING;
			return state;

		}

	private:
		D3DXVECTOR3* m_pos;
		GameObject* m_gameObject;
		
		float m_attackCounter = 0.0f;
		float m_attackTime = 1.0f;

	};
}

