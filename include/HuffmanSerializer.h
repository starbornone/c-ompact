#ifndef HUFFMANSERIALIZER_H
#define HUFFMANSERIALIZER_H

#include <memory>
#include <istream>
#include <ostream>
#include "Node.h"

class HuffmanSerializer
{
public:
  void serializeTree(const Node *node, std::ostream &out) const;
  std::unique_ptr<Node> deserializeTreeHelper(std::istream &in) const;
};

#endif // HUFFMANSERIALIZER_H
