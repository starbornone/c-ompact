#include "include/HuffmanTree.h"
#include "include/utils.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>

// Function to display usage information
void printUsage()
{
  std::cout << "Usage: cppompact [options]\n"
            << "Options:\n"
            << "  --encode -e <input> <output>  Encode the input file to the output file.\n"
            << "  --decode -d <input> <output>  Decode the input file to the output file.\n"
            << "  --help   -h                   Show this help message.\n";
}

// Function to parse command-line arguments
bool parseArguments(int argc, char *argv[], std::string &mode, std::string &inputFile, std::string &outputFile)
{
  if (argc < 2)
  {
    std::cerr << "Error: Missing arguments.\n";
    printUsage();
    return false;
  }

  for (int i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];

    if (arg == "--encode" || arg == "-e")
    {
      if (i + 2 >= argc)
      {
        std::cerr << "Error: Missing input or output file for encoding.\n";
        printUsage();
        return false;
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
        return false;
      }
      mode = "decode";
      inputFile = argv[++i];
      outputFile = argv[++i];
    }
    else if (arg == "--help" || arg == "-h")
    {
      printUsage();
      return false;
    }
    else
    {
      std::cerr << "Error: Unknown option: " << arg << "\n";
      printUsage();
      return false;
    }
  }

  if (mode.empty())
  {
    std::cerr << "Error: No operation mode specified.\n";
    printUsage();
    return false;
  }

  return true;
}

// Function to check if a file exists and is readable
bool isFileReadable(const std::string &filename)
{
  std::ifstream infile(filename);
  return infile.good();
}

// Function to check if a file is writable or can be created
bool isFileWritable(const std::string &filename)
{
  std::ofstream outfile(filename);
  return outfile.good();
}

// Function to calculate the size of a file in bytes
std::size_t getFileSize(const std::string &filename)
{
  std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
  if (!in)
  {
    throw std::runtime_error("Error: Could not open file: " + filename);
  }
  return in.tellg();
}

// Function to handle file encoding with compression ratio display
void handleEncoding(const std::string &inputFile, const std::string &outputFile)
{
  try
  {
    if (!isFileReadable(inputFile))
    {
      std::cerr << "Error: Cannot read input file: " << inputFile << "\n";
      return;
    }

    if (!isFileWritable(outputFile))
    {
      std::cerr << "Error: Cannot write to output file: " << outputFile << "\n";
      return;
    }

    std::unordered_map<char, int> frequencies = calculateFrequencies(inputFile);
    if (frequencies.empty())
    {
      std::cerr << "Error: Input file is empty or not found: " << inputFile << "\n";
      return;
    }

    HuffmanTree huffmanTree;
    huffmanTree.build(frequencies);
    huffmanTree.generateCodes(huffmanTree.getRoot(), "");

    std::unordered_map<char, std::string> codes = huffmanTree.getCodes();

    encodeFile(inputFile, outputFile, huffmanTree, codes);
    std::cout << "Encoding completed. Encoded data saved to " << outputFile << std::endl;

    std::size_t originalSize = getFileSize(inputFile);
    std::size_t encodedSize = getFileSize(outputFile);

    if (encodedSize == 0)
    {
      std::cerr << "Error: Encoded file is empty. Compression ratio cannot be calculated.\n";
      return;
    }

    double compressionRatio = static_cast<double>(originalSize) / encodedSize;
    std::cout << "Original Size: " << originalSize << " bytes\n";
    std::cout << "Encoded Size: " << encodedSize << " bytes\n";
    std::cout << "Compression Ratio: " << compressionRatio << "\n";
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error during encoding: " << e.what() << std::endl;
  }
}

// Function to handle file decoding with enhanced error handling
void handleDecoding(const std::string &inputFile, const std::string &outputFile)
{
  try
  {
    if (!isFileReadable(inputFile))
    {
      std::cerr << "Error: Cannot read input file: " << inputFile << "\n";
      return;
    }

    if (!isFileWritable(outputFile))
    {
      std::cerr << "Error: Cannot write to output file: " << outputFile << "\n";
      return;
    }

    decodeFile(inputFile, outputFile);
    std::cout << "Decoding completed. Decoded data saved to " << outputFile << std::endl;
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error during decoding: " << e.what() << std::endl;
  }
}

int main(int argc, char *argv[])
{
  std::string mode;
  std::string inputFile;
  std::string outputFile;

  // Parse command-line arguments
  if (!parseArguments(argc, argv, mode, inputFile, outputFile))
  {
    return 1;
  }

  try
  {
    createDirectoryIfNotExists("output");
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error creating output directory: " << e.what() << std::endl;
    return 1;
  }

  if (mode == "encode")
  {
    handleEncoding(inputFile, outputFile);
  }
  else if (mode == "decode")
  {
    handleDecoding(inputFile, outputFile);
  }

  return 0;
}
