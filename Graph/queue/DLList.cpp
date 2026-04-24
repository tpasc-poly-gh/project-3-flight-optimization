#include "DLList.hpp"

#include <iostream>
#include <stdexcept>

template <typename T>
DLList<T>::DLList() {
    head = new DLLNode<T>; // sentinel head node
    tail = new DLLNode<T>; // sentinel tail node
    head->next = tail;
    tail->prev = head;
    list_size = 0;
}

template <typename T>
void DLList<T>::push_front(const T& val) {
    head->next = new DLLNode<T>(val, head, head->next);
    head->next->next->prev = head->next;
    
    list_size++;
}

template <typename T>
void DLList<T>::print() const {
    DLLNode<T>* cur = head->next;

    while (cur != tail) {
        std::cout << cur->data;
        if (cur->next != tail) {
            std::cout << " -> ";
        }
        cur = cur->next;
    }
    std::cout << std::endl;
}

template <typename T>
void DLList<T>::pop_back() {
    if (!empty()) {
        DLLNode<T>* to_delete = tail->prev;
        tail->prev = to_delete->prev;
        tail->prev->next = tail;

        list_size--;
        delete to_delete;
    }

}

template <typename T>
bool DLList<T>::empty() const {
    return (list_size == 0);
}

template<typename T>
void DLList<T>::print_backwards() const {
    //iterate through the linked list 
    DLLNode<T>* cur = tail->prev;

    while(cur != head) {
        std::cout << cur->data;
        if (cur->prev != head) {
            std::cout << " -> ";
        }
        cur = cur->prev;
    }
    std::cout << "\n";
}

template<typename T>
void DLList<T>::push_back(const T& value) {
    tail->prev = new DLLNode<T>(value, tail->prev, tail);
    tail->prev->prev->next = tail->prev;
    list_size++; //update size
}

template<typename T>
void DLList<T>::pop_front() {
    if (!empty()) {
        DLLNode<T>* to_delete = head->next;
        head->next = head->next->next;
        head->next->prev = head;
        list_size--;
        delete to_delete;
    }
}

template<typename T>
const T& DLList<T>::front() const {
    if (empty()) {
        throw std::out_of_range("Empty list");
    }
    return head->next->data;
}