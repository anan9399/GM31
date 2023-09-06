#include"GuardBT.h"
#include"TaskPatrol.h"
#include"CheckEnermyInFOVRange.h"
#include"CheckEnermyInAttackRange.h"
#include"TaskAttack.h"
#include"TaskGoToTarget.h"
#include<memory>
#include"Selector.h"
#include"Sequence.h"
#include<list>


namespace BehaviorTree {
	float GuardBT::fovRange = 6.0f;
	float GuardBT::attackRange = 0.3f;
	
	Node* GuardBT::SetupTree() noexcept
	{
		
		auto root = new Selector(std::list<Node*>{
			new Sequence(std::list<Node*>{
				new CheckEnermyInAttackRange(m_pos),
				new TaskAttack(m_target),
			}),
				new Sequence(std::list<Node*>{
				new CheckEnermyInFOVRange(m_pos),
				new TaskGoToTarget(m_pos),
			}),
			new TaskPatrol(m_pos, m_waypoints),
			});

		return root;
	}
}