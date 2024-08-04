#pragma once

#include "model.h"
//#include "solverstrategy.h"

namespace SGBuilds
{
    class GameState;
    class SolverStrategy;

    class Faction
    {
    public:
        static const Faction& Get(const ObjectID& id);
        static const SolverStrategy& Strategy(const ObjectID& id);

        virtual ~Faction();

        virtual ErrorCode ResetGameState(GameState& state) const;
        virtual const SolverStrategy& GetSolverStrategy() const;
        virtual int GetPopulationCap(const GameState& state) const;
        virtual bool LuminiteSaturated(const GameState& state) const;
        virtual ErrorCode StartBuildingProduction(GameState& state) const;
        virtual ErrorCode FinishBuildingProduction(GameState& state) const;
        virtual bool HasBuilderAvailable(const GameState& state) const;
    };

    class Vanguard : public Faction
    {
    public:
        ErrorCode ResetGameState(GameState& state) const override;
        const SolverStrategy& GetSolverStrategy() const override;
        int GetPopulationCap(const GameState& state) const override;
        bool LuminiteSaturated(const GameState& state) const override;
        ErrorCode StartBuildingProduction(GameState& state) const override;
        ErrorCode FinishBuildingProduction(GameState& state) const override;
        bool HasBuilderAvailable(const GameState& state) const override;
    };

    class Infernal : public Faction
    {
    /*
    public:
        ErrorCode ResetGameState(GameState& state) const override;
        const SolverStrategy& GetSolverStrategy() const override;
        int GetPopulationCap(const GameState& state) const override;
        bool LuminiteSaturated(const GameState& state) const override;
    */
    };

    class Celestial : public Faction
    {
    /*
    public:
        ErrorCode ResetGameState(GameState& state) const override;
        const SolverStrategy& GetSolverStrategy() const override;
        int GetPopulationCap(const GameState& state) const override;
        bool LuminiteSaturated(const GameState& state) const override;
    */
    };
}
