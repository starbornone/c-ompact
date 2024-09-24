#include "include/HuffmanTree.h"
#include "include/utils.h"
#include <iostream>      // For standard I/O operations
#include <string>        // For std::string operations
#include <unordered_map> // For character frequency storage

// Function to display usage information
void printUsage()
{
  std::cout << "Usage: cppompact [options]\n"
            << "Options:\n"
            << "  --encode -e <input> <output>  Encode the input file to the output file.\n"
            << "  --decode -d <input> <output>  Decode the input file to the output file.\n"
            << "  --help   -h                   Show this help message.\n";
}

int main(int argc, char *argv[])
{
  // Check if the user has provided the minimum number of arguments
  if (argc < 2)
  {
    std::cerr << "Error: Missing arguments.\n";
    printUsage();
    return 1;
  }

  // Parse command-line arguments
  std::string mode;
  std::string inputFile;
  std::string outputFile;

  for (int i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];

    if (arg == "--encode" || arg == "-e")
    {
      if (i + 2 >= argc)
      {
        std::cerr << "Error: Missing input or output file for encoding.\n";
        printUsage();
        return 1;
      }
      mode = "encode";
      inputFile = argv[++i];
      outputFile = argv[++i];
    }
    else if (arg == "--decode" || arg == "-d")
    {
      if (i + 2 >= argc)
      {
        std::cerr << "Error: Missing input or output file for decoding.\n";
        printUsage();
        return 1;
      }
      mode = "decode";
      inputFile = argv[++i];
      outputFile = argv[++i];
    }
    else if (arg == "--help" || arg == "-h")
    {
      printUsage();
      return 0;
    }
    else
    {
      std::cerr << "Error: Unknown option: " << arg << "\n";
      printUsage();
      return 1;
    }
  }

  // Ensure the mode is set (either encoding or decoding)
  if (mode.empty())
  {
    std::cerr << "Error: No operation mode specified.\n";
    printUsage();
    return 1;
  }

  // Ensure the output directory exists
  createDirectoryIfNotExists("output");

  // Perform the selected operation
  if (mode == "encode")
  {
    // Calculate character frequencies from the input file
    std::unordered_map<char, int> frequencies = calculateFrequencies(inputFile);
    if (frequencies.empty())
    {
      std::cerr << "Error: Input file is empty or not found: " << inputFile << "\n";
      return 1;
    }

    // Build and generate Huffman codes
    HuffmanTree huffmanTree;
    huffmanTree.build(frequencies);
    huffmanTree.generateCodes(huffmanTree.getRoot(), "");

    // Retrieve the generated Huffman codes
    std::unordered_map<char, std::string> codes = huffmanTree.getCodes();

    // Encode the input file
    encodeFile(inputFile, outputFile, huffmanTree, codes);
    std::cout << "Encoding completed. Encoded data saved to " << outputFile << std::endl;
  }
  else if (mode == "decode")
  {
    // Decode the encoded file back to its original content
    decodeFile(inputFile, outputFile);
    std::cout << "Decoding completed. Decoded data saved to " << outputFile << std::endl;
  }

  return 0;
}
