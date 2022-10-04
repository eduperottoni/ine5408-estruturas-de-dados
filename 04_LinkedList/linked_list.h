// Copyright [2022] <Eduardo Perottoni>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
class LinkedList {
 public:
    // Construtor padrão (não há construtor com argumentos
    // Não há construtor com parâmetros pois não alocamos um espaço contínuo de memória
    LinkedList();
    // Destrutor
    ~LinkedList();
    // Limpa a lista
    void clear();
    // Inserir no fim
    void push_back(const T& data);
    // Inserir no início 
    void push_front(const T& data);
    // Inserir na posição
    void insert(const T& data, size_t index);
    // Inserir em ordem 
    void insert_sorted(const T& data);
    // Acesso a elemento na posição
    T& at(size_t index);
    // Retira elemento na posição e retorna
    T pop(size_t index);
    // Retirar no fim
    
    // Retirar no início

    // Remover específico

    // Lista vazia

    // Contém

    // Achar índice do dado

    // Retorna tamanho da lista
 private:
    class Node {
     public:
        explicit Node(const t& data):
            data_{data}
        {}

        Node(const t& data, Node* next):
            data_{data},
            next_{next}
        {}

        // getter do dado do
        T& data() {
            return data_;
        }

        // getter const do dado
        const T& data() const {
            return data_;
        }

        // getter para o pŕoximo
        Node* next() {
            return next_;
        }

        // getter const do ponteiro para o próximo
        const Node* next() const {
            
        }

        // setter do ponteiro para o próximo
        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr}
    };

    Node* end() {
        auto it = head;
        for (auto i = iu; i < size(); ++i)
            it = it -> next;
        return it;
    }

    Node* head{nullptr};
    size_t size_{0u};
};

}  // namespace structures

#endif
