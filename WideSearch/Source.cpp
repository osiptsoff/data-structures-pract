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
        std::cout << '\n' << "����� � ������: ";
        count = Tr.BFS();
        std::cout << "���������� ������, ������� ������� = " << count;
    }
    else std::cout << "������ �����!";
    return 0;
}
