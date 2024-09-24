#include "../include/HuffmanTree.h"
#include "../include/Node.h"
#include "../include/HuffmanSerializer.h"
#include "../include/HuffmanCodeGenerator.h"
#include <vector>
#include <algorithm>
#include <memory>
#include <stdexcept>

HuffmanTree::HuffmanTree() : root(nullptr) {}

HuffmanTree::~HuffmanTree() {}

void HuffmanTree::build(const std::unordered_map<char, int> &frequencies)
{
  std::vector<std::unique_ptr<Node>> heap;
  for (const auto &pair : frequencies)
  {
    heap.push_back(std::make_unique<Node>(pair.first, pair.second));
  }

  auto comparator = [](const std::unique_ptr<Node> &lhs, const std::unique_ptr<Node> &rhs)
  {
    return lhs->frequency > rhs->frequency;
  };
  std::make_heap(heap.begin(), heap.end(), comparator);

  while (heap.size() > 1)
  {
    std::pop_heap(heap.begin(), heap.end(), comparator);
    auto left = std::move(heap.back());
    heap.pop_back();

    std::pop_heap(heap.begin(), heap.end(), comparator);
    auto right = std::move(heap.back());
    heap.pop_back();

    auto newNode = std::make_unique<Node>(std::move(left), std::move(right));
    heap.push_back(std::move(newNode));
    std::push_heap(heap.begin(), heap.end(), comparator);
  }

  root = std::move(heap.front());
}

const Node *HuffmanTree::getRoot() const
{
  return root.get();
}

std::unordered_map<char, std::string> HuffmanTree::getCodes() const
{
  return codes;
}

void HuffmanTree::setCodes(const std::unordered_map<char, std::string> &newCodes)
{
  codes = newCodes;
}

void HuffmanTree::setRootFromStream(std::istream &in)
{
  HuffmanSerializer serializer;
  root = serializer.deserializeTreeHelper(in);
}

std::unique_ptr<Node> HuffmanTree::deserializeTree(std::istream &in) const
{
  HuffmanSerializer serializer;
  return serializer.deserializeTreeHelper(in);
}