// COPYRIGHT [2022] Caio Prá Silva

#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <cstdint>
#include <stdexcept>

namespace structures {

// Fila circular com encadeamento para elemento anterior
template <typename T>
class LinkedQueue {
 public:
    // construtor da classe LinkedQueue
    LinkedQueue();

    // destrutor da classe LinkedQueue
    ~LinkedQueue();

    /*
        Enfileira dado
        @param data: dado a ser enfileirado
    */
    void enqueue(const T& data);

    /*
        Desenfileira dado da fila
        @return data: dado que estava na fila e foi removido
    */
    T dequeue();

    // @return data: ultimo elemento da fila
    T& back();

    // @return data: elemento no topo da fila
    T& front();

    // limpa a fila
    void clear();

    // @return size: tamanho atual da fila
    std::size_t size();

    // @return empty: true caso fila esteja vazia, senao, false
    bool empty();

 private:
    class Node {
     public:
        explicit Node(const T& data) : data_{data} {}

        Node(const T& data, Node* next) : data_{data},
                                          next_{next} {}

        // @return data: dado armazenado pelo no nodo
        T& data() {
            return data_;
        }

        // @return data: dado armazenado pelo no nodo
        const T& data() const {
            return data_;
        }

        // @return node: proximo nodo
        Node* next() {
            return next_;
        }

        // @return node: proximo nodo
        const Node* next() const {
            return next_;
        }

        // @param node: proximo nodo a ser apontado
        void next(Node* node) {
            next_ = node;
        }

     private:
        // vetor com os dados da fila
        T data_;
        Node* next_{nullptr};
    };

    // ponteiro para o comeco da fila
    Node* head{nullptr};
    // ponteiro para o fim da fila
    Node* tail{nullptr};

    // variaval que mostra o tamanho atual da fila
    std::size_t size_{0u};
};

}  // namespace structures

#endif

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
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    }

    return tail->data();
}

template <typename T>
T& structures::LinkedQueue<T>::front() {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    }

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
    return (size() == 0);
}
