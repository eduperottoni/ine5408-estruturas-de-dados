// Copyright [2022] <Eduardo Perottoni

#ifndef STRUCTURES_DOUBLY_CIRCULAR_LIST_H
#define STRUCTURES_DOUBLY_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {
template<typename T>
class DoublyCircularList {
 public:
    // Construtor
    DoublyCircularList();
    // Destrutor
    ~DoublyCircularList();
    // limpa a lista
    void clear();

    // Insere no início da lista
    void push_front(const T& data);
    // Insere no final da lista
    void push_back(const T& data);
    // Insere na posição passada
    void insert(const T& data, size_t index);
    // Insere ordenado
    void insert_sorted(const T& data);

    // Retira do início
    T pop_front();
    // Retira do final
    T pop_back();
    // Retira da posição
    T pop(size_t index);
    // Retira por consulta de dado
    void remove(const T& data);

    // Consulta existência de dado
    bool contains(const T& data) const;
    // Consulta índice de dado
    size_t find(const T& data) const;
    // Teste de vazio
    bool empty() const;

    // Acesso por índice
    T& at(size_t index);
    // Acesso por índice const
    const T& at(size_t index) const;

    // Tamanho da lista
    size_t size() const;

 private:
    class Node {
     public:
        // Constrututor
        explicit Node(const T& data):
            data_{data}
        {}
        // Construtor com next e data
        Node(const T& data, Node* next):
            next_{next},
            data_{data}
        {}
        // Construtor com data, prev e next
        Node(const T& data, Node* prev, Node* next):
            next_{next},
            prev_{prev},
            data_{data}
        {}
        // getter de data
        T& data() {
            return data_;
        }
        // getter de data const
        const T& data() const {
            return data_;
        }
        // getter de next
        Node* next() {
            return next_;
        }
        // getter de next const
        const Node* next() const {
            return next_;
        }
        // setter de next
        void next(Node* node) {
            next_ = node;
        }
        // getter de prev
        Node* prev() {
            return prev_;
        }
        // getter de prev const
        const Node* prev() const {
            return prev_;
        }
        // setter de prev
        void prev(Node* node) {
            prev_ = node;
        }

     private:
        T data_;
        Node *next_, *prev_;
    };

    Node *head{nullptr};
    size_t size_{0u};

    // Retorna ponteiro para o nó no índice solicitado
    Node* position(std::size_t index) {
        if (static_cast<int>(index) < 0 || index > size_)
            throw std::out_of_range("Índice inválido");
        if (index == 0)
            return head;
        if (index == size_ - 1)
            return head -> prev();
        Node* p = nullptr;
        if (index < size_ / 2) {
            p = head;
            for (int i = 0; i < static_cast<int>(index); i++)
                p = p -> next();
        } else {
            p =  head -> prev();
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
structures::DoublyCircularList<T>::DoublyCircularList() {
    size_ = 0;
}

template<typename T>
structures::DoublyCircularList<T>::~DoublyCircularList() {
    clear();
}

template<typename T>
void structures::DoublyCircularList<T>::clear() {
    while (!empty())
        pop_front();
}

template<typename T>
T structures::DoublyCircularList<T>::pop_front() {
    if (empty())
        throw std::out_of_range("Lista vazia");

    Node *aux = head;
    T data = aux -> data();
    if (size_ == 1) {
        head = nullptr;
    } else {
        head = aux -> next();
        head -> prev(aux -> prev());
        aux -> prev() -> next(head);
    }
    delete aux;
    size_--;
    return data;
}

template<typename T>
T structures::DoublyCircularList<T>::pop_back() {
    if (empty())
        throw std::out_of_range("Lista vazia");
    if (size_ == 1)
        return pop_front();

    Node* aux = head -> prev();
    T data = aux -> data();
    aux -> prev() -> next(head);
    head -> prev(aux -> prev());
    delete aux;
    size_--;
    return data;
}

template<typename T>
T structures::DoublyCircularList<T>::pop(size_t index) {
    if (index > size_ - 1 || index < 0)
        throw std::out_of_range("Índice inválido");
    if (index == 0)
        return pop_front();
    if (index == size_ - 1)
        return pop_back();

    Node *aux = position(index);
    T data = aux -> data();
    aux -> prev() -> next(aux -> next());
    aux -> next() -> prev(aux -> prev());
    delete aux;
    size_--;
    return data;
}

template<typename T>
void structures::DoublyCircularList<T>::remove(const T& data) {
    Node* aux = head;
    for (int i = 0; (size_t)i < size_ - 1; i++) {
        if (aux -> data() == data) {
            pop(i);
            break;
        }
        aux = aux -> next();
    }
}

template<typename T>
void structures::DoublyCircularList<T>::push_front(const T& data) {
    Node *novo = new Node(data);
    if (novo == nullptr)
        throw std::out_of_range("Memória cheia");

    if (empty()) {
        head = novo;
        novo -> prev(novo);
        novo -> next(novo);
    } else {
        novo -> prev(head -> prev());
        head -> prev() -> next(novo);
        head -> prev(novo);
        novo -> next(head);
        head = novo;
    }
    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::push_back(const T& data) {
    if (empty())
        return push_front(data);

    Node *novo = new Node(data);
    if (novo == nullptr)
        throw std::out_of_range("Memória cheia");

    head -> prev() -> next(novo);
    novo -> prev(head -> prev());
    head -> prev(novo);
    novo -> next(head);

    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::insert(const T& data, size_t index) {
    if (index < 0 || index > size_)
        throw std::out_of_range("Índice inválido");
    if (index == 0)
        return push_front(data);
    if (index == size_)
        return push_back(data);

    Node* aux = position(index - 1);
    Node* novo = new Node(data);
    if (novo == nullptr)
        throw std::out_of_range("Memória cheia");

    novo -> next(aux -> next());
    novo -> prev(aux);
    aux -> next(novo);
    novo -> next() -> prev(novo);
    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::insert_sorted(const T& data) {
    if (empty() || data <= head -> data())
        return push_front(data);
    if (data > head -> prev() -> data())
        return push_back(data);

    Node *aux = head -> next();
    for (int i = 1; (size_t)i < size_; i++) {
        if (data <= aux -> data()) {
            return insert(data, (size_t)i);
        }
        aux = aux -> next();
    }
    size_++;
}

template<typename T>
bool structures::DoublyCircularList<T>::contains(const T& data) const {
    return (find(data) != size_);
}

template<typename T>
size_t structures::DoublyCircularList<T>::find(const T& data) const {
    Node *aux = head;
    for (int i = 0; (size_t)i < size_; i++) {
        if (aux -> data() == data)
            return (size_t)i;
        aux = aux -> next();
    }
    return (size_);
}

template<typename T>
T& structures::DoublyCircularList<T>::at(size_t index) {
    Node* aux = position(index);
    return aux -> data();
}

template<typename T>
const T& structures::DoublyCircularList<T>::at(size_t index) const {
    Node* aux = position(index);
    return aux -> data();
}

template<typename T>
size_t structures::DoublyCircularList<T>::size() const {
    return size_;
}

template<typename T>
bool structures::DoublyCircularList<T>::empty() const {
    return (size_ == 0);
}
