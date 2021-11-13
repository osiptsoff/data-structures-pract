#pragma once

#include <iostream>
#include "Node.h"
#include "Queue.h"

class Tree {
    Node* root;
    char num, maxnum;
    int maxrow, offset;
    char** SCREEN;
    int count;
    void clrscr();
    Node* MakeNode(int depth);
    void OutNodes(Node* v, int r, int c);
    Tree(const Tree&) = delete;
    Tree(Tree&&) = delete;
    Tree& operator=(const Tree&) const = delete;
    Tree& operator = (Tree&&) const = delete;
public:
    Tree(char num, char maxnum, int maxrow);
    ~Tree();
    void MakeTree() { root = MakeNode(0); }
    bool exist() { return root != nullptr; }
    int BFS();
    void OutTree();
};
Tree::Tree(char nm, char mnm, int mxr) :num(nm), maxnum(mnm), maxrow(mxr), offset(40), root(nullptr),
SCREEN(new char* [maxrow]) {
    for (int i = 0; i < maxrow; i++)SCREEN[i] = new char[80];
}

Tree ::~Tree() {
    for (int i = 0; i < maxrow; i++) {
        delete[] SCREEN[i];
    }
    delete[] SCREEN;
    delete root;
}
Node* Tree::MakeNode(int depth)
{
    Node* v = nullptr;
    int Y = (depth < rand() % 6 + 1) && (num <= 'z');
    if (Y) {
        v = new Node;
        v->tag = num++;
        v->left = MakeNode(depth + 1);
        v->middle = MakeNode(depth + 1);
        v->right = MakeNode(depth + 1);
    }
    return v;
}

void Tree::OutNodes(Node* v, int r, int c) {
    if (r && c && (c < 80)) SCREEN[r - 1][c - 1] = v->tag;
    if (r < maxrow) {
        if (v->left)OutNodes(v->left, r + 1, c - (offset >> r));
        if (v->middle)OutNodes(v->middle, r + 1, c);
        if (v->right)OutNodes(v->right, r + 1, c + (offset >> r));
    }
}

void Tree::clrscr()
{
    for (int i = 0; i < maxrow; i++) {
        memset(SCREEN[i], '.', 80);
    }
}

void Tree::OutTree() {
    clrscr();
    OutNodes(root, 1, offset);
    for (int i = 0; i < maxrow; i++)
    {
        SCREEN[i][79] = 0;
        std::cout << '\n' << SCREEN[i];
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
        //std::cout << v->tag << '_';
        count++;
        if (v->left)Q.push(v->left);
        if (v->middle)Q.push(v->middle);
        if (v->right)Q.push(v->right);
    }
    return count - 1;
}