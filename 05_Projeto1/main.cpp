#include <iostream>
#include <string>

// Biblioteca para escrita/leitura de arquivos
#include <fstream>
#include "headers/XMLFileReader.h"


using namespace std;
using namespace xml;

int main() {

    char xmlfilename[100];

    // Leitura do arquivo
    cin >> xmlfilename;
    ifstream xml_file(xmlfilename);
    string xml_string;
    string line;
    if (xml_file.is_open()){
        while (getline(xml_file, line)) {
            xml_string += line;
        }
        xml_file.close();
    } else {
        cout << "Arquivo não pode ser lido"; 
    }

    XMLFileReader xml_reader = XMLFileReader(xml_string);

    if (xml_reader.xml_validation()) {
        cout << "Arquivo válido" << endl;
    } else {
        cout << "Arquivo inválido" << endl;
    }

    return 0;
}