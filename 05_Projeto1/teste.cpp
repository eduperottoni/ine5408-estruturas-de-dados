#include <iostream>
#include "headers/linked_queue.h"

int main() {
    structures::LinkedQueue<int> lista;

    lista.enqueue(1);
    std::cout << lista.front() << std::endl;
}