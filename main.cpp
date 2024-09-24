#include "HuffmanTree.h"
#include "utils.h"

int main()
{
  // File paths
  std::string inputFile = "input/input.txt";
  std::string encodedFile = "output/encoded.bin";
  std::string decodedFile = "output/decoded.txt";

  // Ensure output directory exists
  createDirectoryIfNotExists("output");

  // Calculate frequencies
  std::unordered_map<char, int> frequencies = calculateFrequencies(inputFile);
  if (frequencies.empty())
  {
    std::cerr << "Error: Input file is empty or not found." << std::endl;
    return 1;
  }

  // Build Huffman tree
  HuffmanTree huffmanTree;
  huffmanTree.build(frequencies);
  huffmanTree.generateCodes(huffmanTree.getRoot(), "");

  // Get codes
  std::unordered_map<char, std::string> codes = huffmanTree.getCodes();

  // Encode file
  encodeFile(inputFile, encodedFile, huffmanTree, codes);
  std::cout << "Encoding completed. Encoded data saved to " << encodedFile << std::endl;

  // Decode file
  decodeFile(encodedFile, decodedFile);
  std::cout << "Decoding completed. Decoded data saved to " << decodedFile << std::endl;

  // Verify
  if (compareFiles(inputFile, decodedFile))
  {
    std::cout << "Success: The original and decoded files are identical." << std::endl;
  }
  else
  {
    std::cout << "Warning: The original and decoded files differ." << std::endl;
  }

  return 0;
}
