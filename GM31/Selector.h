#pragma once
#include"Node.h"

namespace BehaviorTree
{
    class Selector : public Node
    {
    public:
        Selector() : Node() {}
        Selector(std::list<Node*> children) : Node(children) {}

        NodeState Evaluate() override;
      
    };
} 
