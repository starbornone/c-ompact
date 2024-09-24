#ifndef NODE_H
#define NODE_H

#include <memory>

struct Node
{
  char character;
  int frequency;
  std::unique_ptr<Node> left;
  std::unique_ptr<Node> right;

  Node(char ch, int freq);
  Node(std::unique_ptr<Node> l, std::unique_ptr<Node> r);
};

#endif // NODE_H
