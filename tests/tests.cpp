#include "gtest/src/gtest-all.cc"

#include "solver.h"

using namespace SGBuilds;

TEST(Database, Instanciate)
{
    Database db;
}

TEST(BuildOrder, QuickdrawExos10MedTechs2)
{

}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
