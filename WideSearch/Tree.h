#pragma once

#include <iostream>
#include "Node.h"
#include "Queue.h"

class Tree {
    static constexpr int maxRow = 10;
    static constexpr int maxCol = 110;
    static constexpr int offset = maxCol / 2;

    Node* root;
    char tag, maxTag;
    char** Screen;
    void clrscr();
    Node* MakeNode(int depth);
    void OutNodes(Node*, int, int);
    Tree(const Tree&) = delete;
    Tree(Tree&&) = delete;
    Tree& operator=(const Tree&) const = delete;
    Tree& operator = (Tree&&) const = delete;
public:
    Tree(char, char);
    ~Tree();
    void MakeTree() { root = MakeNode(0); }
    bool exist() { return root != nullptr; }
    int BFS();
    void OutTree();
};
Tree::Tree(char _tag, char _maxTag) : tag(_tag), maxTag(_maxTag), root(nullptr), Screen(new char* [maxRow]) {
    for (int i = 0; i < maxRow; i++)Screen[i] = new char[maxCol];
}

Tree ::~Tree() {
    for (int i = 0; i < maxRow; i++) {
        delete[] Screen[i];
    }
    delete[] Screen;
    delete root;
}
Node* Tree::MakeNode(int depth)
{
    Node* node = nullptr;
    bool toMake = (depth < rand() % 6 + 1) && (tag <= 'z');
    if (toMake) {
        node = new Node;
        node->tag = tag++;
        node->left = MakeNode(depth + 1);
        node->middle = MakeNode(depth + 1);
        node->right = MakeNode(depth + 1);
    }
    return node;
}

void Tree::OutNodes(Node* node, int row, int col) {
    if (row && col && (col < maxCol)) Screen[row - 1][col - 1] = node->tag;
    if (row < maxRow) {
        if (node->left)OutNodes(node->left, row + 1, col - (offset >> row));
        if (node->middle)OutNodes(node->middle, row + 1, col);
        if (node->right)OutNodes(node->right, row + 1, col + (offset >> row));
    }
}

void Tree::clrscr()
{
    for (int i = 0; i < maxRow; i++) {
        memset(Screen[i], '.', maxCol);
    }
}

void Tree::OutTree() {
    clrscr();
    OutNodes(root, 1, offset);
    for (int i = 0; i < maxRow; i++)
    {
        Screen[i][maxCol - 1] = 0;
        std::cout << '\n' << Screen[i];
    }
    std::cout << "\n";
}

int Tree::BFS() {
    const int MaxQ = 20;
    int count = 0;
    Queue<Node*>Q(MaxQ);
    Q.push(root);
    while (!Q.empty())
    {
        Node* v = Q.pop();
        std::cout << v->tag << '_';
        count++;
        if (v->left)Q.push(v->left);
        if (v->middle)Q.push(v->middle);
        if (v->right)Q.push(v->right);
    }
    return count - 1;
}