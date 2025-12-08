#include "dec_1.h"

#include <gtest/gtest.h>

#include <cstdio> // for std::remove
#include <filesystem>
#include <fstream>

struct MoveTestCase {
    std::string fileContent;
    int expectedResult;
};

class FileIOTest : public ::testing::TestWithParam<MoveTestCase> {
  protected:
    std::filesystem::path tempFilename = "test_input.txt";

    // Runs before each test
    void SetUp() override {
        // GetParam() retrieves the data (fileContent) for the current case
        std::ofstream out(tempFilename);
        out << GetParam().fileContent;
        out.close();
    }

    // Runs after each test
    void TearDown() override { std::remove(tempFilename.c_str()); }
};

TEST_P(FileIOTest, ProcessesSwitchedMoves) {
    int result = solve_part_two(tempFilename);

    EXPECT_EQ(result, GetParam().expectedResult);
}

INSTANTIATE_TEST_SUITE_P(MoveSwitchTests, // Group name
                         FileIOTest,      // Fixture class name
                         ::testing::Values(
                             // Scenario 1: L50 then R50
                             MoveTestCase{"L50\nR50", 1},
                             // Scenario 2: R50 then L50 (the switched case)
                             MoveTestCase{
                                 "R50\nL50",
                                 1 // <-- Expected result for R50 then L50
                             },
                             MoveTestCase{
                                 "R50\nL50\nL200",
                                 3 // <-- Expected result for R50 then L50
                             },
                             MoveTestCase{"R1000", 10}, MoveTestCase{"L1000", 10},
                             MoveTestCase{"L68\nL30\nR48\nL5\nR60\nL55\nL1\nL99\nR14\nL82", 6}));
