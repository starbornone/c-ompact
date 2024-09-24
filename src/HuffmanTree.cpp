#include "../include/HuffmanTree.h"
#include <queue>
#include <memory>
#include <stdexcept>
#include <vector>
#include <algorithm>

// Node constructor definitions
Node::Node(char ch, int freq) : character(ch), frequency(freq) {}
Node::Node(std::unique_ptr<Node> l, std::unique_ptr<Node> r)
    : character('\0'), frequency(l->frequency + r->frequency), left(std::move(l)), right(std::move(r)) {}

// HuffmanTree constructor and destructor
HuffmanTree::HuffmanTree() : root(nullptr) {}
HuffmanTree::~HuffmanTree() {}

// Custom comparator for priority queue
struct NodeComparator
{
  bool operator()(const std::unique_ptr<Node> &lhs, const std::unique_ptr<Node> &rhs) const
  {
    return lhs->frequency > rhs->frequency;
  }
};

// Function to build the Huffman tree from character frequencies
void HuffmanTree::build(const std::unordered_map<char, int> &frequencies)
{
  // Vector to store nodes and construct a heap
  std::vector<std::unique_ptr<Node>> heap;

  // Insert each character and its frequency as a leaf node into the vector
  for (const auto &pair : frequencies)
  {
    heap.push_back(std::make_unique<Node>(pair.first, pair.second));
  }

  // Convert the vector into a heap using a custom comparator
  auto comparator = [](const std::unique_ptr<Node> &lhs, const std::unique_ptr<Node> &rhs)
  {
    return lhs->frequency > rhs->frequency;
  };
  std::make_heap(heap.begin(), heap.end(), comparator);

  // Build the Huffman Tree
  while (heap.size() > 1)
  {
    // Extract the two nodes with the smallest frequencies
    std::pop_heap(heap.begin(), heap.end(), comparator);
    auto left = std::move(heap.back());
    heap.pop_back();

    std::pop_heap(heap.begin(), heap.end(), comparator);
    auto right = std::move(heap.back());
    heap.pop_back();

    // Create a new internal node with these two nodes as children
    auto newNode = std::make_unique<Node>(std::move(left), std::move(right));

    // Insert the new node back into the heap
    heap.push_back(std::move(newNode));
    std::push_heap(heap.begin(), heap.end(), comparator);
  }

  // The last remaining node is the root of the Huffman tree
  root = std::move(heap.front());
}

// Function to generate Huffman codes from the Huffman tree
void HuffmanTree::generateCodes(const Node *node, const std::string &code)
{
  if (!node)
    return;

  // If it's a leaf node, store the code
  if (!node->left && !node->right)
  {
    codes[node->character] = code;
    return;
  }

  // Traverse the left and right subtrees
  generateCodes(node->left.get(), code + "0");
  generateCodes(node->right.get(), code + "1");
}

// Function to retrieve the generated Huffman codes
std::unordered_map<char, std::string> HuffmanTree::getCodes() const
{
  return codes;
}

// Function to get the root of the Huffman tree
const Node *HuffmanTree::getRoot() const
{
  return root.get();
}

// Function to serialize the Huffman tree to an output stream
void HuffmanTree::serializeTree(const Node *node, std::ostream &out) const
{
  if (!node)
    return;

  if (!node->left && !node->right)
  {
    // Leaf node
    out.put('1');
    out.put(node->character);
  }
  else
  {
    // Internal node
    out.put('0');
    serializeTree(node->left.get(), out);
    serializeTree(node->right.get(), out);
  }
}

// Serialize the entire Huffman tree to an output stream
void HuffmanTree::serializeTree(std::ostream &out) const
{
  serializeTree(root.get(), out);
}

// Helper function to deserialize a Huffman tree and return a unique_ptr<Node>
std::unique_ptr<Node> HuffmanTree::deserializeTreeHelper(std::istream &in) const
{
  char flag;
  if (!in.get(flag))
  {
    return nullptr;
  }

  if (flag == '1')
  {
    // Leaf node
    char ch;
    if (!in.get(ch))
    {
      throw std::runtime_error("Error reading character during tree deserialization.");
    }
    return std::make_unique<Node>(ch, 0);
  }
  else if (flag == '0')
  {
    // Internal node
    auto left = deserializeTreeHelper(in);
    auto right = deserializeTreeHelper(in);
    return std::make_unique<Node>(std::move(left), std::move(right));
  }
  else
  {
    throw std::runtime_error("Invalid flag character in tree deserialization: " + std::to_string(flag));
  }
}

// This function sets the root of the tree by deserializing from the stream
void HuffmanTree::setRootFromStream(std::istream &in)
{
  root = deserializeTreeHelper(in);
}

// This function returns the root of the deserialized tree as a unique_ptr<Node>
std::unique_ptr<Node> HuffmanTree::deserializeTree(std::istream &in) const
{
  return deserializeTreeHelper(in);
}
