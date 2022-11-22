#include <fstream>
#include <iostream>

#include "headers/Trie.h"

int main() {
    using namespace structures;
    using namespace std;

    string dict_filename;

    cin >> dict_filename;  // entrada

    dict_filename = "dictionaries/dicionario" + dict_filename + ".dic";
    ifstream dict(dict_filename);
    Trie trie = Trie();
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
            trie.insert(current_word, line.length(), next_position);
            next_position += line.length() + 1;
        }
        dict.close();
    } else {
        cout << "Não é possível ler o arquivo";
        return 0;
    }

    // Teste do método search
    string word = "bear";
    cout << "Buscando palavra\n";
    cout << "Índice da palavra: " << get<0>(trie.search(word)) << "\n";
    word = "derrocaram";
    cout << "Comprimento da linha da palavra: " << get<1>(trie.search(word)) << "\n";
    cout << word << " é prefixo de " << trie.count_prefixed_words(word) << endl;

    return 0;
}
