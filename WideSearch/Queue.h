#pragma once

template <class T> class Queue {
    T* items;
    int first, last, maxItems;
public:
    Queue(int maxQ) :first(0), last(0), maxItems(maxQ), items(new T[maxQ + 1]) {}
    ~Queue() { delete items; }
    int empty() const { return (first % maxItems) == last; }

    void push(T item)
    {
        items[last++] = item;
        last %= maxItems;
    }

    T pop()
    {
        first %= maxItems;
        return items[first++];
    }
};