cmake_minimum_required(VERSION 3.10)
project(cppompact)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Add the main executable with all required source files
add_executable(
    cppompact
    src/main.cpp 
    src/ArgumentParser.cpp 
    src/FileUtils.cpp 
    src/Handler.cpp 
    src/HuffmanTree.cpp 
    src/EncodeDecodeUtils.cpp 
    src/FrequencyUtils.cpp 
    src/FileComparisonUtils.cpp
    src/HuffmanSerializer.cpp
    src/HuffmanCodeGenerator.cpp  # Include the new file
    src/Node.cpp                  # Include the new file
)

# Add Google Test subdirectory
add_subdirectory(googletest)

# Create a test executable with all required source files
add_executable(
    cppompact_tests
    tests/test_huffman.cpp 
    src/ArgumentParser.cpp 
    src/FileUtils.cpp 
    src/Handler.cpp 
    src/HuffmanTree.cpp 
    src/EncodeDecodeUtils.cpp 
    src/FrequencyUtils.cpp 
    src/FileComparisonUtils.cpp
    src/HuffmanSerializer.cpp
    src/HuffmanCodeGenerator.cpp  # Include the new file
    src/Node.cpp                  # Include the new file
)

# Link Google Test libraries to the test executable
target_link_libraries(cppompact_tests gtest gtest_main)

# Enable testing
enable_testing()

# Add a test for the executable
add_test(NAME cppompact_tests COMMAND cppompact_tests)
