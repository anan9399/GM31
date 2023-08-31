#pragma once
#include"main.h"
#include<vector>
#include<memory>
#include"Node.h"
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

		NodeState Evaluate()override;

	private:
		D3DXVECTOR3* m_pos;
		GameObject* m_target;
	};
}

