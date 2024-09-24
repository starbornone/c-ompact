#include "../include/utils.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>
#include <bitset>
#include <iostream>

#ifdef _WIN32
#include <direct.h>
#endif

// Function to calculate frequencies of characters in a file
std::unordered_map<char, int> calculateFrequencies(const std::string &filename)
{
  std::unordered_map<char, int> frequencies;
  std::ifstream file(filename, std::ios::binary);

  if (!file.is_open())
  {
    std::cerr << "Error opening input file for frequency calculation: " << filename << std::endl;
    return frequencies;
  }

  char ch;
  while (file.get(ch))
  {
    frequencies[ch]++;
  }

  file.close();
  return frequencies;
}

// Function to encode a file using the Huffman tree
void encodeFile(const std::string &inputFilename, const std::string &outputFilename, HuffmanTree &huffmanTree, const std::unordered_map<char, std::string> &codes)
{
  std::ifstream inFile(inputFilename, std::ios::binary);
  std::ofstream outFile(outputFilename, std::ios::binary);

  if (!inFile.is_open() || !outFile.is_open())
  {
    std::cerr << "Error opening files for encoding." << std::endl;
    return;
  }

  // Step 1: Serialize the Huffman tree
  huffmanTree.serializeTree(outFile);

  // Step 2: Read the input file and build the encoded string
  std::string encodedString;
  char ch;
  while (inFile.get(ch))
  {
    encodedString += codes.at(ch);
  }

  // Step 3: Pad the encoded string to make its length a multiple of 8
  int padding = 8 - (encodedString.size() % 8);
  if (padding != 8)
  {
    encodedString.append(padding, '0');
  }
  else
  {
    padding = 0;
  }

  // Step 4: Write padding information to the output file
  outFile.put(static_cast<char>(padding));

  // Step 5: Convert the encoded string to bytes and write to the output file
  for (size_t i = 0; i < encodedString.size(); i += 8)
  {
    std::bitset<8> byte(encodedString.substr(i, 8));
    outFile.put(static_cast<unsigned char>(byte.to_ulong()));
  }

  inFile.close();
  outFile.close();
}

// Function to decode a file using the Huffman tree
void decodeFile(const std::string &inputFilename, const std::string &outputFilename)
{
  std::ifstream inFile(inputFilename, std::ios::binary);
  std::ofstream outFile(outputFilename, std::ios::binary);

  if (!inFile.is_open() || !outFile.is_open())
  {
    std::cerr << "Error opening files for decoding." << std::endl;
    return;
  }

  // Step 1: Deserialize the Huffman tree
  HuffmanTree huffmanTree;
  std::unique_ptr<Node> root = huffmanTree.deserializeTree(inFile);

  if (!root)
  {
    std::cerr << "Error deserializing Huffman tree." << std::endl;
    inFile.close();
    outFile.close();
    return;
  }

  // Step 2: Read padding information
  char paddingChar;
  if (!inFile.get(paddingChar))
  {
    std::cerr << "Error reading padding information." << std::endl;
    inFile.close();
    outFile.close();
    return;
  }
  int padding = static_cast<unsigned char>(paddingChar);

  // Step 3: Read the encoded data
  std::string encodedString;
  char byteChar;
  while (inFile.get(byteChar))
  {
    std::bitset<8> bits(static_cast<unsigned char>(byteChar));
    encodedString += bits.to_string();
  }

  // Step 4: Remove padding from the end of the encoded string
  if (padding > 0 && padding <= 8)
  {
    encodedString.erase(encodedString.end() - padding, encodedString.end());
  }

  // Step 5: Decode the encoded string using the Huffman tree
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

    // If leaf node, write the character and reset to root
    if (!current->left && !current->right)
    {
      outFile.put(current->character);
      current = root.get();
    }
  }

  inFile.close();
  outFile.close();
}

// Function to compare two files byte by byte
bool compareFiles(const std::string &file1, const std::string &file2)
{
  std::ifstream f1(file1, std::ios::binary | std::ios::ate);
  std::ifstream f2(file2, std::ios::binary | std::ios::ate);

  if (!f1.is_open() || !f2.is_open())
  {
    std::cerr << "Error opening files for comparison." << std::endl;
    return false;
  }

  // Check if file sizes are different
  if (f1.tellg() != f2.tellg())
  {
    return false;
  }

  // Seek back to the beginning
  f1.seekg(0);
  f2.seekg(0);

  // Compare byte by byte
  char ch1, ch2;
  while (f1.get(ch1) && f2.get(ch2))
  {
    if (ch1 != ch2)
    {
      return false;
    }
  }

  return true;
}

// Function to create a directory if it does not exist
void createDirectoryIfNotExists(const std::string &directory)
{
#ifdef _WIN32
  _mkdir(directory.c_str());
#else
  mkdir(directory.c_str(), 0777);
#endif
}
