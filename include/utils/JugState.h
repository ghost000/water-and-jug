#pragma once
#include <vector>
#include <string>
#include <functional>

// Represents the state of the water jugs and the steps taken to reach this state
struct JugState {
    std::vector<int> jugs; // Amount of water in each jug
    std::string steps;     // Steps taken to reach this state

    // Comparison operator to check if two JugState objects are equal
    bool operator==(const JugState& other) const {
        return jugs == other.jugs;
    }
};

// Hash function for JugState to allow its use in unordered containers (e.g., unordered_set, unordered_map)
struct JugStateHash {

    // Generates a hash value for a given JugState
    size_t operator()(const JugState& state) const {

        size_t hashValue = 0;
        std::hash<int> hasher;

        // Combine hashes using a more advanced approach to avoid collisions
        for (int jug : state.jugs) {
            hashValue ^= hasher(jug) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
        }
        return hashValue;
    }
};