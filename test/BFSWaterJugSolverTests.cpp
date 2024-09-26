#include "BFSWaterJugSolver.h"
#include "utils/Validator.h"

#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>

// Test fixture for BFSWaterJugSolver
class BFSWaterJugSolverTest : public ::testing::Test {
protected:
    BFSWaterJugSolver solver;
    std::vector<int> validCapacities = { 3, 6, 10 };

    void SetUp() override {
        solver.setJugs(validCapacities);
    }
};

// Test solver for an easy solution
TEST_F(BFSWaterJugSolverTest, SolveEasySolution) {
    int target = 3;
    std::vector<std::string> result = solver.solve(target);
    ASSERT_FALSE(result.empty());
    EXPECT_NE(result[0].find("Fill jug 0"), std::string::npos); // Checking expected step
}

// Test solver for a more complex solution
TEST_F(BFSWaterJugSolverTest, SolveComplexSolution) {
    int target = 7;
    std::vector<std::string> result = solver.solve(target);
    ASSERT_FALSE(result.empty());
    EXPECT_NE(result[0].find("Pour 3L from jug"), std::string::npos); // Verify pouring step
}

// Test solver for a solution with all jugs needed
TEST_F(BFSWaterJugSolverTest, SolveWithAllJugs) {
    int target = 6;
    std::vector<std::string> result = solver.solve(target);
    ASSERT_FALSE(result.empty());
    EXPECT_NE(result[0].find("Fill jug 1"), std::string::npos);
}

// Test solver when the target exceeds total capacity
TEST_F(BFSWaterJugSolverTest, SolveTargetExceedsTotalCapacity) {
    int target = 20;  // Greater than the total capacity of all jugs (3 + 6 + 10)
    std::vector<std::string> result = solver.solve(target);
    ASSERT_EQ(result[0], "Target cannot be reached with the given jug capacities.");
}

// Test an unreachable but valid target
TEST_F(BFSWaterJugSolverTest, NoSolution) {
    int target = 19;  // Very large target, should have solution
    std::vector<std::string> result = solver.solve(target);
    ASSERT_FALSE(result.empty());
}

// Test solver handling large number of states (abort condition)
//TEST_F(BFSWaterJugSolverTest, SolveTooManyStates) {
//    std::vector<int> hugeJugs = { 999999, 1000000 }; // Unrealistically large jugs to test space limitation
//    solver.setJugs(hugeJugs);
//    int target = 1;
//    std::vector<std::string> result = solver.solve(target);
//    ASSERT_EQ(result[0], "Solution space too large, aborting...");
//}

// Test edge case with no solution
TEST_F(BFSWaterJugSolverTest, NoSolutionForImpossibleTarget) {
    int target = 11; // Impossible to get 11L with jugs 3, 6, 10
    std::vector<std::string> result = solver.solve(target);
    ASSERT_EQ(result[0], "No solution found");
}

// Test for correct exception when invalid jug capacities are set
TEST(BFSWaterJugSolverExceptionTest, InvalidJugCapacity) {
    BFSWaterJugSolver solver;
    std::vector<int> invalidCapacities = { 3, -6, 10 };
    EXPECT_THROW(solver.setJugs(invalidCapacities), std::invalid_argument);
}

// Test for exception when no jugs are provided
TEST(BFSWaterJugSolverExceptionTest, NoJugCapacityProvided) {
    BFSWaterJugSolver solver;
    std::vector<int> emptyJugs;
    EXPECT_THROW(solver.setJugs(emptyJugs), std::invalid_argument);
}

// Test that solver initializes and solves correctly with minimal valid input
TEST(BFSWaterJugSolverMinimalTest, SolveMinimalInput) {
    BFSWaterJugSolver solver;
    std::vector<int> minimalCapacities = { 1 };
    solver.setJugs(minimalCapacities);
    int target = 1;
    std::vector<std::string> result = solver.solve(target);
    ASSERT_FALSE(result.empty());
    EXPECT_NE(result[0].find("Fill jug 0"), std::string::npos);
}
