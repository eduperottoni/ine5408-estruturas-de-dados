// @ COPYRIGHT [2022] <Eduardo Perottoni, Caio Prá>

#ifndef LABELER_H
#define LABELER_H

#include <string>

#include "image_infos.h"
#include "linked_queue.h"

using namespace std;
using namespace structures;

class Labeler {
 public:
    /*
        Construtor da classe que faz rotulação de imagem
        @param image_info: struct contendo imagem e suas informações
    */
    Labeler(const image_infos& image_info_);

    /*
        Cria a rotulação
        @return rotulo: quantidade de imagens encontradas
    */
    int create_label();

 private:
    // informações da imagem sendo processada
    image_infos image_info;
    // quantidade de componentes conexos da imagem
    size_t components;
};
#endif

Labeler::Labeler(const image_infos& image_info_) {
    image_info = image_info_;
    components = 0;
}

int Labeler::create_label() {
    int rotulo = 1;

    // matriz inicialmente com valor 0 em todas posições
    int** labeled_matrix = new int*[image_info.height];
    for (int i = 0; i < image_info.height; i++) {
        labeled_matrix[i] = new int[image_info.width];
        for (int j = 0; j < image_info.width; j++) {
            labeled_matrix[i][j] = 0;
        }
    }
    // fila com tipo tupla, contendo dois ints cada
    using tupla = pair<int, int>;
    LinkedQueue<tupla> queue_tupla;

    // image_info.matrix é matriz contendo a imagem
    for (int i = 0; i < image_info.height; i++) {
        for (int j = 0; j < image_info.width; j++) {
            if (
                labeled_matrix[i][j] == 0 && image_info.matrix[i][j] == 1) {
                queue_tupla.enqueue({i, j});
                labeled_matrix[i][j] = rotulo;

                while (!queue_tupla.empty()) {
                    // estrutura pair contem dois inteiros, first e second
                    tupla tupla_atual = queue_tupla.dequeue();

                    int x = tupla_atual.first;
                    int y = tupla_atual.second;

                    // [x-1][y]
                    if (
                        x - 1 >= 0 && labeled_matrix[x - 1][y] == 0 && image_info.matrix[x - 1][y] == 1) {
                        labeled_matrix[x - 1][y] = rotulo;
                        queue_tupla.enqueue({x - 1, y});
                    }

                    // [x+1][y]
                    if (
                        x + 1 < image_info.height && labeled_matrix[x + 1][y] == 0 && image_info.matrix[x + 1][y] == 1) {
                        labeled_matrix[x + 1][y] = rotulo;
                        queue_tupla.enqueue({x + 1, y});
                    }

                    // [x][y-1]
                    if (
                        y - 1 >= 0 && labeled_matrix[x][y - 1] == 0 && image_info.matrix[x][y - 1] == 1) {
                        labeled_matrix[x][y - 1] = rotulo;
                        queue_tupla.enqueue({x, y - 1});
                    }

                    // [x][y+1]
                    if (
                        y + 1 < image_info.width && labeled_matrix[x][y + 1] == 0 && image_info.matrix[x][y + 1] == 1) {
                        labeled_matrix[x][y + 1] = rotulo;
                        queue_tupla.enqueue({x, y + 1});
                    }
                }
                // fila esvaziou
                rotulo++;
            }
        }
    }
    // for (int i = 0; i < image_info.height; i++) {
    //     for (int j = 0; j < image_info.width; j++) {
    //         cout << labeled_matrix[i][j];
    //     }
    //     cout << endl;
    // }

    return rotulo - 1;
}