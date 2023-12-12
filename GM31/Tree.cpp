#include"Tree.h"
#include"Node.h"


void BehaviorTree::Tree::Update()
{
    if (root != nullptr)
    {
        root->Evaluate();
    }
}
