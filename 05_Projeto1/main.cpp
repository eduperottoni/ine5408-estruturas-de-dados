#include <iostream>
#include <string>

#include "./headers/linked_stack.h"

using namespace std;

// Biblioteca para escrita/leitura de arquivos
#include <fstream>

int main() {

    char xmlfilename[100];

    // Leitura do arquivo
    cin >> xmlfilename;
    ifstream xml_file(xmlfilename);

    string line;
    if (xml_file.is_open()){
        while (getline(xml_file, line)) {
            cout << line << '\n';
        }
        xml_file.close();
    } else {
        cout << "Arquivo não pode ser lido"; 
    }

    return 0;
}