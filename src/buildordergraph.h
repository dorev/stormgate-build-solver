#pragma once

#include "gamestate.h"

#include <unordered_set>
#include <memory>

namespace SGBuilds
{
    class BuildOrderGraph
    {
    public:
        struct Node
        {
            GameState state;
            std::unordered_set<std::shared_ptr<Node>> children;

            Node(const GameState& state)
                : state(state)
            {
            }
        };

        BuildOrderGraph()
            : _Root(nullptr)
        {
        }

        std::shared_ptr<Node> AddNode(const GameState& state)
        {
            std::shared_ptr<Node> node = std::make_shared<Node>(state);
            nodes.insert(node);

            if (_Root == nullptr)
            {
                _Root = node;
            }

            return node;
        }

        void AddEdge(const std::shared_ptr<Node>& fromNode, const std::shared_ptr<Node>& toNode)
        {
            fromNode->children.insert(toNode);
        }

    private:
        std::shared_ptr<Node> _Root;
        std::unordered_set<std::shared_ptr<Node>> nodes;
    };
}
