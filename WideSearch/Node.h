#pragma once

class Node {
    char tag;
    Node* left;
    Node* middle;
    Node* right;
public:
    Node() :left(nullptr), right(nullptr), middle(nullptr) {}
    Node(const Node&) = delete;
    Node& operator = (const Node&) = delete;
    ~Node() {
        delete left;
        delete middle;
        delete right;
    }
    friend class Tree;
};
