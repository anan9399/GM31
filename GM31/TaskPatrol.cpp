#include "TaskPatrol.h"
#include"Node.h"


namespace BehaviorTree {
	NodeState BehaviorTree::TaskPatrol::Evaluate()
	{
		if (_waiting)
		{
			_waitCounter += 0.01;
			if (_waitCounter >= _waitTime)
			{

				_waiting = false;
			}
		}
		else
		{
			auto wp = m_waypoints[_currentWaypointIndex];

			D3DXVECTOR3 target = wp - *m_pos;
			auto length = D3DXVec3Length(&target);
			if (length <= 0.01f)
			{
				*m_pos = wp;
				_waiting = true;
				_waitCounter = 0.0f;
				_currentWaypointIndex = (_currentWaypointIndex + 1) % m_waypoints.size();
			}
			else {
				D3DXVec3Normalize(&target, &target);
				*m_pos += target * 0.03f;
			}
		}

		state = NodeState::RUNNING;
		return state;
	}
}