//
// Created by alvaro on 21/9/19.
//

#ifndef FRAMEOFREFERENCE_FILEPROTECTED_H
#define FRAMEOFREFERENCE_FILEPROTECTED_H


#include <mutex>
#include "File.h"
#include <string>
#include <vector>

class FileProtected {
private:
    File file;
    std::mutex m;

public:
    //Inicializa el atributo file con los strings correspondientes.
    FileProtected(const std::string &openingFile,
                  const std::string &outputStream);

    //Devuelve en el vector los numeros leidos. Usa el parametro seekGParameter
    //para determinar de qué linea empezar a leer y el N para saber cuantos
    //debe leer.
    int readNumbers(std::vector<uint32_t> &vector,
                    int N, int seekGParameter);

    //Escribe el string en el file.
    void writeFile(std::string &bufferToWrite);

    //Obtiene la longitud del archivo.
    int getReadingFileLength();

    //True si el file llego al final.
    bool eof();

    //Destructor vacio, atributos en el stack.
    ~FileProtected();
};






#endif //FRAMEOFREFERENCE_FILEPROTECTED_H
