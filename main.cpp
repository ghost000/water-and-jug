#include "include/BFSWaterJugSolver.h"
#include <iostream>
#include <vector>
#include <memory>

int main() {
    // Define capacities of the jugs (3L, 6L, 10L)
    std::vector<int> capacities = { 3, 6, 10 };

    // Initialize the solver
    std::unique_ptr<WaterJugSolver> solver = std::make_unique<BFSWaterJugSolver>();
    solver->setJugs(capacities);


    for (int target = 1; target <= 19; ++target) {
        std::vector<std::string> result = solver->solve(target);
        std::cout << "Target: " << target << "L\n";
        for (const auto& step : result) {
            std::cout << step << '\n';
        }
        std::cout << "--------------------------\n";
    }

    return 0;
}
