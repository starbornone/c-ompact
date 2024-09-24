#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>
#include "Node.h"

class HuffmanTree
{
public:
  HuffmanTree();
  ~HuffmanTree();

  void build(const std::unordered_map<char, int> &frequencies);
  const Node *getRoot() const;

  std::unordered_map<char, std::string> getCodes() const;
  void setCodes(const std::unordered_map<char, std::string> &newCodes);

  void serializeTree(std::ostream &out) const;
  void setRootFromStream(std::istream &in);
  std::unique_ptr<Node> deserializeTree(std::istream &in) const;

private:
  std::unique_ptr<Node> root;
  std::unordered_map<char, std::string> codes;
};

#endif // HUFFMANTREE_H
