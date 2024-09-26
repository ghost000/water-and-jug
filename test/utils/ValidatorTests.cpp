#include "utils/Validator.h"
#include <gtest/gtest.h>
#include <stdexcept>

class ValidatorTest : public ::testing::Test {
protected:
    std::vector<int> validCapacities = { 3, 6, 10 };
};

// Test valid jug capacities
TEST_F(ValidatorTest, ValidateJugsValid) {
    EXPECT_NO_THROW(Validator::validateJugs(validCapacities));
}

// Test empty jug capacities
TEST_F(ValidatorTest, ValidateJugsEmpty) {
    std::vector<int> emptyCapacities = {};
    EXPECT_THROW(Validator::validateJugs(emptyCapacities), std::invalid_argument);
}

// Test negative jug capacity
TEST_F(ValidatorTest, ValidateJugsNegativeCapacity) {
    std::vector<int> negativeCapacity = { 3, -5, 10 };
    EXPECT_THROW(Validator::validateJugs(negativeCapacity), std::invalid_argument);
}

// Test zero jug capacity
TEST_F(ValidatorTest, ValidateJugsZeroCapacity) {
    std::vector<int> zeroCapacity = { 0, 6, 10 };
    EXPECT_THROW(Validator::validateJugs(zeroCapacity), std::invalid_argument);
}

// Test valid target for reachable case
TEST_F(ValidatorTest, CanReachTargetValid) {
    int target = 9;  // Should be reachable with 3, 6, 10
    EXPECT_TRUE(Validator::canReachTarget(target, validCapacities));
}

// Test invalid target exceeding total capacity
TEST_F(ValidatorTest, CanReachTargetExceedsTotalCapacity) {
    int target = 20;  // Total capacity is 19
    EXPECT_FALSE(Validator::canReachTarget(target, validCapacities));
}

// Test target that cannot be reached with GCD rule
TEST_F(ValidatorTest, CanReachTargetInvalidGCD) {
    std::vector<int> gcdInvalidCapacities = { 6, 9 };
    int target = 7;  // 7 cannot be achieved with 6 and 9
    EXPECT_FALSE(Validator::canReachTarget(target, gcdInvalidCapacities));
}

// Test invalid target below 1
TEST_F(ValidatorTest, CanReachTargetBelowMinimum) {
    int target = 0;
    EXPECT_FALSE(Validator::canReachTarget(target, validCapacities));
}
