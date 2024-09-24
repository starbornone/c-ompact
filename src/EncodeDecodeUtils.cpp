#include "../include/EncodeDecodeUtils.h"
#include "../include/HuffmanTree.h"       // Include HuffmanTree for access to serialization and codes
#include "../include/HuffmanSerializer.h" // For serialization and deserialization
#include <bitset>
#include <fstream>
#include <iostream>
#include <stdexcept>

void encodeFile(const std::string &inputFilename, const std::string &outputFilename, HuffmanTree &huffmanTree, const std::unordered_map<char, std::string> &codes)
{
  std::ifstream inFile(inputFilename, std::ios::binary);
  std::ofstream outFile(outputFilename, std::ios::binary);

  if (!inFile.is_open() || !outFile.is_open())
  {
    std::cerr << "Error opening files for encoding." << std::endl;
    return;
  }

  HuffmanSerializer serializer;
  serializer.serializeTree(huffmanTree.getRoot(), outFile);

  std::string encodedString;
  char ch;
  while (inFile.get(ch))
  {
    encodedString += codes.at(ch);
  }

  int padding = 8 - (encodedString.size() % 8);
  if (padding != 8)
  {
    encodedString.append(padding, '0');
  }
  else
  {
    padding = 0;
  }

  outFile.put(static_cast<char>(padding));

  for (size_t i = 0; i < encodedString.size(); i += 8)
  {
    std::bitset<8> byte(encodedString.substr(i, 8));
    outFile.put(static_cast<unsigned char>(byte.to_ulong()));
  }

  inFile.close();
  outFile.close();
}

void decodeFile(const std::string &inputFilename, const std::string &outputFilename)
{
  std::ifstream inFile(inputFilename, std::ios::binary);
  std::ofstream outFile(outputFilename, std::ios::binary);

  if (!inFile.is_open() || !outFile.is_open())
  {
    std::cerr << "Error opening files for decoding." << std::endl;
    return;
  }

  HuffmanTree huffmanTree;
  std::unique_ptr<Node> root = huffmanTree.deserializeTree(inFile);

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
    encodedString.erase(encodedString.end() - padding, encodedString.end());
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
