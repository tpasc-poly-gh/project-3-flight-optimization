#ifndef QUEUEDLL_H
#define QUEUEDLL_H

#include "DLList.hpp"
#include "DLList.cpp"

template <typename T>
class QueueDLL {
public:
    
    int         size() const; // TODO
    bool        empty() const;
    void        print() const;
    void        clear(); // TODO

    void        enqueue(const T& val);
    // Throws std::out_of_range exception
    T           dequeue();
    const T&    front() const; // Return the first element in the queue TODO
    
private:
    DLList<T> data;
};

#include "QueueDLL.tpp"

#endif