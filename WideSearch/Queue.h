#pragma once

template <class item> class Queue {
    item* Q;
    int h, t, N;
public:
    Queue(int maxQ) :h(0), t(0), N(maxQ), Q(new item[maxQ + 1]) {}
    ~Queue() { delete Q; }
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