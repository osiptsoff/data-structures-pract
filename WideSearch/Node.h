#pragma once

class Node {
    char d;
    Node* lft;
    Node* mdl;
    Node* rgt;
public:
    Node() :lft(nullptr), rgt(nullptr), mdl(nullptr) {}
    Node(const Node&) = delete;
    Node& operator = (const Node&) = delete;
    ~Node() {
        delete lft;
        delete mdl;
        delete rgt;
    }
    friend class Tree;
};
