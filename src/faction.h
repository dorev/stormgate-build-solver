#pragma once

#include "model.h"

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

        virtual ErrorCode ResetGameState(GameState& state) const = 0;
        virtual const SolverStrategy& GetSolverStrategy() const = 0;
        virtual int GetPopulationCap(const GameState& state) const = 0;
        virtual int LuminiteSaturated(const GameState& state) const = 0;
    };

    class Vanguard : public Faction
    {
    public:
        ErrorCode ResetGameState(GameState& state) const override;
        const SolverStrategy& GetSolverStrategy() const override;
        int GetPopulationCap(const GameState& state) const override;
        int LuminiteSaturated(const GameState& state) const override;
    };

    class Infernal : public Faction
    {
    public:
        ErrorCode ResetGameState(GameState& state) const override;
        const SolverStrategy& GetSolverStrategy() const override;
        int GetPopulationCap(const GameState& state) const override;
        int LuminiteSaturated(const GameState& state) const override;
    };

    class Celestial : public Faction
    {
    public:
        ErrorCode ResetGameState(GameState& state) const override;
        const SolverStrategy& GetSolverStrategy() const override;
        int GetPopulationCap(const GameState& state) const override;
        int LuminiteSaturated(const GameState& state) const override;
    };
}
