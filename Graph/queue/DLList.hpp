#ifndef DLLIST_H
#define DLLIST_H

#include "DLLNode.hpp"

template <typename T>
class DLList {
public:
    // No-arg constructor
    DLList();

    bool        empty() const; // Returns true if list is empty
    void        push_front(const T& val); // Insert the new node at the beginning
    void        print() const; // Print the list
    void        pop_back(); // Remove the last element (node)
    void        print_backwards() const;
    void        pop_front();
    void        push_back(const T& val);
    const T&    front() const;
private:
    DLLNode<T>* head; // The pointer to the first node
    DLLNode<T>* tail; // The pointer to the last node
    unsigned list_size;
};

#endif