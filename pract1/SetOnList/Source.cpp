#include <iostream>
#include <time.h>


struct Set {
    char el;
    Set* next;
    Set(char e = 1, Set* n = nullptr) :el(e), next(n) {}
    ~Set() { delete next; }
};


Set* GenerateRandomSet()
{
    static const char* universe = "abcdefghijklmnopqrstuvwxyz";
    static const int universeSize = strlen(universe);

    Set* result = nullptr;
    int word = rand() % (1 << universeSize);

    for (int i = 0; i < universeSize; ++i)
        if ((word & (1 << i)) > 0)
            result = new Set(universe[i], result);

    return result;
}



int main()
{
    Set *a = nullptr, *b = nullptr, *c = nullptr, *d = nullptr, *e = nullptr;
    char tem;
    bool* bA = new bool[26];
    int n, ne = 0, k;
    srand(time(nullptr));
    a = GenerateRandomSet();
    b = GenerateRandomSet();
    c = GenerateRandomSet();
    d = GenerateRandomSet();

   
    clock_t start = clock();
    for (int k = 0; k < 1000000; k++)
    {
        delete e;
        e = nullptr;
        for (Set* tempa = a; tempa != nullptr; tempa = tempa->next) {
            for (Set* tempb = b; tempb != nullptr; tempb = tempb->next)
            {
              
                bool fl = true;
                if (tempb->el == tempa->el)
                {
                    for (Set* tempc = c; tempc != nullptr; tempc = tempc->next)
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
        for (Set* tempd = d; tempd != nullptr; tempd = tempd->next)
        {
            bool fl = false;
            for (Set* tempe = e; tempe != nullptr; tempe = tempe->next)
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

    }
    start = clock() - start;
    std::cout <<" Time taken : " << start / (float)CLOCKS_PER_SEC << "\n";
    std::cout << "A:";
    for (Set* tempe = a; tempe != nullptr; tempe = tempe->next)
        std::cout << tempe->el << " ";
    std::cout << "\n";
    std::cout << "B: ";
    for (Set* tempe = b; tempe != nullptr; tempe = tempe->next)
        std::cout << tempe->el << " ";
    std::cout << "\n";
    std::cout << "C: ";
    for (Set* tempe = c; tempe != nullptr; tempe = tempe->next)
        std::cout << tempe->el << " ";
    std::cout << "\n";
    std::cout << "D: ";
    for (Set* tempe = d; tempe != nullptr; tempe = tempe->next)
        std::cout << tempe->el << " ";
    std::cout << "\n";
    std::cout << "E: ";
    for (Set* tempe = e; tempe != nullptr; tempe = tempe->next)
        std::cout << tempe->el << " ";

    
    return 0;
}