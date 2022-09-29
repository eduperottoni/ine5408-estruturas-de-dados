// COPYRIGHT [2022] <EDUARDO PEROTTONI>

#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>
#include <stdexcept>  // importa exceções

namespace structures {

template<typename T>
class ArrayList {
 public:
    // Construtor padrão
    ArrayList();
    // Construtor com argumento
    explicit ArrayList(size_t max);
    // Destrutor
    ~ArrayList();

    // Limpar lista
    void clear();
    // Inserir no final da lista
    void push_back(const T& data);
    // Inserir no início da lista
    void push_front(const T& data);
    // Inserir em qualquer posição
    void insert(const T& data, size_t index);
    // Inserir em uma lista que é ordenada
    void insert_sorted(const T& data);
    // Remover e retornar elemento em qualquer índice
    T pop(size_t index);
    // Remover e retornar o primeiro elemento
    T pop_front();
    // Remover e retornar o último elemento
    T pop_back();
    // Remover primeira ocorrência de dado valor
    void remove(const T& data);
    // Checagem de estrutura cheia
    bool full() const;
    // Checagem de estrutura vazia
    bool empty() const;
    // Checagem se lista contém valor
    bool contains(const T& data) const;
    // Buscar primiera ocorrência de elemento
    size_t find(const T& data) const;
    // Retornar tamanho da lista
    size_t size() const;
    // Retornar tamanho máximo da lista
    size_t max_size() const;
    // Retornar elemento em dado índice
    T& at(size_t index);
    // Redefinição do operador[]
    T& operator[](size_t index);
    // Retornar elemento de dado índice (que não pode ser modiicado)
    const T& at(size_t index) const;
    // Redefinição de operador (para dados imutáveis)
    const T& operator[](size_t index) const;

 private:
    T* contents;
    size_t size_;
    size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};

}  // namespace structures


// IMPLEMENTAÇÃO DOS MÉTODOS
template<typename T>
structures::ArrayList<T>::ArrayList() {
    max_size_ = DEFAULT_MAX;
    contents = new T[max_size_];
    size_ = 0;
}

template<typename T>
structures::ArrayList<T>::ArrayList(size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    size_ = 0;
}

template<typename T>
structures::ArrayList<T>::~ArrayList() {
    delete [] contents;
}

template<typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    if (full())
        throw std::out_of_range("lista cheia");
    contents[size_++] = data;
}

template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    if (full())
        throw std::out_of_range("lista cheia");
    for (int i = static_cast<int>(size_++); i >= 1; i--)
        contents[i] = contents[i-1];
    contents[0] = data;
}

template<typename T>
void structures::ArrayList<T>::insert(const T& data, size_t index) {
    if (full() || static_cast<int>(index) < 0 || index >= max_size_)
        throw std::out_of_range("lista cheia");
    for (int i = static_cast<int>(size_++); i > static_cast<int>(index); i--)
        contents[i] = contents[i-1];
    contents[index] = data;
}

template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    if (full())
        throw std::out_of_range("lista cheia");
    int i = 0;
    while (i < static_cast<int>(size_) && data > contents[i]) {
        i++;
    }
    return insert(data, static_cast<size_t>(i));
}

template<typename T>
T structures::ArrayList<T>::pop(size_t index) {
    if (empty())
        throw std::out_of_range("lista vazia");
    else if (index >= size_ || static_cast<int>(index) < 0)
        throw std::out_of_range("index fora da lista");

    T aux = contents[index];
    for (int i = index; i < (static_cast<int>(size_) - 1); i++)
        contents[i] = contents[i + 1];
    size_--;
    return aux;
}

template<typename T>
T structures::ArrayList<T>::pop_front() {
    return pop(0);
}

template<typename T>
T structures::ArrayList<T>::pop_back() {
    return pop(size_ - 1);
}

template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
    if (empty())
        throw std::out_of_range("lista vazia");
    for (int i = 0; i < static_cast<int>(size_); i++)
        if (contents[i] == data) {
            pop(i);
        }
}

template<typename T>
bool structures::ArrayList<T>::full() const {
    return (size_ == max_size_);
}

template<typename T>
bool structures::ArrayList<T>::empty() const {
    return (static_cast<int>(size_) == 0);
}

template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    return (find(data) != size_);
}

template<typename T>
size_t structures::ArrayList<T>::find(const T& data) const {
    if (empty())
        throw std::out_of_range("lista vazia");

    for (int i = 0; i < static_cast<int>(size_); i++)
        if (contents[i] == data)
            return i;

    return size_;
}

template<typename T>
size_t structures::ArrayList<T>::size() const {
    return size_;
}

template<typename T>
size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}

template<typename T>
T& structures::ArrayList<T>::at(size_t index) {
    if (index > max_size_ || index < 0) {
        throw std::out_of_range("Erro na posição");
    }
    return contents[index];
}

template<typename T>
T& structures::ArrayList<T>::operator[](size_t index) {
    return at(index);
}

template<typename T>
const T& structures::ArrayList<T>::at(size_t index) const {
    if (index > max_size_ || index < 0) {
        throw std::out_of_range("Erro de posição");
    }
    return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>::operator[](size_t index) const {
    return at(index);
}

#endif
