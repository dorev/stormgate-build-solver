#include "graph.h"

namespace SGBuilds
{
    Graph::Node::Node(const GameState& state)
        : state(state)
    {
    }

    Graph::Graph()
        : _Root(nullptr)
    {
    }

    NodePtr Graph::AddNode(const GameState& state)
    {
        NodePtr node = std::make_shared<Node>(state);
        _Nodes.insert(node);

        if (_Root == nullptr)
        {
            _Root = node;
        }

        return node;
    }

    void Graph::AddEdge(const NodePtr& parentNode, const NodePtr& childNode)
    {
        parentNode->children.insert(childNode);
        childNode->parent = parentNode;
    }

    void Graph::RemoveNode(const NodePtr& node)
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

    NodePtr Graph::GetRootNode()
    {
        return _Root;
    }

    void Graph::GetLeafNodes(std::vector<NodePtr>& leafNodes)
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
}
