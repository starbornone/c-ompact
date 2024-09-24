#include "../include/HuffmanTree.h"

HuffmanTree::HuffmanTree() : root(nullptr) {}

HuffmanTree::~HuffmanTree()
{
  destroyTree(root);
}

void HuffmanTree::destroyTree(Node *node)
{
  if (node)
  {
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
  }
}

void HuffmanTree::build(const std::unordered_map<char, int> &frequencies)
{
  // Priority queue (min-heap) to build the Huffman tree
  std::priority_queue<Node *, std::vector<Node *>, compare> minHeap;

  // Create leaf nodes for each character and add them to the heap
  for (const auto &pair : frequencies)
  {
    minHeap.push(new Node(pair.first, pair.second));
  }

  // Build the tree until there is only one node left in the heap
  while (minHeap.size() > 1)
  {
    // Extract the two nodes with the smallest frequencies
    Node *left = minHeap.top();
    minHeap.pop();
    Node *right = minHeap.top();
    minHeap.pop();

    // Create a new internal node with these two nodes as children
    Node *newNode = new Node('\0', left->freq + right->freq);
    newNode->left = left;
    newNode->right = right;

    // Add the new node back to the heap
    minHeap.push(newNode);
  }

  // The remaining node is the root of the Huffman tree
  root = minHeap.top();
}

void HuffmanTree::generateCodes(Node *node, const std::string &str)
{
  if (!node)
    return;

  // If it's a leaf node, store the code
  if (!node->left && !node->right)
  {
    codes[node->ch] = str;
  }

  // Traverse the left and right subtrees
  generateCodes(node->left, str + "0");
  generateCodes(node->right, str + "1");
}

std::unordered_map<char, std::string> HuffmanTree::getCodes()
{
  return codes;
}

Node *HuffmanTree::getRoot()
{
  return root;
}

void HuffmanTree::serializeTree(Node *node, std::ostream &out)
{
  if (!node)
    return;

  if (!node->left && !node->right)
  {
    // Leaf node
    out.put('1');
    out.put(node->ch);
  }
  else
  {
    // Internal node
    out.put('0');
    serializeTree(node->left, out);
    serializeTree(node->right, out);
  }
}

Node *HuffmanTree::deserializeTree(std::istream &in)
{
  char flag;
  if (!in.get(flag))
    return nullptr;

  if (flag == '1')
  {
    // Leaf node
    char ch;
    if (!in.get(ch))
    {
      std::cerr << "Error reading character during tree deserialization." << std::endl;
      return nullptr;
    }
    return new Node(ch, 0);
  }
  else if (flag == '0')
  {
    // Internal node
    Node *left = deserializeTree(in);
    Node *right = deserializeTree(in);
    Node *node = new Node('\0', 0);
    node->left = left;
    node->right = right;
    return node;
  }
  else
  {
    std::cerr << "Invalid flag character in tree deserialization: " << flag << std::endl;
    return nullptr;
  }
}
