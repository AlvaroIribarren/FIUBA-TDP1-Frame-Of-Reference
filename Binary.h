//
// Created by alvaro on 14/9/19.
//

#ifndef FRAMEOFREFERENCE_BINARY_H
#define FRAMEOFREFERENCE_BINARY_H

#include <cstdint>

int getHexadecimalNumberLength(uint32_t number);

std::string getHexaAsString(uint32_t number);

uint32_t fromDecToHexa(uint32_t number);

std::string getHexaTo8Binary(std::string actualString);

uint8_t getBinaryLength(uint32_t number);

std::string getBinaryString(uint32_t number,  char* finalNumber);

std::string ConvertFrom10(long value, int base);

std::string getHexaTo8Binary(uint32_t number);

int getHexadecimalNumberLengthInBits(uint32_t number);

#endif //FRAMEOFREFERENCE_BINARY_H
