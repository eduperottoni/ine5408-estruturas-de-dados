// @ COPYRIGHT [2022] <Eduardo Perottoni e Caio Prá>

#ifndef XMLFILEREADER_H
#define XMLFILEREADER_H

#include <string>

// Biblioteca para escrita/leitura de arquivos
#include <fstream>

using namespace std;

namespace xml {

// Classe que lida com o processamento do XML
class XMLFileReader {
 public:
    // Construtor
    XMLFileReader(string xml) {
        xml_ = xml;
    }

 private:
    string xml_;
};

}  // namespace xml

#endif
