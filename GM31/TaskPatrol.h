#pragma once
#include"main.h"
#include<vector>
#include<memory>
#include"Node.h"
namespace BehaviorTree {

	class TaskPatrol : public Node
	{
	public:
		TaskPatrol(D3DXVECTOR3 *pos, std::vector<D3DXVECTOR3> waypoints) {
			m_pos = pos;
			m_waypoints = waypoints;
		}

		NodeState Evaluate()override;
	
	private:
		D3DXVECTOR3* m_pos;
		std::vector<D3DXVECTOR3> m_waypoints;


		int _currentWaypointIndex = 0;
		float _waitTime = 1.0f;
		float _waitCounter = 0.0f;
		bool _waiting = false;

	};
}

