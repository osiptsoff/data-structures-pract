#include <iostream>
#include "Tree.h"

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
