#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>

// Node structure for the Huffman tree
struct Node
{
  char ch;     // Character
  int freq;    // Frequency of the character
  Node *left;  // Left child
  Node *right; // Right child

  Node(char character, int frequency)
      : ch(character), freq(frequency), left(nullptr), right(nullptr) {}
};

// Comparator for the priority queue (min-heap)
struct compare
{
  bool operator()(Node *left, Node *right)
  {
    return left->freq > right->freq;
  }
};

class HuffmanTree
{
public:
  HuffmanTree();
  ~HuffmanTree();

  // Build the Huffman tree based on character frequencies
  void build(const std::unordered_map<char, int> &frequencies);

  // Generate Huffman codes from the tree
  void generateCodes(Node *node, const std::string &str);

  // Get the generated Huffman codes
  std::unordered_map<char, std::string> getCodes();

  // Get the root of the Huffman tree
  Node *getRoot();

  // Serialize the Huffman tree to an output stream
  void serializeTree(Node *node, std::ostream &out);

  // Deserialize the Huffman tree from an input stream
  Node *deserializeTree(std::istream &in);

  // Destroy the tree and free memory
  void destroyTree(Node *node);

private:
  Node *root;                                  // Root of the Huffman tree
  std::unordered_map<char, std::string> codes; // Map of characters to their Huffman codes
};

#endif // HUFFMANTREE_H
