#include "BFSWaterJugSolver.h"
#include "utils/Validator.h"
#include <queue>
#include <format>
#include <ranges>
#include <algorithm>
#include <numeric>

// Set jug capacities after validating them
void BFSWaterJugSolver::setJugs(const std::vector<int>& newCapacities) {
    Validator::validateJugs(newCapacities);
    capacities = newCapacities;
}

// Check if any jug in the current state contains the target amount of water
bool BFSWaterJugSolver::isTargetAchieved(const JugState& state, int targetAmount) const {
    // Check if we have exactly target in one of the jugs
    if (std::ranges::any_of(state.jugs, [targetAmount](int water) { return water == targetAmount; })) {
        return true;
    }

    // Check if the sum of water in several jugs gives the target
    int totalWater = std::accumulate(state.jugs.begin(), state.jugs.end(), 0);
    return totalWater == targetAmount;

}

// Create a state where a jug is filled to its maximum capacity
JugState BFSWaterJugSolver::createFillState(const JugState& currentState, size_t jugIndex) const {
    JugState filledState = currentState;
    filledState.jugs[jugIndex] = capacities[jugIndex]; // Fill the jug to its max capacity
    filledState.steps += std::format("\nFill jug {} ({}L)", jugIndex+1, capacities[jugIndex]);
    return filledState;
}

// Create a state where a jug is emptied
JugState BFSWaterJugSolver::createEmptyState(const JugState& currentState, size_t jugIndex) const {
    JugState emptiedState = currentState;
    emptiedState.jugs[jugIndex] = 0; // Empty the jug
    emptiedState.steps += std::format("\nEmpty jug {}", jugIndex+1);
    return emptiedState;
}

// Create a state where water is poured from one jug to another
JugState BFSWaterJugSolver::createPourState(const JugState& currentState, size_t fromJug, size_t toJug) const {
    JugState pouredState = currentState;
    int pourAmount = std::min(currentState.jugs[fromJug], capacities[toJug] - currentState.jugs[toJug]); // Max amount that can be poured
    pouredState.jugs[fromJug] -= pourAmount;
    pouredState.jugs[toJug] += pourAmount;
    pouredState.steps += std::format("\nPour {}L from jug {} to jug {}", pourAmount, fromJug+1, toJug+1);
    return pouredState;
}

// Generate all possible next states by filling, emptying, or pouring water between jugs
std::vector<JugState> BFSWaterJugSolver::generatePossibleNextStates(const JugState& currentState) const {
    std::vector<JugState> nextStates;

    // Loop through each jug and generate possible states
    for (size_t jugIndex = 0; jugIndex < capacities.size(); ++jugIndex) {
        // If the jug is not full, generate the state where it is filled
        if (currentState.jugs[jugIndex] < capacities[jugIndex]) {
            nextStates.push_back(createFillState(currentState, jugIndex));
        }

        // If the jug contains water, generate the state where it is emptied
        if (currentState.jugs[jugIndex] > 0) {
            nextStates.push_back(createEmptyState(currentState, jugIndex));
        }

        // Try pouring water between every pair of jugs
        for (size_t targetJugIndex = 0; targetJugIndex < capacities.size(); ++targetJugIndex) {
            if (jugIndex != targetJugIndex && currentState.jugs[jugIndex] > 0 && currentState.jugs[targetJugIndex] < capacities[targetJugIndex]) {
                nextStates.push_back(createPourState(currentState, jugIndex, targetJugIndex));
            }
        }
    }

    return nextStates;
}

// Add a new state to the queue if it hasn't been visited yet
void BFSWaterJugSolver::addNewStateToQueue(std::queue<JugState>& stateQueue, std::unordered_set<JugState, JugStateHash>& visitedStates, const JugState& newState) const {
    if (visitedStates.find(newState) == visitedStates.end()) {
        visitedStates.insert(newState);
        stateQueue.push(newState);
    }
}

// Solve the water jug problem using BFS and return the steps to reach the target amount of water
std::vector<std::string> BFSWaterJugSolver::solve(int targetAmount) const {
    // Validate if the target can be reached with the given jug capacities
    if (!Validator::canReachTarget(targetAmount, capacities)) {
        return { "Target cannot be reached with the given jug capacities." };
    }
    // Initialize visited states and BFS queue
    std::unordered_set<JugState, JugStateHash> visitedStates;
    std::queue<JugState> stateQueue;

    // Starting state: All jugs are empty
    JugState initialState{ std::vector<int>(capacities.size(), 0), "Start" };
    stateQueue.push(initialState);
    visitedStates.insert(initialState);

    constexpr size_t MAX_VISITED_STATES = 1000; // Limit to avoid infinite search

    // BFS search loop
    while (!stateQueue.empty()) {
        JugState currentState = stateQueue.front();
        stateQueue.pop();

        // Check if the current state achieves the target
        if (isTargetAchieved(currentState, targetAmount)) {
            return std::vector<std::string>{currentState.steps};
        }

        // Stop if too many states are visited to prevent an unbounded search
        if (visitedStates.size() > MAX_VISITED_STATES) {
            return { "Solution space too large, aborting..." };
        }

        // Generate possible next states and add them to the queue if not visited
        std::vector<JugState> nextStates = generatePossibleNextStates(currentState);
        for (const auto& nextState : nextStates) {
            addNewStateToQueue(stateQueue, visitedStates, nextState);
        }
    }

    return { "No solution found" };
}
