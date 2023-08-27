#include"GuardBT.h"
#include"TaskPatrol.h"
#include"CheckEnermyInFOVRange.h"
#include"TaskGoToTarget.h"
#include<memory>
#include"Selector.h"
#include"Sequence.h"
#include<list>

namespace BehaviorTree {

	Node* GuardBT::SetupTree() noexcept
	{
		std::vector<D3DXVECTOR3> waypoints = { {0.0f,0.0f,10.0f},{0.0f,3.0f,10.0f},{10.0f,3.0f,10.0f} };
		auto root = new Selector(std::list<Node*>{
			new Sequence(std::list<Node*>{
				new CheckEnermyInFOVRange(m_pos),
				new TaskGoToTarget(m_pos),
			}),
			new TaskPatrol(m_pos, waypoints),
			});

		//auto root = new TaskPatrol(m_pos, waypoints);
		//Node* root = new Node();
		return root;
	}
}