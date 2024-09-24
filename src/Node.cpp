#include "../include/Node.h"

Node::Node(char ch, int freq) : character(ch), frequency(freq) {}

Node::Node(std::unique_ptr<Node> l, std::unique_ptr<Node> r)
    : character('\0'), frequency(l->frequency + r->frequency), left(std::move(l)), right(std::move(r)) {}
