#include <iostream>
#include <string>

// Biblioteca para escrita/leitura de arquivos
#include <fstream>

#include "headers/Labeler.h"
#include "headers/XMLFileReader.h"

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
        image_infos images_array[xml_reader.count_images()];
        xml_reader.generate_bin_images(images_array);

        for (int i = 0; i < xml_reader.count_images(); i++) {
            Labeler label_teste = Labeler(images_array[i]);
            int label_img = label_teste.create_label();

            cout << images_array[i].name << " " << label_img << endl;
        }

    } else {
        cout << "error" << endl;
    }

    return 0;
}