#pragma once
#include <iostream>
#include <list>
#include "Node.h"

namespace BehaviorTree
{
    class Sequence : public Node
    {
    public:
        Sequence() : Node() {}
        Sequence(std::list<Node*> children) : Node(children) {}

        NodeState Evaluate() override
        {
            bool anyChildrenRunning = false;
            for (Node* node : children)
            {
                switch (node->Evaluate())
                {
                case NodeState::FAILURE:
                    state = NodeState::FAILURE;
                    return state;
                case NodeState::SUCCESS:
                    continue;
                case NodeState::RUNNING:
                    anyChildrenRunning = true;
                    continue;
                default:
                    state = NodeState::SUCCESS;
                    return state;
                }
            }
            state = anyChildrenRunning ? NodeState::RUNNING : NodeState::SUCCESS;
            return state;
        }
    };
} // namespace BehaviorTree
