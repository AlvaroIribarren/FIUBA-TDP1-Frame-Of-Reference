//
// Created by alvaro on 14/9/19.
//

#ifndef FRAMEOFREFERENCE_VECTOR_H
#define FRAMEOFREFERENCE_VECTOR_H

#include <cstdint>
#include <vector>
#include <string>

class Vector {
private:
    std::vector<uint32_t>& numbers;
    int N;
    uint32_t minimum;
    int maxNumbersLengthInBits;

public:
    //Recibe la cantidad de elementos y el vector a asignar.
    //Esta clase es utilizada para manejar los recursos del vector de la
    //standard library de forma orientada al trabajo a realizar.
    Vector(int N, const std::vector<uint32_t> &anotherVector);

    //Constructor por copia.
    Vector(const Vector &other);

    //Agrega el padding al auxiliar buffer en caso de que sea necesario
    void addPaddingIfNecesary(std::vector<char>& auxiliarBuffer);

    //Busca el minimo en el vector.
    uint32_t findMinimum();

    //Busca el maximo en el vector y lo devuelve. En base a esto se sabe
    //que numero tomar como referencia para la longitud maxima.
    uint32_t findMaximum();

    //Resta el minimo a todos los elementos.
    void substractMinimum();

    //Pasa el minimo a string en bits y lo devuelve.
    std::string getMinimumAsString();

    //Pasa la longitud maxima en bits a string y lo devuelve.
    std::string getMaxNumberLengthAsString();

    //Recibe un numero de 4 bytes y devuelve la longitud del mismo en bits.
    uint8_t getBinaryLength(uint32_t number);

    //Pone todos los numeros ya procesados en el auxiliarVector.
    void putNumbersTogetherAsString(std::vector<char>& auxiliarVector);

    //Destructor vacio, todo en el stack.
    virtual ~Vector();
};


#endif //FRAMEOFREFERENCE_VECTOR_H
