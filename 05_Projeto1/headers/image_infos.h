#ifndef IMAGE_INFOS_H
#define IMAGE_INFOS_H

#include <string>

using namespace std;

typedef struct {
    string name, data;
    size_t height, width;
} image_infos;

#endif
