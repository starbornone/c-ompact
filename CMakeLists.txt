cmake_minimum_required(VERSION 3.10)
project(cppompact)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Add Google Test subdirectory
add_subdirectory(googletest)

# Add the main executable
add_executable(cppompact main.cpp src/HuffmanTree.cpp src/utils.cpp)

# Link Google Test libraries
target_link_libraries(cppompact gtest gtest_main)

# Create a test executable
add_executable(cppompact_tests tests/test_huffman.cpp src/HuffmanTree.cpp src/utils.cpp)

# Link Google Test libraries to the test executable
target_link_libraries(cppompact_tests gtest gtest_main)

# Enable testing
enable_testing()

# Add a test for the executable
add_test(NAME cppompact_tests COMMAND cppompact_tests)
