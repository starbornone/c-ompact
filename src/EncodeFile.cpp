#include "EncodeFile.h"
#include "HuffmanSerializer.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <unordered_map>

void encodeFile(const std::string &inputFilename,
                const std::string &outputFilename,
                const HuffmanTree &huffmanTree,
                const std::unordered_map<char, std::string> &codes)
{
  std::ifstream inFile(inputFilename, std::ios::binary);
  if (!inFile)
  {
    throw std::runtime_error("Error opening input file: " + inputFilename);
  }

  std::ofstream outFile(outputFilename, std::ios::binary);
  if (!outFile)
  {
    throw std::runtime_error("Error opening output file: " + outputFilename);
  }

  HuffmanSerializer serializer;
  serializer.serializeTree(huffmanTree.getRoot(), outFile);

  std::streampos paddingPos = outFile.tellp();
  outFile.put(0);

  unsigned char currentByte = 0;
  int bitCount = 0;

  char ch;
  while (inFile.get(ch))
  {
    auto it = codes.find(ch);
    if (it == codes.end())
    {
      throw std::runtime_error(std::string("Character '") + ch + "' not found in Huffman codes.");
    }

    const std::string &code = it->second;
    for (char bitChar : code)
    {
      if (bitChar == '1')
      {
        currentByte |= (1 << (7 - bitCount));
      }
      else if (bitChar != '0')
      {
        throw std::runtime_error("Invalid bit character in Huffman code.");
      }

      bitCount++;

      if (bitCount == 8)
      {
        outFile.put(static_cast<unsigned char>(currentByte));
        currentByte = 0;
        bitCount = 0;
      }
    }
  }

  int padding = 0;
  if (bitCount > 0)
  {
    padding = 8 - bitCount;
    currentByte <<= padding;
    outFile.put(static_cast<unsigned char>(currentByte));
  }

  outFile.seekp(paddingPos);
  outFile.put(static_cast<unsigned char>(padding));
}
