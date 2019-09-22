//
// Created by alvaro on 15/9/19.
//

#ifndef FRAMEOFREFERENCE_BLOCK_H
#define FRAMEOFREFERENCE_BLOCK_H


#include "Vector.h"
#include <vector>
#include <string>

class Block {
private:
    Vector *vector;
    uint8_t totalBlockBytes;

public:
    explicit Block(int N);

    Block(const Block &other);

    Block(Block&& other);

    void saveNumbers(std::vector<uint32_t> *anotherVector);

    void substractMinimum();

    void printContent();

    //En sending buffer devuelve la cadena a
    //enviar y como valor de retorno su largo.
    int getContentInBuffer(char* sendingBuffer);

    //Auxiliar para getContentInBuffer. Este lo arma y lo devuelve.
    int buildBuffer(char *sendingBuffer, char *auxiliarBuffer,
                           std::string min, std::string length);

    virtual ~Block();
};


#endif //FRAMEOFREFERENCE_BLOCK_H
