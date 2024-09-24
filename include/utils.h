#ifndef UTILS_H
#define UTILS_H

#include <unordered_map>
#include <string>
#include "HuffmanTree.h"

// Calculates the frequency of each character in the specified file.
// Returns a map where the key is a character and the value is its frequency.
std::unordered_map<char, int> calculateFrequencies(const std::string &filename);

// Encodes the input file using the provided Huffman tree and codes.
// The encoded data and the serialized Huffman tree are saved to the output file.
void encodeFile(const std::string &inputFilename, const std::string &outputFilename, HuffmanTree &huffmanTree, const std::unordered_map<char, std::string> &codes);

// Decodes the encoded input file using the stored Huffman tree and writes the original data to the output file.
void decodeFile(const std::string &inputFilename, const std::string &outputFilename);

// Compares two files byte by byte and returns true if they are identical, false otherwise.
bool compareFiles(const std::string &file1, const std::string &file2);

// Creates the specified directory if it does not already exist.
void createDirectoryIfNotExists(const std::string &directory);

#endif // UTILS_H
