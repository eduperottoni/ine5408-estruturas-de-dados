#ifndef IMAGE_INFOS_H
#define IMAGE_INFOS_H

#include <string>

using namespace std;

typedef struct {
    string name;
    int** matrix;
    size_t height, width;
} image_infos;

#endif
