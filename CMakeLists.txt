# Minimalna wersja CMake
cmake_minimum_required(VERSION 3.8)

# Włącz przeładowywanie kodu XAML na gorąco dla kompilatorów MSVC
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Projekt
project("water-and-jug")

# Pobieranie GoogleTest za pomocą FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Dodaj główny plik wykonywalny projektu (bez testów)
add_executable(water-and-jug "src/water-and-jug.cpp" "include/water-and-jug.h")

# Ustawienie standardu C++ na 20
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET water-and-jug PROPERTY CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
endif()

# Umożliwienie testowania
enable_testing()
include(GoogleTest)

# Dodaj plik wykonywalny dla testów
add_executable(water-and-jug-tests test/water-and-jug-tests.cpp)

# Dodanie include dla GoogleTest
target_include_directories(water-and-jug-tests PRIVATE ${gtest_SOURCE_DIR}/include)

# Linkowanie testów z GoogleTest
target_link_libraries(water-and-jug-tests GTest::gtest GTest::gtest_main)

# Dodanie testów do CMake
add_test(NAME water_and_jug_tests COMMAND water-and-jug-tests)

# Automatyczne odkrywanie testów
gtest_discover_tests(water-and-jug-tests)
