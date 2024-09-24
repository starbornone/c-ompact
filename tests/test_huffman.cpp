#include "gtest/gtest.h"
#include "../include/HuffmanTree.h"
#include "../include/utils.h"
#include <filesystem>
#include <fstream>

// Test case for basic Huffman Tree functionality
// This test checks if the Huffman Tree correctly generates Huffman codes for a set of given character frequencies.
TEST(HuffmanTreeTest, BasicFunctionality)
{
  // Step 1: Define character frequencies
  // These frequencies determine how the Huffman Tree is built. Higher frequency characters get shorter codes.
  std::unordered_map<char, int> freqs = {
      {'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}, {'e', 16}, {'f', 45}};

  // Step 2: Build the Huffman Tree using the frequencies
  HuffmanTree tree;
  tree.build(freqs);

  // Step 3: Generate Huffman codes for each character
  tree.generateCodes(tree.getRoot(), "");

  // Step 4: Retrieve the generated codes from the tree
  std::unordered_map<char, std::string> codes = tree.getCodes();

  // Verify that the codes are generated (there should be more than zero codes)
  EXPECT_GT(codes.size(), 0);

  // Check specific Huffman codes for correctness (these values are implementation-specific and may vary)
  // The character 'f' is expected to have the shortest code because it has the highest frequency.
  EXPECT_EQ(codes['f'], "0");    // 'f' should have the shortest code in the tree
  EXPECT_EQ(codes['a'], "1100"); // Adjust these based on the actual generated codes
}

// Test case for file encoding functionality
// This test verifies that the encodeFile function correctly encodes a text file using Huffman coding.
TEST(UtilsTest, EncodeFile)
{
  // Step 1: Define character frequencies for the test input
  std::unordered_map<char, int> freqs = {
      {'a', 3}, {'b', 2}, {'c', 1}};

  // Step 2: Build the Huffman Tree using these frequencies
  HuffmanTree tree;
  tree.build(freqs);

  // Step 3: Generate Huffman codes for each character in the tree
  tree.generateCodes(tree.getRoot(), "");
  std::unordered_map<char, std::string> codes = tree.getCodes();

  // Step 4: Ensure that necessary directories exist for the test files
  createDirectoryIfNotExists("tests");  // Directory for input files
  createDirectoryIfNotExists("output"); // Directory for output files

  // Step 5: Specify paths for the input and encoded files
  std::string input = "tests/sample_input.txt";      // Input file to be encoded
  std::string encoded = "output/sample_encoded.bin"; // Encoded output file

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

// Test case for file decoding functionality
// This test checks if the decodeFile function correctly decodes a previously encoded file, restoring the original content.
TEST(UtilsTest, DecodeFile)
{
  // Step 1: Define character frequencies for the test input
  std::unordered_map<char, int> freqs = {
      {'a', 3}, {'b', 2}, {'c', 1}};

  // Step 2: Build the Huffman Tree using these frequencies
  HuffmanTree tree;
  tree.build(freqs);

  // Step 3: Generate Huffman codes for each character in the tree
  tree.generateCodes(tree.getRoot(), "");
  std::unordered_map<char, std::string> codes = tree.getCodes();

  // Step 4: Ensure that necessary directories exist for the test files
  createDirectoryIfNotExists("tests");  // Directory for input files
  createDirectoryIfNotExists("output"); // Directory for output files

  // Step 5: Specify paths for the input, encoded, and decoded files
  std::string input = "tests/sample_input.txt";      // Input file to be encoded
  std::string encoded = "output/sample_encoded.bin"; // Encoded output file
  std::string decoded = "output/sample_decoded.txt"; // Decoded output file (to be compared with the input)

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

// Main function to run all the test cases defined above
int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}