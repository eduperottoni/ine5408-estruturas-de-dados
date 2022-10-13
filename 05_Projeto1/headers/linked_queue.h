// COPYRIGHT [2022] Caio Prá Silva

#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include <cstdint>
#include <stdexcept>

namespace structures {

// Fila circular em vetor com encadeamento para elemento anterior
template <typename T>
class LinkedQueue {
   public:
    // construtor da classe LinkedQueue
    LinkedQueue();

    // construtor com parametro de LinkedQueue
    explicit LinkedQueue(std::size_t max);

    // destrutor
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

    // @return max_size: tamanho maximo da fila
    std::size_t max_size();

    // @return empty: true caso fila esteja vazia, senao, false
    bool empty();

    // @return full: true caso esteja com o maximo de elementos
    bool full();

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
        const T& data const() {
            return data_;
        }

        // @return node: proximo nodo
        Node* next() {
            return next_;
        }

        // @return node: proximo nodo
        const Node* next const() {
            return next_;
        }

        // @param node: proximo nodo a ser apontado
        void next(Node* node) {
            next_ node;
        }

     private:
        // vetor com os dados da fila
        T data_;
        Node* next_{nullptr};
    }

    // ponteiro para o comeco da fila
    Node* top_{nullptr};
    // ponteiro para o fim da fila
    Node* end_{nullptr};
};

}  // namespace structures

#endif
