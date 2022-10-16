// Copyright [2022] <Eduardo Perottoni>


#ifndef STRUCTURES_DOUBLY_LINKED_LIST_H
#define STRUCTURES_DOUBLY_LINKED_LIST_H


#include <cstdint>

namespace structures {

template<typename T>
class DoublyLinkedList {
 public:
    // Construtor
    DoublyLinkedList();
    // Destrutor
    ~DoublyLinkedList();
    // Limpa a lista
    void clear();

    // Insere no final da lista
    void push_back(const T& data);
    // Insere no início da lista
    void push_front(const T& data);
    // Insere em qualquer posição da lista
    void insert(const T& data, std::size_t index);
    // Insere ordenado
    void insert_sorted(const T& data);

    // Retira da posição passada
    T pop(std::size_t index);
    // Retira da frente
    T pop_front();
    // Retira de trás
    T pop_back();
    // Remove elemento com o dado passado
    void remove(const T& data);

    // Teste vazio
    bool empty() const;
    // Teste contém
    bool contains(const T& data) const;

    // Retorna dado na posição passada
    T& at(std::size_t index);
    // Retorna dado na posição constante
    const T& at(std::size_t index) const;

    // Retorna posição de um dado
    std::size_t find(const T& data) const;
    // Retorna tamanho
    std::size_t size() const;

 private:
    class Node {
     private:
        T data_;
        Node *prev_, *next_;

     public:
        // Construtor padrão
        explicit Node(const T& data) {
            data_ = data;
        }
        Node(const T& data, Node* next) {
            data_ = data;
            next_ = next;
        }
        Node(const T& data, Node* prev, Node* next) {
            data_ = data;
            prev_ = prev;
            next_ = next;
        }
        // data getter
        T& data() {
            return data_;
        }
        const T& data() const {
            return data_;
        }
        // next getter
        Node* next() {
            return next_;
        }
        const Node* next() const {
            return next_;
        }
        // next setter
        void next(Node* node) {
            next_ = node;
        }
        // prev getter
        Node* prev() {
            return prev_;
        }
        const Node* prev() const {
            return prev_;
        }
        // prev setter
        void prev(Node* node) {
            prev_ = node;
        }
    };
    Node *head, *tail;
    std::size_t size_;
    Node* position(std::size_t index) {
        if (static_cast<int>(index) < 0 || index > size_)
            throw std::out_of_range("Índice inválido");
        Node* p = nullptr;
        if (index < size_ / 2) {
            p = head;
            for (int i = 0; i < static_cast<int>(index); i++)
                p = p -> next();
        } else {
            p =  tail;
            for (int i = static_cast<int>(size_) - 1;
            i > static_cast<int>(index); i--)
                p = p -> prev();
        }
        return p;
    }
};
}  // namespace structures

#endif

// IMPLEMENTAÇÃO DOS MÉTODOS
template<typename T>
structures::DoublyLinkedList<T>::DoublyLinkedList() {
    size_ = 0;
    head = nullptr;
    tail = nullptr;
}

template<typename T>
structures::DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

template<typename T>
void structures::DoublyLinkedList<T>::clear() {
    while (!empty())
        pop_front();
}

template<typename T>
void structures::DoublyLinkedList<T>::push_back(const T& data) {
    if (empty())
        return push_front(data);
    Node* novo = new Node(data,  tail, nullptr);
    tail -> next(novo);
    tail = novo;
    size_++;
}

template<typename T>
void structures::DoublyLinkedList<T>::push_front(const T& data) {
    Node* novo = new Node(data, nullptr, head);
    if (empty())
        tail = novo;
    else
        head -> prev(novo);
    head = novo;
    size_++;
}


template<typename T>
void structures::DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
    if (index < 0 || index > size_)
        throw std::out_of_range("Índice inválido");
    if (index == 0)
        return push_front(data);
    if (index == size_)
        return push_back(data);
    Node* p = position(index - 1);
    Node* novo = new Node(data, p, p -> next());
    novo -> next() -> prev(novo);
    p -> next(novo);
    size_++;
}

template<typename T>
void structures::DoublyLinkedList<T>::insert_sorted(const T& data) {
    if (empty() || data < head -> data())
        return push_front(data);
    if (data > tail -> data())
        return push_back(data);
    Node *p = head;
    while (p -> next() != nullptr && p ->  next() -> data() < data) {
        p = p -> next();
    }
    Node *novo = new Node(data, p, p -> next());
    novo -> next() -> prev(novo);
    novo -> prev() -> next(novo);
    size_++;
}

template<typename T>
T structures::DoublyLinkedList<T>::pop(std::size_t index) {
    if (empty())
        throw std::out_of_range("Lista vazia");
    if ( index < 0 || index > size_ - 1)
        throw std::out_of_range("Índice inválido");
    if (index == 0)
       return pop_front();
    if (index == size_ - 1)
        return pop_back();
    Node *p = position(index);
    T data = p -> data();
    p -> next() -> prev(p -> prev());
    p -> prev() -> next(p -> next());
    delete p;
    size_--;
    return data;
}

template<typename T>
T structures::DoublyLinkedList<T>::pop_front() {
    if (empty())
        throw std::out_of_range("Lista vazia");

    Node *p = head;
    T data = p -> data();
    if (size_ == 1) {
        head = nullptr;
        tail = nullptr;
    } else {
        head = p -> next();
        p -> next() -> prev(nullptr);
    }
    delete p;
    size_--;
    return data;
}

template<typename T>
T structures::DoublyLinkedList<T>::pop_back() {
    if (empty())
        throw std::out_of_range("Lista vazia");
    if (size_ == 1)
        return pop_front();
    Node *p = tail;
    T data = p -> data();
    p -> prev() -> next(nullptr);
    tail = p -> prev();
    delete p;
    size_--;
    return data;
}

template<typename T>
void structures::DoublyLinkedList<T>::remove(const T& data) {
    if (empty())
        throw std::out_of_range("Lista vazia");
    Node *p = head;
    for (int i = 0; i < static_cast<int>(size_) - 1; i++) {
        if (p -> data() == data) {
            pop(i);
            break;
        }
        p = p -> next();
    }
}

template<typename T>
bool structures::DoublyLinkedList<T>::empty() const {
    return (static_cast<int>(size_) == 0);
}

template<typename T>
bool structures::DoublyLinkedList<T>::contains(const T& data) const {
    if (empty())
        throw std::out_of_range("Lista vazia");
    Node* p = head;
    for (int i = 0; i < static_cast<int>(size_); i++) {
        if (p -> data() == data)
            return true;
        p = p -> next();
    }
    return false;
}

template<typename T>
std::size_t structures::DoublyLinkedList<T>::find(const T& data) const {
    if (empty())
        throw std::out_of_range("Lista vazia");
    Node *p = head;
    for (int i = 0; i < static_cast<int>(size_); i++) {
        if (p -> data() == data)
            return (std::size_t)i;
        p = p -> next();
    }
    return size_;
}

template<typename T>
T& structures::DoublyLinkedList<T>::at(std::size_t index) {
	Node *p = position(index);
	return p -> data();
}

template<typename T>
const T& structures::DoublyLinkedList<T>::at(std::size_t index) const {
    Node *p = position(index);
    return p -> data();
}

template<typename T>
std::size_t structures::DoublyLinkedList<T>::size() const {
    return size_;
}
