#pragma once

#include "model.h"
#include "errorcodes.h"
#include "graph.h"
#include "solverstrategy.h"

#include <vector>
#include <unordered_set>

namespace SGBuilds
{
    struct BuildOrderStep
    {
        const unsigned supply;
        const unsigned time;
        const ObjectID buy;
    };

    class Solver
    {
    public:
        ErrorCode Solve(BuildTarget* targets, unsigned targetsSize);
        ErrorCode GetBuildOrderSize(unsigned& buildOrderSize);
        ErrorCode ReadAndClearBuildOrder(BuildOrderStep*& buildOrderSteps);

    private:
        ErrorCode ValidateTargetList(std::vector<BuildTarget> targetList);
        ErrorCode PrepareTargets(std::vector<BuildTarget>& targetList);
        ErrorCode InitSolver();
        ErrorCode ProcessGraph();
        ErrorCode PrepareBuildOrder();

    private:
        ObjectID _Faction;
        std::vector<BuildTarget> _Targets;

        Graph _Graph;
        std::vector<NodePtr> _LeafNodes;
        NodePtr _Solution;
    };
}
