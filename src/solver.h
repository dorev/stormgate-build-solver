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
        ErrorCode Solve(Objective* objectives, unsigned objectivesSize);
        ErrorCode GetBuildOrderSize(unsigned& buildOrderSize);
        ErrorCode ReadAndClearBuildOrder(BuildOrderStep*& buildOrderSteps);

    private:
        ErrorCode ValidateObjectiveList(std::vector<Objective> objectiveList);
        ErrorCode PrepareObjectives(std::vector<Objective>& objectiveList);
        ErrorCode InitSolver();
        ErrorCode ProcessGraph();
        ErrorCode PrepareBuildOrder();

    private:
        ObjectID _Faction;
        std::vector<Objective> _Objectives;

        Graph _Graph;
        std::vector<NodePtr> _LeafNodes;
        NodePtr _Solution;
    };
}
