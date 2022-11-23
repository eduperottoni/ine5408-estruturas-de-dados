#include <fstream>
#include <iostream>

#include "headers/Trie.h"

using namespace structures;

Trie trie = Trie();

// função auxiliar para realizar os prints das palavras passadas
void word_prints(string& word) {
    int prefix_amout = trie.count_prefixed_words(word);
    if (prefix_amout > 0) {
        cout << word << " is prefix of " << prefix_amout << " words" << endl;
    } else {
        cout << word << " is not prefix" << endl;
        return;
    }
    
    tuple<size_t, size_t> tupla_busca = trie.search(word);
    
    if (get<1>(tupla_busca) > 0) {
        cout << word << " is at (" << get<0>(tupla_busca) <<"," << get<1>(tupla_busca) << ")" << endl;
    }
}

// função principal do programa
int main() {

    string input_string, file_name;
    getline(cin, input_string);  // entrada

    // posição 10 deve ser o número do arquivo
    int file_number = int(input_string[10]) - 48;
    file_name = "dictionaries/dicionario" + to_string(file_number) + ".dic";

    ifstream dict(file_name);
    string line;
    if (dict.is_open()) {
        size_t next_position = 0;
        while (getline(dict, line)) {
            string current_word;
            // Caso a linha atual não seja início de palavra
            // if (line[0] != '[') {
            //     next_position += line.length() + 1;
            //     continue;
            // }
            // Caso a linha atual seja início de palavra
            for (int i = 1; i < line.length(); i++) {
                // Caso palavra tenha acabado
                if (line[i] == ']')
                    break;
                current_word += line[i];
            }
            // caso a palavra informada esteja no dicionário
            trie.insert(current_word, line.length(), next_position);

            next_position += line.length() + 1;
        }
        dict.close();
    } else {
        cout << "Não é possível ler o arquivo" << endl;
        return 0;
    }

    input_string.erase(0, 16);
    // input pra teste: dicionario1.dic bear bell bid bu bull buy but sell stock stop 0
    string word = "";
    while (true) { 
        for (auto x: input_string) {
            if (x == ' ') {
                tuple<size_t, size_t> palavra = trie.search(word);
                word_prints(word);
                word = "";
            } else {
                word += x;
            }
        }
        if (word == "0") {
            break;
        }

        word_prints(word);
        break;  
    }

    return 0;
}
