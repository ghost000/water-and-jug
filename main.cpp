#include "include/BFSWaterJugSolver.h"
#include <iostream>
#include <vector>

int main() {
    // Define capacities of the jugs (3L, 6L, 10L)
    std::vector<int> capacities = { 3, 6, 10 };
    int target;

    std::cout << "Enter the target amount of water (1-19): ";
    std::cin >> target;

    // Initialize the solver
    BFSWaterJugSolver solver;
    solver.setJugs(capacities);

    // Find solution
    std::vector<std::string> result = solver.solve(target);

    // Output the solution steps
    if (!result.empty()) {
        for (const auto& step : result) {
            std::cout << step << std::endl;
        }
    }
    else {
        std::cout << "No solution found or target is unreachable." << std::endl;
    }

    return 0;
}
