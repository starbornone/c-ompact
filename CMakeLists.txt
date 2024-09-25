cmake_minimum_required(VERSION 3.10)
project(cppompact VERSION 1.0 LANGUAGES CXX)

# =========================
# Configuration Options
# =========================

# Set the C++ standard to C++17 and enforce it
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# =========================
# Organize Source Files
# =========================

# List of source files for the library
set(CPPO_COMPACT_SOURCES
    src/ArgumentParser.cpp
    src/FileUtils.cpp
    src/Handler.cpp
    src/HuffmanTree.cpp
    src/FrequencyUtils.cpp
    src/FileComparisonUtils.cpp
    src/HuffmanSerializer.cpp
    src/HuffmanCodeGenerator.cpp
    src/Node.cpp
    src/EncodeFile.cpp         # Added
    src/DecodeFile.cpp         # Added
)

# List of header files (optional, useful for IDEs)
set(CPPO_COMPACT_HEADERS
    include/ArgumentParser.h
    include/EncodeFile.h        # Added
    include/DecodeFile.h        # Added
    include/FileUtils.h
    include/Handler.h
    include/HuffmanTree.h
    include/FrequencyUtils.h
    include/FileComparisonUtils.h
    include/HuffmanSerializer.h
    include/HuffmanCodeGenerator.h
    include/Node.h
)

# =========================
# Create the Library
# =========================

add_library(cppompact_lib
    ${CPPO_COMPACT_SOURCES}
    ${CPPO_COMPACT_HEADERS} # Optional: Helps IDEs recognize headers
)

# Specify include directories for the library
target_include_directories(cppompact_lib
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

# Optionally, set library properties (e.g., compile options)
# target_compile_options(cppompact_lib PRIVATE -Wall -Wextra)

# =========================
# Create the Main Executable
# =========================

add_executable(cppompact src/main.cpp)

# Link the library to the executable
target_link_libraries(cppompact
    PRIVATE
        cppompact_lib
)

# =========================
# Testing Setup
# =========================

# Enable testing
enable_testing()

# Add GoogleTest (assuming it's added as a submodule in the 'googletest' directory)
add_subdirectory(googletest)

# Create the test executable
add_executable(cppompact_tests tests/test_huffman.cpp)

# Link the library and GoogleTest libraries to the test executable
target_link_libraries(cppompact_tests
    PRIVATE
        cppompact_lib
        gtest
        gtest_main
)

# Define a test
add_test(NAME cppompact_tests
    COMMAND cppompact_tests
)

# Optionally, group tests in the IDE
set_target_properties(cppompact_tests PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
