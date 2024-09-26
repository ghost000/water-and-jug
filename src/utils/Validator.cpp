#include "utils/Validator.h"
#include <stdexcept>
#include <numeric>
#include <algorithm>

// Validates if the capacities of the jugs are positive and non-empty
void Validator::validateJugs(const std::vector<int>& capacities) {
    // Ensure at least one jug is provided
    if (capacities.empty()) {
        throw std::invalid_argument("At least one jug is required.");
    }
    // Ensure all jug capacities are positive
    for (int capacity : capacities) {
        if (capacity <= 0) {
            throw std::invalid_argument("Jug capacities must be positive.");
        }
    }
}

// Determines if the target amount of water can be reached with the given jugs
bool Validator::canReachTarget(int target, const std::vector<int>& capacities) {
    // Target must be positive to be achievable
    if (target <= 0) {
        return false;
    }

    // Compute the greatest common divisor (GCD) of all jug capacities
    int gcd_of_jugs = std::reduce(capacities.begin(), capacities.end(), capacities[0], std::gcd<int, int>);
    // If the target is not divisible by the GCD, it is not reachable
    if (target % gcd_of_jugs != 0) {
        return false;
    }

    // Ensure the target does not exceed the total capacity of all jugs
    if (target > std::accumulate(capacities.begin(), capacities.end(), 0)) {
        return false;
    }

    // If all conditions are met, the target is achievable
    return true;
}
