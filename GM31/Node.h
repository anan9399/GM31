#pragma once
#include<unordered_map>
#include<list>
#include<string>


class GameObject;


namespace BehaviorTree
{
    enum class NodeState
    {
        RUNNING,
        SUCCESS,
        FAILURE
    };

    class Node
    {
    public:
         Node()
        {
            parent = nullptr;
        }

        Node(std::list<Node*> children)
        {
            for (auto& c : children) {
                _Attach(c);
            }
        }

        virtual NodeState Evaluate() { return NodeState::FAILURE; };

        void SetData(std::string key, GameObject* value)
        {
            dataContext[key] = value;
        }

        GameObject* GetData(std::string key)
        {
            auto it = dataContext.find(key);
            if (it != dataContext.end())
            {
                return it->second;
            }

            Node* node = parent;
            while (node != nullptr)
            {
                auto* value = node->GetData(key);
                if (value != nullptr)
                {
                    return value;
                }
                node = node->parent;
            }
            return nullptr;
        }

        bool ClearData(std::string key)
        {
            auto it = dataContext.find(key);
            if (it != dataContext.end())
            {
                dataContext.erase(it);
                return true;
            }

            Node* node = parent;
            while (node != nullptr)
            {
                bool cleared = node->ClearData(key);
                if (cleared)
                {
                    return true;
                }
                node = node->parent;
            }
            return false;
        }

    private:
        void _Attach(Node* node)
        {
            node->parent = this;
            children.push_back(node);
        }
    protected:
        std::list<Node*> children;
        NodeState state = NodeState::FAILURE;
        std::unordered_map<std::string,GameObject*> dataContext;
    public:
        Node *parent = nullptr;
    };
}
