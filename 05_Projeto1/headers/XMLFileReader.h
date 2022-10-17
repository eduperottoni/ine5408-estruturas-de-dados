// @ COPYRIGHT [2022] <Eduardo Perottoni e Caio Prá>

#ifndef XMLFILEREADER_H
#define XMLFILEREADER_H

#include <iostream>
#include <string>

#include <cstdlib>
#include "image_infos.h"
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
    bool validate_xml();
    // Retorna quantas veze uma tag se repete no xml
    int count_tag_occurrance(const string& sub);
    // Retorna quantas matrizes há no dataset
    int count_images();
    // Retorna um ponteiro para array de matrizes
    void generate_bin_images(image_infos* vector);
    // Pega o que está dentro de dada tag que aparece a partir de uma posição
    string catch_inside_tag(const string& start_tag, const string& end_tag, size_t& pos);

 private:
    string xml_;
};

}  // namespace xml

#endif

// IMPLEMENTAÇÃO DOS MÉTODOS
xml::XMLFileReader::XMLFileReader(const string& xml) {
    xml_ = xml;
}

bool xml::XMLFileReader::validate_xml() {
    LinkedStack<string> tags_stack;

    size_t start = 0, end = 0;
    while (end <= xml_.length() - 1) {
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

        if (tag_name[0] != '/') {
            tags_stack.push(tag_name);
            // cout << "empilhei:  " << tag_name << endl;
        } else if (tags_stack.top() == tag_name.substr(1, (tag_name.length() - 1))) {
            // cout << "desempilhei: " << tag_name << endl;
            tags_stack.pop();
        } else {
            return false;
        }
        start = end;
    }

    return tags_stack.empty();
}

void xml::XMLFileReader::generate_bin_images(image_infos* vector) {
    if (validate_xml()) {
        int images_count = count_images();
        cout << images_count << " imagens no arquivo" << endl;
        image_infos images[images_count];
        size_t pos = 0;  //? variavel necessaria? nao tem seu valor atualizado, sempre como 0
        for (int i = 0; i < images_count; i++) {
            image_infos mx_infos;
            mx_infos.name = catch_inside_tag("<name>", "</name>", pos);
            mx_infos.height = (size_t)(stoi(catch_inside_tag("<height>", "</height>", pos)));
            mx_infos.width = (size_t)(stoi(catch_inside_tag("<width>", "</width>", pos)));
            
            // criação da matriz a qual a imagem sera copiada
            mx_infos.matrix = new int*[mx_infos.height];

            mx_infos.matrix[0] = new int[mx_infos.height * mx_infos.width];
            for (int i = 1; i < mx_infos.height; i++) {
                mx_infos.matrix[i] = mx_infos.matrix[0] + i * mx_infos.width;
            } 

            // imagem lida
            string imagem = catch_inside_tag("<data>", "</data>", pos);

            // converte a imagem binaria de string para vetor de inteiro
            int position = 0;
            for (int linha = 0; linha < mx_infos.height; linha++) {
                for (int coluna = 0; coluna < mx_infos.width; coluna++) {
                    mx_infos.matrix[linha][coluna] = int(imagem[position])-'0';
                    position++;
                }
            }

            vector[i] = mx_infos;
        }
    }
    vector = nullptr;
}

string xml::XMLFileReader::catch_inside_tag(const string& start_tag, const string& end_tag, size_t& pos) {
    size_t start = xml_.find(start_tag, pos);
    size_t end = xml_.find(end_tag, start);

    string content = xml_.substr(start + start_tag.length(), (end - (start + start_tag.length())));
    pos = end + end_tag.length();  //? precisa atualizar o valo? nao é retornado e nem usado depois

    return content;
}

int xml::XMLFileReader::count_tag_occurrance(const string& sub) {
    //? verificacao desnecessaria ? (metodo apenas usado dentro de generate_bin_images, que já faz essa verificacação)
    if (validate_xml()) {
        int count = 0;
        for (size_t offset = xml_.find(sub); offset != string::npos;
             offset = xml_.find(sub, offset + sub.length())) {
            ++count;
        }
        return count;
    }
    return -1;
}

int xml::XMLFileReader::count_images() {
    return count_tag_occurrance("<img>");
}