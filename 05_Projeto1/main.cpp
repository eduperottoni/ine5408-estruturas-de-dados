#include <iostream>
#include <string>

// Biblioteca para escrita/leitura de arquivos
#include <fstream>

#include "headers/XMLFileReader.h"
#include "headers/Labeler.h"

using namespace std;
using namespace xml;

int main() {
    string xmlfilename;

    // Leitura do arquivo
    cin >> xmlfilename;
    xmlfilename = "datasets/dataset" + xmlfilename + ".xml";
    ifstream xml_file(xmlfilename);
    string xml_string;
    string line;
    if (xml_file.is_open()) {
        while (getline(xml_file, line)) {
            xml_string += line;
        }
        xml_file.close();
    } else {
        cout << "Arquivo não pode ser lido" << endl;
        return 0;
    }
    XMLFileReader xml_reader = XMLFileReader(xml_string);

    if (xml_reader.validate_xml()) {
        cout << "Arquivo válido" << endl;
        image_infos images_array[xml_reader.count_images()];
        xml_reader.generate_bin_images(images_array);

        for (int i = 0; i < xml_reader.count_images(); i++) {
            cout << images_array[i].name << endl;
            cout << images_array[i].height << endl;
            cout << images_array[i].width << endl;

            // printa todas imagens lidas do arquivo
            // for (int j = 0; j < images_array[i].height; j++) {
            //     for (int k = 0; k < images_array[i].width; k++) {
            //         cout << images_array[i].matrix[j][k] ;
            //     }
            //     cout << endl;
            // }
        }

    for (int i = 0; i < xml_reader.count_images(); i++) {
    Labeler label_teste = Labeler(images_array[i]);
    int label_img1 = label_teste.create_label();

    cout << label_img1 << " regioes" << endl;
    }

    } else {
        cout << "error" << endl;
    }

    return 0;
}