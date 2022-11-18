// COPYRIGHT [2022] <EDUARDO PEROTTONI>
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "array_list.h"

namespace structures {

template<typename T>
class BinaryTree {
 public:
    // Construtor
    BinaryTree();
    // Destrutor
    ~BinaryTree();
    // Insere
    void insert(const T& data);
    // Remove
    void remove(const T& data);
    // Testa se árvore contém o dado
    bool contains(const T& data) const;
    // Testa se está vazia
    bool empty() const;
    // Tamanho da arvore
    size_t size() const;
    // Algoritmo de percurso pré-ordem
    ArrayList<T> pre_order() const;
    // Algoritmo de percurso em ordem
    ArrayList<T> in_order() const;
    // Algoritmo de percurso pós-ordem
    ArrayList<T> post_order() const;

 private:
    struct Node {
        explicit Node(const T& data) {
            data_ = data;
            left = nullptr;
            right = nullptr;
        }

        T data_;
        Node* left;
        Node* right;

        // Retorna o nó mais à esquerda da árvore
        Node* minimum() {
            if (left)
                return left -> minimum();
            else
                return this;
        }

        // Insere nó a partir do nó raiz
        void insert(const T& data) {
            if (data_ > data) {
                if (!left)
                    left = new Node(data);
                else
                    left -> insert(data);
            } else {
                if (!right)
                    right = new Node(data);
                else
                    right -> insert(data);
            }
        }

        // Remove nó a partir dessa sub-árvore
        Node* remove(const T& data) {
            // Caso o dado esteja à esquerda
            if (data_ > data) {
                if (left) {
                    left = left -> remove(data);
                    return this;
                } else {
                    return nullptr;
                }
            // Caso do dado esteja à direita
            } else if (data_ < data) {
                if (right) {
                    right = right -> remove(data);
                    return this;
                } else {
                    return nullptr;
                }
            // Caso este nó contenha o dado
            } else {
                // Se o node tem direita e esquerda
                if (right && left) {
                    Node* tmp = right -> minimum();
                    data_ = tmp -> data_;
                    right = right -> remove(data);
                    return this;
                // Se o node tem apenas direita
                } else if (right) {
                    Node* tmp = right;
                    delete this;
                    return tmp;
                // Se o node tem apenas esquerda
                } else if (left) {
                    Node* tmp = left;
                    delete this;
                    return tmp;
                // Caso em que o nó é folha
                } else {
                    delete this;
                    return nullptr;
                }
            }
        }

        // Teste se subárvore contém info
        bool contains(const T& data) const {
            // Se o valor estiver na raíz
            if (data == data_)
                return true;
            // Se o valor é menor e há subárvore à esquerda
            else if (data < data_ && left)
                return left -> contains(data);
            // Se o valor é maior e há subárvore à direita
            else if (data > data_ && right)
                return right -> contains(data);

            // Caso em que é folha e não tem o valor
            return false;
        }

        // Algoritmo de pré-ordem
        void pre_order(ArrayList<T>& v) const {
            // Insere raíz da subárvore
            v.push_back(data_);
            // Chama para esquerda
            if (left)
                left -> pre_order(v);
            // Chama para direita
            if (right)
                right -> pre_order(v);
        }

        // Algoritmo em ordem
        void in_order(ArrayList<T>& v) const {
            // Chama para esquerda
            if (left)
                left -> in_order(v);
            v.push_back(data_);
            // Chama para direita
            if (right)
                right -> in_order(v);
        }

        // Algoritmo de pós-ordem
        void post_order(ArrayList<T>& v) const {
            // Chama para esquerda
            if (left)
                left -> post_order(v);
            // Chama para direita
            if (right)
                right -> post_order(v);
            // Insere raiz
            v.push_back(data_);
        }
    };

    Node* root;
    size_t size_;
};

}  // namespace structures

// IMPLEMENTAÇÃO DOS MÉTODOS

template<typename T>
structures::BinaryTree<T>::BinaryTree() {
    root = nullptr;
    size_ = 0;
}

template<typename T>
structures::BinaryTree<T>::~BinaryTree() {
    if (root) {
        structures::ArrayList<T> nodes_list = pre_order();

        while (size_)
            remove(nodes_list.pop_back());
    }
}

template<typename T>
void structures::BinaryTree<T>::insert(const T& data) {
    if (contains(data)) {
        throw std::out_of_range("Elemento já está na árvore");
    }

    if (root)
        root -> insert(data);
    else
        root = new Node(data);

    size_++;
}

template<typename T>
void structures::BinaryTree<T>::remove(const T& data) {
    if (!root)
        throw std::out_of_range("Árvore vazia");
    else if (!contains(data))
        throw std::out_of_range("Dado não está contido na árvore");

    root -> remove(data);
    size_--;
}

template<typename T>
bool structures::BinaryTree<T>::contains(const T& data) const {
    if (root)
        return root -> contains(data);
    return false;
}

template<typename T>
bool structures::BinaryTree<T>::empty() const {
    return static_cast<int>(size_) == 0;
}

template<typename T>
size_t structures::BinaryTree<T>::size() const {
    return size_;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::pre_order() const {
    if (!root)
        throw std::out_of_range("Árvore vazia");

    structures::ArrayList<T> v;
    root -> pre_order(v);

    return v;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::in_order() const {
    if (!root)
        throw std::out_of_range("Árvore vazia");

    structures::ArrayList<T> v;
    root -> in_order(v);

    return v;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::post_order() const {
    if (!root)
        throw std::out_of_range("Árvore vazia");

    structures::ArrayList<T> v;
    root -> post_order(v);

    return v;
}

#endif  // endif
