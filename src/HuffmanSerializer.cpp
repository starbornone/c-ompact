#include "../include/HuffmanSerializer.h"
#include "../include/Node.h"
#include <stdexcept>
#include <string>

void HuffmanSerializer::serializeTree(const Node *node, std::ostream &out) const
{
  if (!node)
    return;

  if (!node->left && !node->right)
  {
    out.put('1');
    out.put(node->character);
  }
  else
  {
    out.put('0');
    serializeTree(node->left.get(), out);
    serializeTree(node->right.get(), out);
  }
}

std::unique_ptr<Node> HuffmanSerializer::deserializeTreeHelper(std::istream &in) const
{
  char flag;
  if (!in.get(flag))
  {
    return nullptr;
  }

  if (flag == '1')
  {
    char ch;
    if (!in.get(ch))
    {
      throw std::runtime_error("Error reading character during tree deserialization.");
    }
    return std::make_unique<Node>(ch, 0);
  }
  else if (flag == '0')
  {
    auto left = deserializeTreeHelper(in);
    auto right = deserializeTreeHelper(in);
    return std::make_unique<Node>(std::move(left), std::move(right));
  }
  else
  {
    throw std::runtime_error("Invalid flag character in tree deserialization: " + std::to_string(flag));
  }
}
