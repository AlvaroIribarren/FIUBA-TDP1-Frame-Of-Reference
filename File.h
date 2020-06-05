//
// Created by alvaro on 14/9/19.
//

#ifndef FRAMEOFREFERENCE_FILE_H
#define FRAMEOFREFERENCE_FILE_H

#include <fstream>
#include "Block.h"
#include <string>
#include <vector>

class File {
private:
    std::ifstream readingFile;
    std::ofstream outputFile;

    //Abre el archivo, privado para que solo sea usado por el constructor
    void openFile(const std::string& openingFile);

    //Abre el archivo de salida, privado para que sea usado por el constructor.
    void openOutputStream(const std::string& outputStream);

public:
    //Abre los streams con los nombres recibidos
    File(const std::string& openingFile, const std::string& outputStream);

    //Devuelve en el vector los numeros leidos del archivo, ademas devuelve
    //la cantidad de numeros leidos.
    int readNumbersFromFile(std::vector<uint32_t>& vector,
            int N, int seekGParameter);

    //Escribe el string recibido por parametro en el archivo de salida
    void writeBlockToFile(std::string& finalBuffer);

    //Devuelve la longitud del archivo de entrada.
    int getReadingFileLength();

    //Devuelve true si se llego al end of file del archivo de entrada.
    bool eof();

    //Funcion auxiliar usada por writeBlockToFile para escribir en el archivo.
    void writeByte(std::string &byte);

    //Cierra ambos archivos.
    ~File();
};



#endif //FRAMEOFREFERENCE_FILE_H
