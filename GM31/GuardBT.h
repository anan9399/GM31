#include"Tree.h"
#include"main.h"
#include"GameObject.h"
#include<vector>

namespace BehaviorTree
{
	class Node;
	class GuardBT :public Tree
	{
	public:
		GameObject* m_target;
		D3DXVECTOR3* m_pos;

		std::vector<D3DXVECTOR3> m_waypoints;

		float speed;
		static float fovRange;
		static float attackRange;

		GuardBT(GameObject* target, std::vector<D3DXVECTOR3> &waypoints): Tree()
		{
			m_target = target;
			m_pos = target->GetPosAdress();
			m_waypoints = waypoints;
			speed = 2.0f;
			root = SetupTree();
		}
	protected:
		Node* SetupTree() noexcept override;
	public:

	};
}