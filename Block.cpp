//
// Created by alvaro on 15/9/19.
//

#include <string>
#include "Block.h"
#include <vector>

#define BYTE_SIZE 8

Block::Block(int N, std::vector<uint32_t>& anotherVector):
     vector(N, anotherVector), totalBlockBytes(0) {}

Block::Block(const Block &other): vector(other.vector),
                totalBlockBytes(other.totalBlockBytes) {}

Block::Block(Block&& other): vector(std::move(other.vector)){
    this->totalBlockBytes = other.totalBlockBytes;
    other.totalBlockBytes = 0;
}

void Block::substractMinimum() {
    this->vector.substractMinimum();
}

std::string Block::getContentInBuffer() {
    std::string min = this->vector.getMinimumAsString();
    std::string length = this->vector.getMaxNumberLengthAsString();

    std::vector<char> auxiliarVector;

    this->vector.putNumbersTogetherAsString(auxiliarVector);
    //Agrega el padding de ser necesario
    this->vector.addPaddingIfNecesary(auxiliarVector);
    //Pasa el vector a string
    std::string aux(auxiliarVector.begin(), auxiliarVector.end());

    //Concatena todos los strings
    std::string finalSending = min + length + aux;
    return finalSending;
}


Block::~Block() {}
