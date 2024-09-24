#ifndef UTILS_H
#define UTILS_H

#include <unordered_map>
#include <string>
#include "HuffmanTree.h"

// Function to calculate character frequencies from a file
std::unordered_map<char, int> calculateFrequencies(const std::string &filename);

// Function to encode a file using Huffman codes and store the Huffman tree
void encodeFile(const std::string &inputFilename, const std::string &outputFilename, HuffmanTree &huffmanTree, const std::unordered_map<char, std::string> &codes);

// Function to decode a file using the stored Huffman tree
void decodeFile(const std::string &inputFilename, const std::string &outputFilename);

// Function to compare two files byte by byte
bool compareFiles(const std::string &file1, const std::string &file2);

// Function to ensure a directory exists or create it
void createDirectoryIfNotExists(const std::string &directory);

#endif // UTILS_H
