#include <iostream>

namespace BehaviorTree
{
    class Node; // Forward declaration of Node class (to be defined later)

    class Tree
    {
    protected:
        Node* root = nullptr;

    public:
        Tree()
        {
            root = SetupTree();
        }

        void Update();

    protected:
        virtual Node* SetupTree() noexcept { return nullptr; };
    };
}