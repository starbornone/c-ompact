cmake_minimum_required(VERSION 3.10)
project(cppompact)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Source files for the main executable
set(SOURCES
    main.cpp
    src/HuffmanTree.cpp
    src/utils.cpp
)

# Source files for the test executable
set(TEST_SOURCES
    tests/test_huffman.cpp
    src/HuffmanTree.cpp
    src/utils.cpp
)

# Add Google Test subdirectory
add_subdirectory(googletest)

# Add the main executable
add_executable(cppompact ${SOURCES})

# Link Google Test libraries to the main executable (optional if you need GTest in main)
target_link_libraries(cppompact gtest gtest_main)

# Add the test executable
add_executable(cppompact_tests ${TEST_SOURCES})

# Link Google Test libraries to the test executable
target_link_libraries(cppompact_tests gtest gtest_main)

# Ensure include directories are set for both executables
target_include_directories(cppompact PRIVATE include)
target_include_directories(cppompact_tests PRIVATE include)

# Enable testing
enable_testing()

# Add a test for the test executable
add_test(NAME cppompact_tests COMMAND cppompact_tests)
