#include <iostream>
#include <time.h>

bool generRandBool()
{
    bool fl;
    int n;
    n = rand() % 4;
    if (n == 1)
        fl = true;
    else
        fl = false;

    return fl;
}

bool* GeneBoolSet()
{
    bool* a = new bool[26];
    for (int i = 0; i < 26; i++)
        a[i] = generRandBool();
    return a;
}


char* tostr(int* k, bool* bE)
{
    char* res = new char[26];
    for (int i = 0; i < 26; i++)
    {
        if (bE[i])
        {
            char tem;
            tem = i + 'a';
            res[*k] = tem;
            *k += 1;
        }
    }
    return res;
}
int main()
{
    int sizea = 0, sizeb = 0, sizec = 0, sized = 0, sizee = 0, shabl = 0;
    char* a, * b, * c, * d, * res;
    bool* bA, * bB, * bC, * bD, * bE;
    srand(time(nullptr));
    bA = GeneBoolSet();
    bB = GeneBoolSet();
    bC = GeneBoolSet();
    bD = GeneBoolSet();
    bE = new bool[26];
    clock_t start = clock();
    for (int j = 0; j < 1000000; j++)
    {
        sizee = 0;
        for (int i = 0; i < 26; i++)
        {
            bE[i] = (bA[i] && bB[i]) && !bC[i] || bD[i];

            if (bE[i])
                sizee++;
        }
    }
    start = clock() - start;
    std::cout << "Time taken: " << start / (float)CLOCKS_PER_SEC << "\n";
    res = tostr(&shabl, bE);
    a = tostr(&sizea, bA);
    b = tostr(&sizeb, bB);
    c = tostr(&sizec, bC);
    d = tostr(&sized, bD);

    std::cout << "A: ";
    for (int i = 0; i < sizea; i++)
        std::cout << a[i] << " ";
    std::cout << "\n";
    std::cout << "B: ";
    for (int i = 0; i < sizeb; i++)
        std::cout << b[i] << " ";
    std::cout << "\n";
    std::cout << "C: ";
    for (int i = 0; i < sizec; i++)
        std::cout << c[i] << " ";
    std::cout << "\n";
    std::cout << "D: ";
    for (int i = 0; i < sized; i++)
        std::cout << d[i] << " ";
    std::cout << "\n";
    std::cout << "E: ";
    for (int i = 0; i < sizee; i++)
        std::cout << res[i] << " ";
    return 0;
}
