#pragma once
#include <vector>

class Validator {
public:
    static void validateJugs(const std::vector<int>& capacities);
    static bool canReachTarget(int target, const std::vector<int>& capacities);
};