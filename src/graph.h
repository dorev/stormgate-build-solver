#pragma once

#include "errorcodes.h"
#include "gamestate.h"

#include <unordered_set>
#include <memory>

namespace SGBuilds
{

    class Graph
    {
    public:
        struct Node;
        using NodePtr = std::shared_ptr<Node>;
        struct Node
        {
            GameState state;

            NodePtr parent;
            std::unordered_set<NodePtr> children;

            Node(const GameState& state)
                : state(state)
            {
            }
        };


        Graph()
            : _Root(nullptr)
        {
        }

        NodePtr AddNode(const GameState& state)
        {
            NodePtr node = std::make_shared<Node>(state);
            _Nodes.insert(node);

            if (_Root == nullptr)
            {
                _Root = node;
            }

            return node;
        }

        void AddEdge(const NodePtr& parentNode, const NodePtr& childNode)
        {
            parentNode->children.insert(childNode);
            childNode->parent = parentNode;
        }

        void RemoveNode(const NodePtr& node)
        {
            // Call recursively on children
            for (const NodePtr& child : node->children)
            {
                RemoveNode(child);
            }

            if (node->parent)
            {
                node->parent->children.erase(node);
            }

            _Nodes.erase(node);

            if (node == _Root)
            {
                _Root = nullptr;
            }
        }

        NodePtr GetRootNode()
        {
            return _Root;
        }

        void GetLeafNodes(std::vector<NodePtr>& leafNodes)
        {
            leafNodes.clear();

            for (NodePtr node : _Nodes)
            {
                if (node->children.empty())
                {
                    leafNodes.push_back(node);
                }
            }
        }

    private:
        std::shared_ptr<Node> _Root;
        std::unordered_set<std::shared_ptr<Node>> _Nodes;
    };

    using NodePtr =  Graph::NodePtr;
}
