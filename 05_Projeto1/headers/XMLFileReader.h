// @ COPYRIGHT [2022] <Eduardo Perottoni e Caio Prá>

#ifndef XMLFILEREADER_H
#define XMLFILEREADER_H

//Apenas para teste -> Apagar antes de enviar
#include <iostream>

#include <string>
#include "linked_stack.h"



using namespace std;
using namespace structures;

namespace xml {

// Classe que lida com o processamento do XML
class XMLFileReader {
 public:
    // Construtor
    XMLFileReader(const string& xml);
    // Valida o dataset (1º problema)
    bool xml_validation();
    // Retorna um ponteiro para array de matrizes
    char *matrices_vector();

 private:
    string xml_;
};

}  // namespace xml

#endif

// IMPLEMENTAÇÃO DOS MÉTODOS
xml::XMLFileReader::XMLFileReader(const string& xml) {
    xml_ = xml;
}

bool xml::XMLFileReader::xml_validation() {
    LinkedStack<string> tags_stack;

    unsigned int start = 0, end = 0;
    while (end < xml_.length() - 1) {
        start = xml_.find("<", start);
        end = xml_.find(">", start);

        // start e end são achados ?
        if (start == string::npos) {
            break;
        }
        if (end == string::npos) {
            return false;
        }

        string tag_name = xml_.substr(start + 1, (end - (start + 1)));
 
        // cout << tag_name << '\n';

        if (tag_name[0] == '/') {
            try {
                if (tags_stack.top() == tag_name.substr(1, (tag_name.length() - 1)))
                    // cout << "Desempilhei: " << tag_name << endl;
                    tags_stack.pop();
            } catch (const out_of_range e) {
                return false;
            }
        } else {
            // cout << "Empilhei: " << tag_name << endl;
            tags_stack.push(tag_name);
        }

        start = end;
    }

    return tags_stack.empty();
}


