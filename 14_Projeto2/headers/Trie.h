// Copyright [2022] Caio Prá Silva & Eduardo Dani Perotonni

#ifndef STRUCTURES_TRIE_H
#define STRUCTURES_TRIE_H
#define ALPHABET_SIZE 26

#include <stdlib.h>

#include <iostream>
#include <string>
#include <tuple>

using namespace std;

namespace structures {

class Trie {
   public:
    /**
     * @brief Construtor da Trie
     * @return Trie
     */
    Trie();

    /**
     * @brief Insere uma palavra na Trie
     * @param word Palavra a ser inserida na Trie
     * @param size Tamanho da linha que contém o significado da palavra
     * @param index Índice em que a palavra se encontra no dicionário
     */
    void insert(string& word, size_t size, size_t index);

    /**
     * @brief Pesquisa palavra na Trie
     * @param word Palavra a ser encontrada
     * @return Tupla com dois valores do tipo size_t
     * 1º valor -> posição da palavra no dicionário.
     * 2º valor -> tamanho da linha da palavra.
     * Se 1º valor == -1 && 2º valor == -1 -> palavra não está no dicionário.
     * Se 1º valor == 0 && 2º valor == 0 -> palavra é prefixo.
     */
    tuple<size_t, size_t> search(string& string);

    /**
     * @brief Conta de quantas palavras a palavra dada é prefixo
     * @param prefix Palavra prefixo
     * @return size_t com quantidade de palavras cujo prefix é prefixo
     */
    size_t count_prefixed_words(string& prefix);

   private:
    class TrieNode {
       public:
        /**
         * @brief Construtor de TriNode
         * @return Trie criado
         */
        TrieNode() {
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                children[i] = nullptr;
            }
        }

        /**
         * @brief Get do children
         * @return TrieNode* children
         */
        TrieNode* get_children(size_t index) {
            return children[index];
        }

        /**
         * @brief Insere ponteiro para letra em children
         * @param index Índice de children a inserir ponteiro
         * @param new_node Ponteiro para o novo node
         */
        void set_children(size_t index, TrieNode* new_node) {
            children[index] = new_node;
        }

        /**
         * @brief Get do índice
         * @return Índice da palavra que termina no nó
         */
        size_t get_dict_index() {
            return dict_index;
        }

        /**
         * @brief Set do índice da palavra que finaliza no node
         * @param new_dict_index Novo índice para a palavra que termina no Node
         */
        void set_dict_index(size_t& new_dict_index) {
            dict_index = new_dict_index;
        }

        /**
         * @brief Get de length
         * @return Comprimento da linha da palavra no dicionário
         */
        size_t get_length() {
            return line_length;
        }

        /**
         * @brief Set do comprimento da linha que explica a palavra
         * @param new_length Novo comprimento de linha para a palavra que termina no Node
         */
        void set_line_length(size_t& new_length) {
            line_length = new_length;
        }

        /**
         * @brief Get da quantidade de filhos diretos que o TrieNode possui
         * @return size_t: quantidade de filhos diretos (armazenados em children[])
         */
        size_t get_children_amount() {
            return children_amount;
        }

        /**
         * @brief Incrementa em 1 a quantidade de filhos diretos do TrieNode
         * 
         */
        void increment_children_amount() {
            children_amount++;
        }

        /**
         * @brief Get indicando se o TrieNode indica que pode terminar ali e formar uma palavra
         * 
         * @return true caso seja última letra de alguma palavra do dicionário
         * @return false caso não seja última letra de nenhuma palavra
         */
        bool get_is_final_node() {
            return is_final_node;
        }

        /**
         * @brief Altera o estado do nodo ser ou não fim de alguma palavra
         * 
         * @param state booleano indicando se é ou não fim
         */
        void set_is_final_node(bool state) {
            is_final_node = state;
        }

        /**
         * @brief Conta quantas palavras estão abaixo do TrieNode que invoca o método
         * @return size_t com o número de palavras abaixo do node
         */
        size_t count_words_below() {
            size_t counted_words = 0;
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                if (children[i]) {
                    // Se filho é final de palavra
                    // if (children[i]->get_length())
                    if (children[i]->get_is_final_node())
                        counted_words++;
                    counted_words += children[i]->count_words_below();
                }
            }
            return counted_words;
        }

       private:
        TrieNode* children[ALPHABET_SIZE];
        size_t dict_index{0}, line_length{0}, children_amount{0};
        // indica se o TrieNode é final para alguma palavra
        bool is_final_node{false};
    };

    TrieNode* root{nullptr};
};

}  // namespace structures

#endif

// IMPLEMENTAÇÃO DOS MÉTODOS DE TRIE

structures::Trie::Trie() {
    root = new TrieNode;
}

void structures::Trie::insert(string& word, size_t line_size, size_t dict_index) {
    TrieNode* current_node = root;

    for (int i = 0; i < word.length(); i++) {
        size_t children_position = word[i] - 'a';
        // Se node atual não tem ponteiro para letra
        if (!current_node->get_children(children_position)) {
            current_node->set_children(children_position, new TrieNode);
            current_node->increment_children_amount();
        }
        current_node = current_node->get_children(children_position);
    }
    current_node->set_dict_index(dict_index);
    current_node->set_line_length(line_size);
    current_node->set_is_final_node(true);
    cout << "Palavra " << word << " inserida!\n";
}

tuple<size_t, size_t> structures::Trie::search(string& word) {
    tuple<size_t, size_t> res;
    TrieNode* current = root;

    for (int i = 0; i < word.length(); i++) {
        size_t children_position = word[i] - 'a';

        // Caso a palavra não exista no dicionário
        if (!current->get_children(children_position)) {
            get<0>(res) = -1;
            get<1>(res) = -1;
            return res;
        }
        current = current->get_children(children_position);
    }
    // Caso a palavra pesquisada seja prefixo
    if (current->get_length() == 0) {
        get<0>(res) = 0;
        get<1>(res) = 0;
        return res;
    }
    // Caso a palavra exista e não seja prefixo
    get<0>(res) = current->get_dict_index();
    get<1>(res) = current->get_length();
    return res;
}


size_t structures::Trie::count_prefixed_words(string& prefix) {
    // verifica se o prefixo aparece alguma vez no dicionário
    tuple<size_t, size_t> search_result = search(prefix);
    if (get<0>(search_result) == -1 && get<1>(search_result) == -1)  {
        return 0;
    }
    
    int prefix_count = 0;

    TrieNode* last_letter = root;
    // percorre até a última letra da palavra (TrieNode)
    for (int i = 0; i < prefix.length(); i++) {
        size_t children_position = prefix[i] - 'a';
        last_letter = last_letter->get_children(children_position);
    }

    /*
        Para cada letra depois da última do prefixo, 
        soma a quantidade de palavras que cada um dele possui
    */
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (last_letter->get_children(i)) {
            prefix_count += last_letter->get_children(i)->count_words_below();
        }
    }
    // se o prefixo for uma palavra, conta como prefixo
    if (last_letter->get_is_final_node()) {
        prefix_count++;
    }

    return prefix_count;
}

