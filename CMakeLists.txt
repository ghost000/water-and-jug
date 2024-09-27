# Minimum required version of CMake to ensure compatibility with modern features
cmake_minimum_required(VERSION 3.8)

# Enable hot-reloading for XAML code when using MSVC compilers
# This setting allows faster development iterations by preserving debugging information
# when reloading code during development. It helps especially with Edit and Continue functionality.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT 
      "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>"
  )
endif()

# Define the project name and type (C++ project)
project("water-and-jug")

# Fetch GoogleTest using FetchContent
# GoogleTest is required for unit testing. Using FetchContent ensures that we always 
# download and use a specific version of GoogleTest (1.15.2 in this case) to maintain consistency across environments.
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)

# Force GoogleTest to use the same runtime as the rest of the project
# This avoids issues when linking with different runtime libraries (static vs dynamic)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Make GoogleTest available for this project
FetchContent_MakeAvailable(googletest)

# Enable unit testing support
# This sets up testing using CMake’s testing infrastructure, which integrates well with GoogleTest.
enable_testing()

# Create the main project executable (excluding test files)
# This includes both the solver logic (BFSWaterJugSolver) and validation (Validator) functionality.
# 'main.cpp' is the entry point for the application.
add_executable(water-and-jug
  "include/WaterJugSolver.h"
  "include/BFSWaterJugSolver.h"
  "src/BFSWaterJugSolver.cpp"
  "main.cpp"
  "include/utils/Validator.h"
  "src/utils/Validator.cpp"
  "include/utils/JugState.h"
)

# Assuming your source files are in src/ and your headers are in include/
target_include_directories(water-and-jug PRIVATE "${CMAKE_SOURCE_DIR}/include")

# Set the C++ standard to C++20, ensuring access to modern features like concepts and ranges
# We set this property explicitly to avoid compilation issues on systems where the default is C++14 or older.
set_property(TARGET water-and-jug PROPERTY CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)  # Ensures that the project does not fall back to an older standard

# Include GoogleTest's integration with CMake
include(GoogleTest)

# Add the test executable for validating the 'Validator' class
# This is a separate executable that runs unit tests on the validation logic in isolation.
add_executable(ValidatorTests 
  "test/utils/ValidatorTests.cpp"
  "src/utils/Validator.cpp"
  "include/utils/JugState.h"
)

# Assuming your source files are in src/ and your headers are in include/
target_include_directories(ValidatorTests PRIVATE "${CMAKE_SOURCE_DIR}/include")

# Add the test executable for the BFS-based water jug solver
# These tests will check the core solving algorithm.
add_executable(BFSWaterJugSolverTests 
  "test/BFSWaterJugSolverTests.cpp"
  "src/BFSWaterJugSolver.cpp"
  "src/utils/Validator.cpp"
  "include/utils/JugState.h"
)

# Assuming your source files are in src/ and your headers are in include/
target_include_directories(BFSWaterJugSolverTests PRIVATE "${CMAKE_SOURCE_DIR}/include")

# Ensure both test executables can include GoogleTest's headers
# We explicitly tell the targets where GoogleTest's include files are located.
target_include_directories(ValidatorTests PRIVATE ${gtest_SOURCE_DIR}/include)
target_include_directories(BFSWaterJugSolverTests PRIVATE ${gtest_SOURCE_DIR}/include)

# Link the test executables with GoogleTest libraries
# GoogleTest provides both a testing framework and a main function to run tests.
# Linking with 'GTest::gtest' and 'GTest::gtest_main' ensures that the GoogleTest runner is used.
target_link_libraries(ValidatorTests GTest::gtest GTest::gtest_main)
target_link_libraries(BFSWaterJugSolverTests GTest::gtest GTest::gtest_main)

# Register the test executables with CMake
# The 'add_test' command makes CTest aware of the test executables.
# We provide names that correspond to the functionality being tested.
add_test(NAME ValidatorTests COMMAND ValidatorTests)
add_test(NAME BFSWaterJugSolverTests COMMAND BFSWaterJugSolverTests)

# Automatically discover and register the tests within the executables
# 'gtest_discover_tests' will inspect the code for TEST macros and automatically register them with CTest.
# This ensures new tests are automatically added to the testing pipeline without needing manual updates here.
gtest_discover_tests(ValidatorTests)
gtest_discover_tests(BFSWaterJugSolverTests)

# Improvements or additional steps:
# - We could add sanitizers (e.g., AddressSanitizer, UndefinedBehaviorSanitizer) to catch runtime bugs during development.
# - It might be beneficial to set up different build configurations (e.g., Release, Debug) with tailored flags for each.