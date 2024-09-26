#include "WaterJugSolver.h"
#include "utils/JugState.h"
#include <queue>
#include <unordered_set>
 
class BFSWaterJugSolver : public WaterJugSolver {
public:
    void setJugs(const std::vector<int>& newCapacities) override;
    std::vector<std::string> solve(int targetAmount) const override;
private:
    std::vector<int> capacities;

    bool isTargetAchieved(const JugState& state, int targetAmount) const;
    JugState createFillState(const JugState& currentState, size_t jugIndex) const;
    JugState createEmptyState(const JugState& currentState, size_t jugIndex) const;
    JugState createPourState(const JugState& currentState, size_t fromJug, size_t toJug) const;
    std::vector<JugState> generatePossibleNextStates(const JugState& currentState) const;
    void addNewStateToQueue(std::queue<JugState>& stateQueue, std::unordered_set<JugState, JugStateHash>& visitedStates, const JugState& newState) const;
};