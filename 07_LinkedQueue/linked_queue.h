// Copyright [2022] <Eduardo Perottoni

#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
class LinkedQueue {
 public:
    // Construtor
    LinkedQueue();
    // Destrutor
    ~LinkedQueue();
    // Limpa a fila
    void clear();

    // Enfileirar
    void enqueue(const T& data);
    // Desenfileirar
    T dequeue();

    // Retorna primeiro elemento
    T& front() const;
    // Retorna último elemento
    T& back() const;
    // Retorna tamanho da fila
    size_t size() const;

    // Testa se a lista está vazia
    bool empty() const;

 private:
    // Elemento da fila
    class Node {
     public:
        // Construtor
        explicit Node(const T& data):
            data_{data}
        {}
        // Construtor com data e next
        Node(const T& data, Node* node):
            data_{data},
            next_{node}
        {}
        // getter data
        T& data() {
            return data_;
        }
        // getter data const
        const T& data() const {
            return data_;
        }
        // getter next
        Node* next() {
            return next_;
        }
        // getter next const
        const Node* next() const {
            return next_;
        }
        // setter next
        void next(Node* next) {
            next_ = next;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };
    // propriedades privadas
    Node *tail{nullptr}, *head{nullptr};
    size_t size_;
};

}  // namespace structures

#endif

// IMPLEMENTAÇÃO DOS MÉTODOS
template<typename T>
structures::LinkedQueue<T>::LinkedQueue() {
    size_ = 0;
    tail = nullptr;
    head = nullptr;
}

template<typename T>
structures::LinkedQueue<T>::~LinkedQueue() {
    clear();
}

template<typename T>
void structures::LinkedQueue<T>::clear() {
    while (!empty())
        dequeue();
}

template<typename T>
void structures::LinkedQueue<T>::enqueue(const T& data) {
    Node *novo = new Node(data, nullptr);
    if (novo == nullptr)
        throw std::out_of_range("Memória cheia");
    if (empty())
        head = novo;
    else
        tail -> next(novo);
    tail = novo;
    size_++;
}

template<typename T>
T structures::LinkedQueue<T>::dequeue() {
    if (empty())
        throw std::out_of_range("Fila vazia");
    Node* aux = head;
    T data = aux -> data();
    if (static_cast<int>(size_) == 1) {
        tail = nullptr;
    }
    head = head -> next();
    size_--;
    return data;
}

template<typename T>
T& structures::LinkedQueue<T>::front() const {
    if (empty())
        throw std::out_of_range("Fila vazia");
    return head -> data();
}

template<typename T>
T& structures::LinkedQueue<T>::back() const {
    if (empty())
        throw std::out_of_range("Fila vazia");
    return tail -> data();
}

template<typename T>
size_t structures::LinkedQueue<T>::size() const {
    return size_;
}

template<typename T>
bool structures::LinkedQueue<T>::empty() const {
    return (static_cast<int>(size_) == 0);
}
