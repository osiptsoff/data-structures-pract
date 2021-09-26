#include <iostream>

struct Set {
    char el;
    Set* next;
    Set(char e = 1, Set* n = nullptr) :el(e), next(n) {}
    ~Set() { delete next; }
};

int main()
{
    Set *a=nullptr, *b=nullptr, *c=nullptr, *d=nullptr, *e=nullptr;
    char tem;
    int n, ne = 0;
    std::cout << "A" << "\n";
    for (tem = std::cin.get(); tem !='\n'; tem = std::cin.get())
        a = new Set(tem, a);
    std::cout << "B" << "\n";
    for (tem = std::cin.get(); tem != '\n'; tem = std::cin.get())
        b = new Set(tem, b);
    std::cout << "C" << "\n";
    for (tem = std::cin.get(); tem != '\n'; tem = std::cin.get())
        c = new Set(tem, c);
    std::cout << "D" << "\n";
    for (tem = std::cin.get(); tem != '\n'; tem = std::cin.get())
        d = new Set(tem, d);
    for(Set *tempa = a; tempa!=nullptr; tempa=tempa->next){
        for (Set *tempb = b; tempb!= nullptr; tempb=tempb->next)
        {
            bool fl = true;
            if (tempb->el == tempa->el)
            {
                for (Set *tempc = c; tempc != nullptr; tempc=tempc->next)
                    if (tempb->el == tempc->el)
                        fl = false;
                if (fl)
                {
                    if (ne == 0)
                        e = new Set(tempb->el);
                    else
                        e = new Set(tempb->el, e);
                    ne++;
                }
            }     
        }
    }
    for (Set *tempd= d; tempd!= nullptr; tempd=tempd->next)
    {
        bool fl = false;
        for (Set *tempe=e; tempe != nullptr; tempe=tempe->next)
            if (tempd->el == tempe->el)
                fl = true;
        if (!fl && ne != 0)
        {
            e = new Set(tempd->el, e);
            ne++;
        }
        else if (ne == 0 && !fl)
        {
            e = new Set(tempd->el);
            ne++;
        }
    }
    for(Set *tempe = e;tempe != nullptr; tempe=tempe->next)
        std::cout << tempe->el << " ";
    return 0;
}