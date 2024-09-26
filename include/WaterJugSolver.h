#pragma once
#include <vector>
#include <string>

class WaterJugSolver {
public:
    virtual void setJugs(const std::vector<int>& newCapacities) = 0;
    virtual std::vector<std::string> solve(int targetAmount) const = 0;
    virtual ~WaterJugSolver() = default;
};
