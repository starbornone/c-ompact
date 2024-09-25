#ifndef ENCODE_FILE_H
#define ENCODE_FILE_H

#include "HuffmanTree.h"
#include <string>
#include <unordered_map>

// Function to encode a file using the Huffman tree
void encodeFile(const std::string &inputFilename,
                const std::string &outputFilename,
                const HuffmanTree &huffmanTree,
                const std::unordered_map<char, std::string> &codes);

#endif // ENCODE_FILE_H