#include "../include/Handler.h"
#include "../include/HuffmanTree.h"
#include "../include/HuffmanCodeGenerator.h"
#include "../include/EncodeDecodeUtils.h"
#include "../include/FrequencyUtils.h"
#include "../include/FileUtils.h"
#include <iostream>
#include <unordered_map>
#include <fstream>

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

    HuffmanCodeGenerator codeGenerator;
    std::unordered_map<char, std::string> codes;
    codeGenerator.generateCodes(huffmanTree.getRoot(), "", codes);
    huffmanTree.setCodes(codes); // Use the setter method

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
