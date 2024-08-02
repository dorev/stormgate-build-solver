#include "gtest/src/gtest-all.cc"

#include "solver.h"
#include "database.h"

using namespace SGBuilds;

TEST(Database, Instanciate)
{
    Database db;
}

TEST(BuildOrder, QuickdrawExos10MedTechs2)
{
    Target targets[] = 
    {
        { ID::Exo, 10 },
        { ID::MedTech, 2 },
        { ID::QuickdrawHustle }
    };

    Solver solver;
    ErrorCode result = solver.Solve(targets, sizeof(targets) / sizeof(Target));
    EXPECT_EQ(result, Success);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
