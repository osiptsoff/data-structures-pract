#pragma once

#include <iostream>
#include <time.h>
#include <string.h>
using namespace std;

class Set {
private:
    static int setsExist;
    const static char universe[];
    const static int universeSize;

    bool* bA;
    char tag;
    int power;

public:
    Set(int) {
        bA = new bool[universeSize];
        tag = 'A' + setsExist++;
        power = 0;
    };
    Set(char) {
        bA = new bool[universeSize];
        power = 0;
        for (int i = 0; i < universeSize; i++)
        {
            if (rand() % 2 == 0)
                bA[i] = false;
            else {
                bA[i] = true;
                power++;
            }
        }
        tag = 'A' + setsExist++;
    };
    Set()
    {
        bA = new bool[universeSize];
        tag = 'A' + setsExist++;
        power = 0;

    };
    Set(const Set& other)
    {
        bA = new bool[universeSize];
        tag = 'A' + setsExist++;
        for (int i = 0; i < universeSize; i++)
            bA[i] = other.bA[i];
        power = other.power;

    };
    Set(Set&& other)
    {
        bA = other.bA;
        power = other.power;
        other.bA = nullptr;
        tag = 'A' + setsExist++;
    }
    ~Set() { setsExist--; delete[] bA; };

    Set operator| (const Set& other) const;
    Set operator& (const Set& other) const;
    Set operator=(const Set& other);
    Set operator=(Set&& other);
    Set operator~ ()const;

    int GetPower() { return power; }
    void Print();
};

Set Set::operator&(const Set& other) const {
    Set C;
    for (int i = 0; i < universeSize; i++) {
        C.bA[i] = bA[i] & other.bA[i];
        C.power += C.bA[i];
    }
    return C;
}

Set Set::operator|(const Set& other) const {
    Set C;
    for (int i = 0; i < universeSize; i++) {
        C.bA[i] = bA[i] | other.bA[i];
        C.power += C.bA[i];
    }
    return C;
}

Set Set::operator~() const
{
    Set C;
    for (int i = 0; i < universeSize; i++) {
        C.bA[i] = !bA[i];
        C.power += C.bA[i];
    }
    return C;
}

Set Set::operator=(const Set& other) {
    if (this != &other) {
        for (int i = 0; i < universeSize; i++)
            bA[i] = other.bA[i];
        tag = other.tag;
        power = other.power;
    }
    return *this;
}

Set Set::operator=(Set&& other) {
    if (this != &other)
    {
        delete this->bA;
        bA = other.bA;
        other.bA = nullptr;
        tag = other.tag;
        power = other.power;
    }
    return *this;
}
void Set::Print()
{
    cout << "Set " << this->tag << ": \n";
    for (int i = 0; i < universeSize; i++)
    {
        if (this->bA[i])
        {
            char tem;
            tem = i + 'a';
            std::cout << tem << " ";
        }
    }
    cout << "\n";
}

const char Set::universe[] = "abcdefghijklmnopqrstuvwxyz";
const int Set::universeSize = strlen(universe);
int Set::setsExist = 0;


