#include "DecodeFile.h"
#include "HuffmanSerializer.h"
#include <bitset>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>

void decodeFile(const std::string &inputFilename,
                const std::string &outputFilename,
                HuffmanTree &huffmanTree)
{
  std::ifstream inFile(inputFilename, std::ios::binary);
  std::ofstream outFile(outputFilename, std::ios::binary);

  if (!inFile.is_open() || !outFile.is_open())
  {
    std::cerr << "Error opening files for decoding." << std::endl;
    return;
  }

  HuffmanSerializer serializer;
  std::unique_ptr<Node> root = serializer.deserializeTreeHelper(inFile);

  if (!root)
  {
    std::cerr << "Error deserializing Huffman tree." << std::endl;
    inFile.close();
    outFile.close();
    return;
  }

  char paddingChar;
  if (!inFile.get(paddingChar))
  {
    std::cerr << "Error reading padding information." << std::endl;
    inFile.close();
    outFile.close();
    return;
  }
  int padding = static_cast<unsigned char>(paddingChar);

  std::string encodedString;
  char byteChar;
  while (inFile.get(byteChar))
  {
    std::bitset<8> bits(static_cast<unsigned char>(byteChar));
    encodedString += bits.to_string();
  }

  if (padding > 0 && padding <= 8)
  {
    encodedString.erase(encodedString.size() - padding, padding);
  }

  const Node *current = root.get();
  for (size_t i = 0; i < encodedString.size(); ++i)
  {
    if (encodedString[i] == '0')
    {
      current = current->left.get();
    }
    else
    {
      current = current->right.get();
    }

    if (!current->left && !current->right)
    {
      outFile.put(current->character);
      current = root.get();
    }
  }

  inFile.close();
  outFile.close();
}
