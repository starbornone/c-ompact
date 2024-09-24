#include "gtest/gtest.h"
#include "../include/HuffmanTree.h"
#include "../include/FileUtils.h"
#include "../include/EncodeDecodeUtils.h"
#include "../include/FrequencyUtils.h"
#include "../include/FileComparisonUtils.h"
#include "../include/HuffmanCodeGenerator.h"
#include <fstream>

TEST(HuffmanTreeTest, BasicFunctionality)
{
  // Step 1: Define character frequencies
  std::unordered_map<char, int> freqs = {
      {'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}, {'e', 16}, {'f', 45}};

  // Step 2: Build the Huffman Tree using the frequencies
  HuffmanTree tree;
  tree.build(freqs);

  // Step 3: Use HuffmanCodeGenerator to generate Huffman codes for each character
  HuffmanCodeGenerator codeGenerator;
  std::unordered_map<char, std::string> codes;
  codeGenerator.generateCodes(tree.getRoot(), "", codes);

  // Step 4: Verify that the codes are generated correctly
  EXPECT_GT(codes.size(), 0);
  EXPECT_EQ(codes['f'], "0");    // 'f' should have the shortest code in the tree
  EXPECT_EQ(codes['a'], "1100"); // Adjust these based on the actual generated codes
}

TEST(UtilsTest, EncodeFile)
{
  // Step 1: Define character frequencies for the test input
  std::unordered_map<char, int> freqs = {
      {'a', 3}, {'b', 2}, {'c', 1}};

  // Step 2: Build the Huffman Tree using these frequencies
  HuffmanTree tree;
  tree.build(freqs);

  // Step 3: Generate Huffman codes using HuffmanCodeGenerator
  HuffmanCodeGenerator codeGenerator;
  std::unordered_map<char, std::string> codes;
  codeGenerator.generateCodes(tree.getRoot(), "", codes);

  // Step 4: Ensure that necessary directories exist for the test files
  createDirectoryIfNotExists("tests");
  createDirectoryIfNotExists("output");

  // Step 5: Specify paths for the input and encoded files
  std::string input = "tests/sample_input.txt";
  std::string encoded = "output/sample_encoded.bin";

  // Step 6: Create and write the sample content to the input file
  std::ofstream out(input);
  if (!out.is_open())
  {
    std::cerr << "Error creating input file: " << input << std::endl;
    FAIL() << "Failed to create input file for test.";
  }
  out << "abc"; // Writing test content "abc" to the input file
  out.close();

  // Step 7: Encode the input file using the Huffman codes generated earlier
  encodeFile(input, encoded, tree, codes);

  // Step 8: Verify that the encoded file was created successfully
  std::ifstream encodedFile(encoded);
  EXPECT_TRUE(encodedFile.good()) << "Encoded file not created: " << encoded;
  encodedFile.close();
}

TEST(UtilsTest, DecodeFile)
{
  // Step 1: Define character frequencies for the test input
  std::unordered_map<char, int> freqs = {
      {'a', 3}, {'b', 2}, {'c', 1}};

  // Step 2: Build the Huffman Tree using these frequencies
  HuffmanTree tree;
  tree.build(freqs);

  // Step 3: Generate Huffman codes using HuffmanCodeGenerator
  HuffmanCodeGenerator codeGenerator;
  std::unordered_map<char, std::string> codes;
  codeGenerator.generateCodes(tree.getRoot(), "", codes);

  // Step 4: Ensure that necessary directories exist for the test files
  createDirectoryIfNotExists("tests");
  createDirectoryIfNotExists("output");

  // Step 5: Specify paths for the input, encoded, and decoded files
  std::string input = "tests/sample_input.txt";
  std::string encoded = "output/sample_encoded.bin";
  std::string decoded = "output/sample_decoded.txt";

  // Step 6: Create and write the sample content to the input file
  std::ofstream out(input);
  if (!out.is_open())
  {
    std::cerr << "Error creating input file: " << input << std::endl;
    FAIL() << "Failed to create input file for test.";
  }
  out << "abc"; // Writing test content "abc" to the input file
  out.close();

  // Step 7: Encode the input file and generate the encoded output file
  encodeFile(input, encoded, tree, codes);

  // Step 8: Decode the encoded file back to its original form
  decodeFile(encoded, decoded);

  // Step 9: Verify that the decoded file matches the original input file
  EXPECT_TRUE(compareFiles(input, decoded)) << "Decoded file does not match the original: " << decoded;
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
