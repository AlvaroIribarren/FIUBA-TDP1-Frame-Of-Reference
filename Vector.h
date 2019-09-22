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
    std::vector<uint32_t> *numbers;
    int N;
    uint32_t minimum;
    int maxNumbersLengthInBits;

public:
    explicit Vector(int N);

    void saveNumbers(std::vector<uint32_t> *anotherVector);

    void printContent();

    int addPaddingIfNecesary(char *auxiliarBuffer);

    uint32_t findMinimum();

    uint32_t findMaximum();

    void substractMinimum();

    std::string getMinimumAsString();

    std::string getMaxNumberLengthAsString();

    uint8_t getBinaryLength(uint32_t number);

    void putNumbersTogetherAsString(char *auxiliarBuffer);

    virtual ~Vector();
};


#endif //FRAMEOFREFERENCE_VECTOR_H
