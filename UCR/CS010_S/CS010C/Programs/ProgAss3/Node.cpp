#include "Node.h"

Node::Node() : numData(1), parent(nullptr), left(nullptr), middle(nullptr), right(nullptr) {}

Node::Node(const std::string& word) : small(word), numData(1), parent(nullptr), left(nullptr), middle(nullptr), right(nullptr) {}
