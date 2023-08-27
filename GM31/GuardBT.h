#include"Tree.h"
#include"main.h"

namespace BehaviorTree
{
	class Node;
	class GuardBT :public Tree
	{
	public:
		D3DXVECTOR3* m_pos;
		float speed;
		static float range;

		GuardBT(D3DXVECTOR3* pos): Tree()
		{
			m_pos = pos;
			speed = 2.0f;
			root = SetupTree();
		}
	protected:
		Node* SetupTree() noexcept override;
	public:

	};
}