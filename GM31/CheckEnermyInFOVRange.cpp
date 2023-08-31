#include"CheckEnermyInFOVRange.h"
#include"GuardBT.h"

namespace BehaviorTree {
	NodeState BehaviorTree::CheckEnermyInFOVRange::Evaluate()
	{
		auto t = GetData("target");
		if (t == nullptr)
		{
			auto distance = m_target->GetPos() - *m_pos;
			float l = D3DXVec3Length(&distance);

			if (l <= GuardBT::fovRange) {
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
}