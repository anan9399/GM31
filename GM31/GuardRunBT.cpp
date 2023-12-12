#include"GuardRunBT.h"
#include"TaskPatrol.h"
#include"CheckEnermyInFOVRange.h"
#include"TaskRunAwayFromTarget.h"
#include"TaskGoToTarget.h"
#include<memory>
#include"Selector.h"
#include"Sequence.h"
#include<list>


namespace BehaviorTree {
	float GuardRunBT::fovRunRange = 5.0f;

	Node* GuardRunBT::SetupTree() noexcept
	{

		auto root = new Selector(std::list<Node*>{
				new Sequence(std::list<Node*>{
					new CheckEnermyInFOVRange(m_pos),
					new TaskRunAwayFromTarget(m_pos),
				}),
					new TaskPatrol(m_pos, m_waypoints),
		});

		//auto root = new TaskPatrol(m_pos, waypoints);
		//Node* root = new Node();
		return root;
	}
}