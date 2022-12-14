// Copyright [2022] 
// <Caio Prá e Eduardo Perottoni>

#ifndef XMLFILEREADER_H
#define XMLFILEREADER_H

#include <cstdlib>
#include <iostream>
#include <string>

#include "image_infos.h"
#include "linked_stack.h"

using namespace std;
using namespace structures;

namespace xml {


class XMLFileReader {
 public:
    /*
        Construtor da classe
        @param xml: xml em formato string
    */
    XMLFileReader(const string& xml);

    /*
        Valida o dataset (1º problema)
        @return bool: se o xml é válido ou não
    */
    bool validate_xml();

    /* 
        Conta tags no arquivo
        @param sub: tag a ser pesquisada no xml
        @return int: quantas vezez a tag se repete no xml
    */
    int count_tag_occurrance(const string& sub);

    /*
        Conta imagens binárias
        @return int: quantas matrizes há no dataset
    */
    int count_images();

    /*
        Gera as imagens binárias
        @param vector: vetor a ser preenchido com structs do tipo image_infos geradoss 
    */
    void generate_bin_images(image_infos* vector);

    /*
        Lê o conteúdo dentro de uma tag, lida a partir de dada posição
        @param start_tag: tag de abertura
        @param end_tag: tag de fechamento
        @param pos: posição do xml a iniciar a busca (é atualizada após busca)
        @return string: o que está escrito entre start_tag e end_tag
    */
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

        if (tag_name[0] != '/') {
            tags_stack.push(tag_name);
        } else if (tags_stack.top() == tag_name.substr(1, (tag_name.length() - 1))) {
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

        size_t pos = 0;
        for (int i = 0; i < images_count; i++) {
            image_infos mx_infos;
            mx_infos.name = catch_inside_tag("<name>", "</name>", pos);
            mx_infos.height = (size_t)(stoi(catch_inside_tag("<height>", "</height>", pos)));
            mx_infos.width = (size_t)(stoi(catch_inside_tag("<width>", "</width>", pos)));

            // criação da matriz a qual a imagem sera copiada
            mx_infos.matrix = new int*[mx_infos.height];
            for (int i = 0; i < mx_infos.height; i++) {
                mx_infos.matrix[i] = new int[mx_infos.width];
                for (int j = 0; j < mx_infos.width; j++) {
                    mx_infos.matrix[i][j] = 0;
                }
            }

            // imagem lida
            string imagem = catch_inside_tag("<data>", "</data>", pos);

            // converte a imagem binaria de string para vetor de inteiro
            int position = 0;
            for (int linha = 0; linha < mx_infos.height; linha++) {
                for (int coluna = 0; coluna < mx_infos.width; coluna++) {
                    mx_infos.matrix[linha][coluna] = int(imagem[position]) - '0';
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
    pos = end + end_tag.length();

    return content;
}

int xml::XMLFileReader::count_tag_occurrance(const string& sub) {
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