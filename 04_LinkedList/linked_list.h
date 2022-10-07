// Copyright [2022] <Eduardo Perottoni>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
class LinkedList {
 public:
    /* Construtor padrão (não há construtor com argumentos
    Não há construtor com parâmetros pois não alocamos um 
    espaço contínuo de memória */
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
    T pop_back();

    // Retirar no início
    T pop_front();

    // Remove pelo conteúdo
    void remove(const T& data);

    // Lista vazia
    bool empty() const;

    // Contém
    bool contains(const T& data) const;

    // Achar índice do dado
    size_t find(const T& data) const;

    // Retorna tamanho da lista
    size_t size() const;

 private:
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
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
            return next_;
        }

        // setter do ponteiro para o próximo
        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* end() {
        auto it = head;
        for (auto i = 1u; i < size(); ++i)
            it = it -> next();
        return it;
    }

    Node* head{nullptr};
    size_t size_{0u};
};

}  // namespace structures

#endif

// IMPLEMENTAÇÃO DOS MÉTODOS
template<typename T>
structures::LinkedList<T>::LinkedList() {
    size_ = 0;
}

template<typename T>
structures::LinkedList<T>::~LinkedList() {
    clear();
}

template<typename T>
void structures::LinkedList<T>::clear() {
    while (!empty())
        pop_front();
}

template <typename T>
void structures::LinkedList<T>::push_back(const T& data) {
    if (empty())
        return push_front(data);

    Node* p = head;
    Node* novo = new Node(data);

    while (p -> next() != nullptr) {
        p = p -> next();
    }

    p->next(novo);
    size_++;
}

template<typename T>
void structures::LinkedList<T>::push_front(const T& data) {
    Node *new_node = new Node(data, head);
    head = new_node;
    size_++;
}

template<typename T>
void structures::LinkedList<T>::insert(const T& data, size_t index) {
    if (index < 0 || index > size_)
        throw std::out_of_range("Índice inválido");
    if (index == 0)
        return push_front(data);
    if (index == size_)
        return push_back(data);

    Node *p = head;
    for (int i = 1; i < static_cast<int>(index); i++)
        p = p -> next();

    Node *new_node = new Node(data, p -> next());
    p -> next(new_node);
    size_++;
}

template<typename T>
void structures::LinkedList<T>::insert_sorted(const T& data) {
    Node *p = head;

    if (empty() || p -> data() > data)
        return push_front(data);

    while (p -> next() != nullptr && data > p -> next() -> data()) {
        p = p -> next();
    }

    if (p -> next() == nullptr)  // p está no último nodo
        return push_back(data);
    Node *new_node = new Node(data, p -> next());
    p -> next(new_node);
    size_++;
}

template<typename T>
T& structures::LinkedList<T>::at(size_t index) {
    if (empty())
        throw std::out_of_range("Lista vazia");
    if (index < 0 || index >= size_)
        throw std::out_of_range("Índice inválido");

    Node *p = head;
    for (int i = 0; i < static_cast<int>(index); i++)
        p = p -> next();

    return p -> data();
}

template<typename T>
T structures::LinkedList<T>::pop(size_t index) {
    if (empty())
        throw std::out_of_range("Lista vazia");
    if (index < 0 || index >= size_)
        throw std::out_of_range("Índice inválido");
    if (size_ == 1)
        return pop_front();
    if (index == (size_ - 1))
        return pop_back();

    Node *p = head;
    for (int i = 1; i < static_cast<int>(index); i++) {
        p = p -> next();
    }

    Node *aux = p -> next();
    T saida = aux -> data();
    p -> next(aux -> next());
    delete aux;
    size_--;
    return saida;
}

template<typename T>
T structures::LinkedList<T>::pop_front() {
    if (empty())
        throw std::out_of_range("Lista vazia");

    Node *aux = head;
    T saida = aux -> data();
    head = aux -> next();
    delete aux;
    size_--;
    return saida;
}

template<typename T>
T structures::LinkedList<T>::pop_back() {
    if (empty())
        throw std::out_of_range("Lista vazia");
    if (size_ == 1)
        return pop_front();

    Node *p = head;
    while (p -> next() -> next() != nullptr)
        p = p -> next();

    T saida = p -> next() -> data();
    delete p -> next();
    p -> next(nullptr);
    size_--;
    return saida;
}

template<typename T>
void structures::LinkedList<T>::remove(const T& data) {
    if (empty())
        throw std::out_of_range("Lista vazia");

    Node *p = head;
    for (int i = 0; i < static_cast<int>(size_); i++) {
        if (p -> data() == data) {
            pop(i);
            break;
        }
        p = p -> next();
    }
}

template<typename T>
bool structures::LinkedList<T>::empty() const {
    return (size_ == 0);
}

template<typename T>
bool structures::LinkedList<T>::contains(const T& data) const {
    return (find(data) != size_);
}

template<typename T>
size_t structures::LinkedList<T>::find(const T& data) const {
    if (empty())
        throw std::out_of_range("Lista vazia");

    Node *p = head;
    while (p != nullptr && p -> data() != data)
        p = p -> next();

    return p == nullptr ? size_ : p -> data();
}

template<typename T>
size_t structures::LinkedList<T>::size() const {
    return size_;
}
