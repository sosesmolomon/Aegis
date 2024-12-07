# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and set C++ standard
project(Aegis)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Add source files and headers for the engine

set (SOURCES
    src/main.cpp
    src/bitboard.cpp
    src/CBoard.cpp
    src/engine.cpp
    src/evaluate.cpp
    src/magic.cpp
    src/move.cpp
    src/moveGen.cpp
    src/MoveList.cpp
    src/print.cpp
    src/utils.cpp

)

set (TEST_SOURCES
    src/bitboard.cpp
    src/CBoard.cpp
    src/engine.cpp
    src/evaluate.cpp
    src/magic.cpp
    src/move.cpp
    src/moveGen.cpp
    src/MoveList.cpp
    src/print.cpp
    src/utils.cpp
)



set(Headers
    src/bitboard.h
    src/CBoard.h
    src/engine.h
    src/evaluate.h
    src/magic.h
    src/move.h
    src/MoveList.h
    src/print.h
    src/utils.h
)

# Add an executable for the chess engine (main program)
add_executable(Aegis ${SOURCES} ${HEADERS})

include(FetchContent)

FetchContent_Declare(
    googletest

    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
# Make Google Test available
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Add test sources (for the tests you are writing, like test_CBoard.cpp)
set(TEST_FILES
    tests/test_CBoard.cpp
    tests/test_MoveGen.cpp
    tests/test_Methods.cpp
)

# Create a test executable for running the tests. $TEST_SOURCES EXCLUDES main.cpp
add_executable(AegisTests ${TEST_FILES} ${TEST_SOURCES} ${HEADERS})




# Link Google Test with the test executable
target_link_libraries(AegisTests gtest gtest_main)

# Add the tests to CMake's test infrastructure
add_test(NAME AegisTests COMMAND AegisTests)