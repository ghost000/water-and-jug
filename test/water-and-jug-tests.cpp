#include <gtest/gtest.h>
#include "../include/water-and-jug.h"

// Prosty test do przykładowej funkcji z water-and-jug.h
//TEST(WaterAndJugTest, BasicTest) {
//    // Zakładając, że masz funkcję np. solveJugProblem w water-and-jug.h
//    int result = solveJugProblem(3, 6, 10, 4);  // Przykładowe wywołanie funkcji
//    EXPECT_EQ(result, 1);  // Sprawdzamy czy funkcja zwróciła oczekiwany wynik
//}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}