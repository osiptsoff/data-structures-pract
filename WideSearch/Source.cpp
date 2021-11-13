#include <iostream>
#include <string.h>
#include <time.h>

template <class item> class QUEUE {
    item* Q;
    int h, t, N;
public:
    QUEUE(int maxQ) :h(0), t(0), N(maxQ), Q(new item[maxQ + 1]) {}
    int empty() const
    {
        return (h % N) == t;
    }
    void push(item ltem)
    {
        Q[t++] = ltem;
        t %= N;
    }
    item pop()
    {
        h %= N;
        return Q[h++];
    }
};

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
        v->d = num++;
        v->lft = MakeNode(depth + 1);
        v->mdl = MakeNode(depth + 1);
        v->rgt = MakeNode(depth + 1);
    }
    return v;
}

void Tree::OutNodes(Node* v, int r, int c) {
    if (r && c && (c < 80)) SCREEN[r - 1][c - 1] = v->d;
    if (r < maxrow) {
        if (v->lft)OutNodes(v->lft, r + 1, c - (offset >> r));
        if (v->mdl)OutNodes(v->mdl, r + 1, c);
        if (v->rgt)OutNodes(v->rgt, r + 1, c + (offset >> r));
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
    QUEUE<Node*>Q(MaxQ);
    Q.push(root);
    while (!Q.empty())
    {
        Node* v = Q.pop();
        std::cout << v->d << '_';
        count++;
        if (v->lft)Q.push(v->lft);
        if (v->mdl)Q.push(v->mdl);
        if (v->rgt)Q.push(v->rgt);
    }
    return count - 1;
}

int main()
{
    int count = 0;
    Tree Tr('a', 'z', 8);
    srand(time(nullptr));
    setlocale(LC_ALL, "Russian");
    Tr.MakeTree();
    if (Tr.exist()) {
        Tr.OutTree();
        std::cout << '\n' << "Обход в ширину: ";
        count = Tr.BFS();
        std::cout << "Количество вершин, имеющих предков = " << count;
    }
    else std::cout << "Дерево пусто!";
    return 0;
}
