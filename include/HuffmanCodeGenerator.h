#ifndef HUFFMANCODEGENERATOR_H
#define HUFFMANCODEGENERATOR_H

#include <unordered_map>
#include <string>
#include "Node.h"

class HuffmanCodeGenerator
{
public:
  void generateCodes(const Node *node, const std::string &code, std::unordered_map<char, std::string> &codes);
};

#endif // HUFFMANCODEGENERATOR_H
