#ifndef ENCODE_DECODE_UTILS_H
#define ENCODE_DECODE_UTILS_H

#include "HuffmanTree.h"
#include <string>

// Function to encode a file using the Huffman tree
void encodeFile(const std::string &inputFilename, const std::string &outputFilename, HuffmanTree &huffmanTree, const std::unordered_map<char, std::string> &codes);

// Function to decode a file using the Huffman tree
void decodeFile(const std::string &inputFilename, const std::string &outputFilename);

#endif // ENCODE_DECODE_UTILS_H
