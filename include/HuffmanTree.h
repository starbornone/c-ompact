#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>

// Node structure for Huffman Tree
struct Node
{
  char character;
  int frequency;
  std::unique_ptr<Node> left;
  std::unique_ptr<Node> right;

  Node(char ch, int freq);
  Node(std::unique_ptr<Node> l, std::unique_ptr<Node> r);
};

// HuffmanTree class declaration
class HuffmanTree
{
public:
  HuffmanTree();
  ~HuffmanTree();

  void build(const std::unordered_map<char, int> &frequencies);
  void generateCodes(const Node *node, const std::string &code);
  std::unordered_map<char, std::string> getCodes() const;
  const Node *getRoot() const;

  // Serialize and deserialize functions
  void serializeTree(std::ostream &out) const; // Serialize the tree to a stream

  // This function sets the root by deserializing from the stream
  void setRootFromStream(std::istream &in);

  // This function returns a unique_ptr<Node> by deserializing from the stream
  std::unique_ptr<Node> deserializeTree(std::istream &in) const;

private:
  std::unique_ptr<Node> root;
  std::unordered_map<char, std::string> codes;

  void serializeTree(const Node *node, std::ostream &out) const;

  // Helper function to return std::unique_ptr<Node>
  std::unique_ptr<Node> deserializeTreeHelper(std::istream &in) const;
};

#endif // HUFFMANTREE_H
