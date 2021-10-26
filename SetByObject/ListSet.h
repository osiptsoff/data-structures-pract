#pragma once

#include <iostream>
#include <time.h>

using std::cout;
using std::cin;

class El {
    static const int poolSize = 300;
    static El* pool;

    char e;
    El* next;
public:
    static void* operator new(size_t size)
    {
        int i;
        std::bad_alloc exception;

        for (i = 0; i < poolSize && pool[i].e != '!'; i++);
        if (i != poolSize)
            return pool + i;
        else
            throw exception;
    }

    static void operator delete(void* ptr) { ((El*)ptr)->e = '!'; }


    El() : e('!'), next(nullptr) { }
    El(char e, El* n = nullptr) : e(e), next(n) {  }
    ~El() {
        if (this) {
            if (next) { delete next; }
            e = '*';
        }
    }
    friend class Set;
    friend std::ostream& operator << (std::ostream& o, El& S);

};
std::ostream& operator << (std::ostream& o, El& S)
{
    for (El* p = &S; p; p = p->next) o << p->e;
    return o;
}

El* El::pool = new El[poolSize];

class Set
{
private:
    const static int N;
    static int num;
    int n;
    char S;
    El* A;

public:
    Set();
    Set(char);
    Set(const Set&);
    Set(Set&&) noexcept;
    Set& operator = (const Set&);
    Set& operator = (Set&&) noexcept;
    ~Set() {
        delete A; num--;
    }


    int GetPower() { return n; }

    Set& operator |= (const Set&);
    Set& operator &= (const Set&);
    Set operator | (const Set&) const;
    Set operator & (const Set&) const;
    Set operator ~ () const;
    void Print();

};

Set::Set() : n(0), S('A' + num++), A(nullptr)
{ }

Set::Set(char) : S('A' + num++), n(0)
{

    A = nullptr;
    for (int i = 0; i < N; i++)
        if (rand() % 2)
            A = new El(i + 'a', A), ++n;

}

Set::Set(const Set& B) : n(B.n), S('A' + num++), A(nullptr)
{
    for (El* p = B.A; p; p = p->next) A = new El(p->e, A);

}

Set::Set(Set&& B) noexcept : n(B.n), S('A' + num++), A(B.A)
{
    B.A = nullptr;
}

Set& Set::operator &= (const Set& B)
{
    Set C;
    delete A;
    A = nullptr;
    for (El* i = A; i; i = i->next)
    {
        for (El* j = B.A; j; j = j->next)
            if (i->e == j->e)
                this->A = new El(i->e, this->A), this->n++;
    }

    return *this;
}
Set Set::operator & (const Set& B) const
{
    Set C(*this);

    return std::move(C &= B);
}

Set& Set::operator |= (const Set& B)
{
    for (El* i = B.A; i; i = i->next)
    {
        bool f = true;
        for (El* j = A; f && j; j = j->next)
            f = f && (i->e != j->e);
        if (f)
            this->A = new El(i->e, this->A), this->n++;
    }


    return *this;
}
Set Set::operator | (const Set& B) const
{
    Set C(*this);

    return std::move(C |= B);
}


Set Set::operator ~ ()const
{
    Set C;
    for (char c = 'A'; c <= 'Z'; ++c)
    {
        bool f = true;
        for (El* j = A; j && f; j = j->next)
            if (c == j->e) f = false;
        if (f)
            C.A = new El(c, C.A), ++C.n;
    }

    return C;
}

Set& Set::operator = (const Set& B)
{
    if (this != &B)
    {
        delete A;
        A = nullptr;
        n = 0;
        for (El* p = B.A; p; p = p->next)
            A = new El(p->e, A), ++n;
        S = 'A' + num++;
    }

    return *this;
}

Set& Set::operator = (Set&& B) noexcept
{
    this->A = B.A;
    this->n = B.n;
    B.A = nullptr;
    delete B.A; B.A = nullptr;
    S = 'A' + num++;

    return *this;
}

void Set::Print()
{
    std::cout << "Set " << S << ":" << " [";
    for (El* p = A; p; p = p->next) std::cout << p->e;
    std::cout << "] " << "\n";
}

int Set::num = 0;
const int Set::N = 26;
