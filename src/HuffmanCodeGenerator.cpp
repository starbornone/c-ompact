#include "../include/HuffmanCodeGenerator.h"
#include "../include/Node.h"

void HuffmanCodeGenerator::generateCodes(const Node *node, const std::string &code, std::unordered_map<char, std::string> &codes)
{
  if (!node)
    return;

  if (!node->left && !node->right)
  {
    codes[node->character] = code;
    return;
  }

  generateCodes(node->left.get(), code + "0", codes);
  generateCodes(node->right.get(), code + "1", codes);
}
