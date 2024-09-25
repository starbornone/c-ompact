#ifndef DECODE_FILE_H
#define DECODE_FILE_H

#include "HuffmanTree.h"
#include <string>

// Function to decode a file using the Huffman tree
void decodeFile(const std::string &inputFilename,
                const std::string &outputFilename,
                HuffmanTree &huffmanTree);

#endif // DECODE_FILE_H
