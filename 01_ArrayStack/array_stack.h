// Copyright [2022] <EDUARDO PEROTTONI>

#ifndef STRUCTURES_ARRAY_STACK_H
// Caso header já tenha sido carregado anteriormente
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>  // importa o size_t
#include <stdexcept>  // importa exceções

namespace structures {
template<typename T>

// DEFINICAO DOS MÉTODOS
class ArrayStack {
 public:
    // Construtor
    ArrayStack();
    // Construtor com parâmetro
    explicit ArrayStack(size_t max);
    // Destrutor
    ~ArrayStack();
    // Método de empilhamento
    void push(const T &data);
    // Método desempilha
    T pop();
    // Método que retorna o topo da stack
    T& top();
    // Método que limpa a pilha
    void clear();
    // Método que retorna tamanho da pilha
    size_t size();
    // Método que retorna capacidade máxima
    size_t max_size();
    // Método que retorna caso esteja vazia
    bool empty();
    // Método que retorna caso esteja cheia
    bool full();

 private:
    // Ponteiro para o array
    T *contents;
    // Topo
    int top_;
    // Tamanho máximo
    size_t max_size_;

    static const auto DEFAULT_SIZE = 10u;
};
}  // namespace structures

#endif

// IMPLEMENTAÇÃO DOS MÉTODOS:
template<typename T>
structures::ArrayStack<T>::ArrayStack() {
    contents = new T[DEFAULT_SIZE];
    top_ = -1;
}

template<typename T>
structures::ArrayStack<T>::ArrayStack(size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    top_ = -1;
}

template<typename T>
structures::ArrayStack<T>::~ArrayStack() {
    delete *contents;
}

template<typename T>
void structures::ArrayStack<T>::push(const T &data) {
    if (full())
        throw std::out_of_range("pilha cheia");
    top_++;
    contents[top_] = data;
}

template<typename T>
T structures::ArrayStack<T>::pop() {
    if (empty())
        throw std::out_of_range("pilha vazia");
    top_--;
    return contents[top_ + 1];
}

template<typename T>
T& structures::ArrayStack<T>::top() {
    if (empty())
        throw std::out_of_range("pilha vazia");
    return contents[top_];
}

template<typename T>
void structures::ArrayStack<T>::clear() {
    top_ = -1;
}

template<typename T>
size_t structures::ArrayStack<T>::size() {
    return top_ + 1;
}

template<typename T>
size_t structures::ArrayStack<T>::max_size() {
    return max_size_;
}

template<typename T>
bool structures::ArrayStack<T>::empty() {
    return (top_ == -1);
}

template<typename T>
bool structures::ArrayStack<T>::full() {
    return (top_ == static_cast<int>(max_size() - 1));
}

