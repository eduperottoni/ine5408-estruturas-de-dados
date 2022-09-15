// Copyright [2022] <EDUARDO PEROTTONI>
#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>  // importa o size_t
#include <stdexcept>  // importa exceções

namespace structures {

template<typename T>

class ArrayQueue {
 public:
    // Construtor
    ArrayQueue();
    // Construtor com parâmetro
    explicit ArrayQueue(size_t max);
    // Destrutor
    ~ArrayQueue();
    // Enfileirar
    void enqueue(const T& data);
    // Desenfileirar
    T dequeue();
    // Retornar o último da fila
    T& back();
    // Limpar a fila
    void clear();
    // Retornar o tamanho atual
    std::size_t size();
    // Retorna o tamanho máximo
    std::size_t max_size();
    // Verificar se é vazia
    bool empty();
    // Verifica se está cheio
    bool full();

 private:
    T* contents;
    std::size_t max_size_;
    std::size_t size_;
    int begin_;
    int end_;
    static const auto DEFAULT_SIZE = 10u;
};

}  // namespace structures

#endif

// IMPLEMENTAÇÃO DOS MÉTODOS
template<typename T>
structures::ArrayQueue<T>::ArrayQueue() {
    // max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    begin_ = 0;
    end_ = -1;
    size_ = 0;
}

template<typename T>
structures::ArrayQueue<T>::ArrayQueue(size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    begin_ = 0;
    end_ = -1;
    size_ = 0;
}

template<typename T>
structures::ArrayQueue<T>::~ArrayQueue() {
    delete [] contents;
}

template<typename T>
void structures::ArrayQueue<T>::enqueue(const T& data) {
    if (full())
        throw std::out_of_range("fila cheia");
    end_ = (end_ + 1) % max_size_;
    contents[end_] = data;
    size_++;
}

template<typename T>
T structures::ArrayQueue<T>::dequeue() {
    if (empty())
        throw std::out_of_range("fila vazia");
    T elemento = contents[begin_];
    begin_ = (begin_ + 1) % max_size_;
    size_--;
    return elemento;
}

template<typename T>
T &structures::ArrayQueue<T>::back() {
    if (empty())
        throw std::out_of_range("fila vazia");
    return contents[end_];
}

template<typename T>
void structures::ArrayQueue<T>::clear() {
    size_ = 0;
}

template<typename T>
size_t structures::ArrayQueue<T>::size() {
    return size_;
}

template<typename T>
size_t structures::ArrayQueue<T>::max_size() {
    return max_size_;
}

template<typename T>
bool structures::ArrayQueue<T>::empty() {
    return (size_ == 0);
}

template<typename T>
bool structures::ArrayQueue<T>::full() {
    return (size_ == max_size_);
}
