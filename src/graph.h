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
            Graph& graph;
            NodePtr parent;
            std::unordered_set<NodePtr> children;

            Node(const GameState& state, Graph& graph);
        };

        Graph();
        NodePtr AddNode(const GameState& state);
        void AddEdge(const NodePtr& parentNode, const NodePtr& childNode);
        void RemoveNode(const NodePtr& node);
        NodePtr GetRootNode();
        void GetLeafNodes(std::vector<NodePtr>& leafNodes);

    private:
        std::shared_ptr<Node> _Root;
        std::unordered_set<std::shared_ptr<Node>> _Nodes;
    };

    using NodePtr =  Graph::NodePtr;
}
