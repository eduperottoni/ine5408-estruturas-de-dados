#include "../headers/linked_queue.h"

template <typename T>
structures::LinkedQueue<T>::LinkedQueue() {
    head = nullptr;
    tail = nullptr;
    size_ = 0;
}

template <typename T>
structures::LinkedQueue<T>::~LinkedQueue() {
    clear();
}

template <typename T>
void structures::LinkedQueue<T>::enqueue(const T& data) {
    // inserer node no final da fila
    Node* new_node = new Node(data, tail);

    if (new_node == nullptr) {
        throw std::out_of_range("Erro na criação do nó");
    }

    if (empty()) {
        head = new_node;
    } else {
        tail->next(new_node);
    }
    tail = new_node;

    size_++;
}

template <typename T>
T structures::LinkedQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("Fila vazia");
    }

    Node* aux = head;
    T data = aux->data();

    head = aux->next();
    
    delete aux;
    size_--;

    return data;
}

template <typename T>
T& structures::LinkedQueue<T>::back() {
    return tail->data();
}

template <typename T>
T& structures::LinkedQueue<T>::front() {
    return head->data();
}

template <typename T>
void structures::LinkedQueue<T>::clear() {
    // desenfileira, mas sem armazenar os dados retornados
    while (!empty()) {
        dequeue();
    }
}

template <typename T>
std::size_t structures::LinkedQueue<T>::size() {
    return size_;
}

template <typename T>
bool structures::LinkedQueue<T>::empty() {
    return (size_ == 0);
}
