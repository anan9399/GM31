#include"Selector.h"


namespace BehaviorTree
{
    NodeState BehaviorTree::Selector::Evaluate()
    {
        {
            bool anyChildrenRunning = false;
            for (Node* node : children)
            {
                switch (node->Evaluate())
                {
                case NodeState::FAILURE:
                    continue;
                case NodeState::SUCCESS:
                    state = NodeState::SUCCESS;
                    return state;
                case NodeState::RUNNING:
                    state = NodeState::RUNNING;
                    return state;
                default:
                    continue;
                }
            }
            state = NodeState::FAILURE;
            return state;
        }
    }
}