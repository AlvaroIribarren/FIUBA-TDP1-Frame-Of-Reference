//
// Created by alvaro on 15/9/19.
//

#ifndef FRAMEOFREFERENCE_BLOCK_H
#define FRAMEOFREFERENCE_BLOCK_H


#include "Vector.h"
#include <vector>
#include <string>
#include <mutex>

class Block {
private:
    Vector vector;
    uint8_t totalBlockBytes;

public:
    //Crea un bloque con la longitud del mismo y otro vector
    //que ya tiene los numeros del archivo a asignar
    Block(int N, std::vector<uint32_t>& anotherVector);

    //Constructor por copia
    Block(const Block &other);

    //Constructor por movimiento
    Block(Block&& other);

    //Resta el minimo a todos los elementos del bloque
    void substractMinimum();

    //Arma el bloque como string con el minimo, la maxima longitud,
    //y los numeros del bloque restados y lo devuelve.
    std::string getContentInBuffer();

    //Todo en el stack, nada para liberar
    virtual ~Block();
};


#endif //FRAMEOFREFERENCE_BLOCK_H
