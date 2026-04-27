#include "QueueDLL.hpp"
#include "QueueDLL.tpp"

#include <stdexcept>

int main(void) {
    QueueDLL<int> q;

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    q.print(); 

    std::cout << q.dequeue() << std::endl;
    std::cout << q.dequeue() << std::endl;
    std::cout << q.dequeue() << std::endl;

    // Dequeue an empty queue
    try {
        q.dequeue();
    }
    catch(std::out_of_range& ex) {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}