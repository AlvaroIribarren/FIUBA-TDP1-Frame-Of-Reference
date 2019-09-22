//
// Created by alvaro on 15/9/19.
//

#include <iostream>
#include <vector>
#include <bitset>
#include <cstring>
#include "Block.h"

#define BYTE_SIZE 8

using namespace std;

Block::Block(int N) {
    this->vector = new Vector(N);
    this->totalBlockBytes = 0;
}

Block::Block(const Block &other) {
    this->vector = other.vector;
    this->totalBlockBytes = other.totalBlockBytes;
}

Block::Block(Block&& other) {
    this->vector = other.vector;
    this->totalBlockBytes = other.totalBlockBytes;
    other.vector = nullptr;
    other.totalBlockBytes = 0;
}

void Block::saveNumbers(std::vector<uint32_t> *anotherVector) {
    this->vector->saveNumbers(anotherVector);
}

void Block::substractMinimum() {
    this->vector->substractMinimum();
}


int Block::getContentInBuffer(char* sendingBuffer) {
    std::string min = this->vector->getMinimumAsString();
    std::string length = this->vector->getMaxNumberLengthAsString();

    char auxiliarBuffer[300];
    memset(auxiliarBuffer, '\0', sizeof(auxiliarBuffer));

    this->vector->putNumbersTogetherAsString(auxiliarBuffer);
    int lengthCounter = this->buildBuffer(sendingBuffer, auxiliarBuffer, min, length);

    return lengthCounter;
}



int Block::buildBuffer(char *sendingBuffer, char *auxiliarBuffer,
                        std::string min, std::string length){
    int lengthCounter = 0;
    int minSize = min.size();
    int amountOfZeros = 32 - minSize;

    for (int i=0; i< amountOfZeros; i++){
        sendingBuffer[i] = '0';
        lengthCounter++;
    }

    for (int i= amountOfZeros; i<32; i++){
        sendingBuffer[i] = min[i - amountOfZeros];
        lengthCounter++;
    }

    for (int i= 0; i< 8 ; i++){
        sendingBuffer[i +32] = length[i];
        lengthCounter++;
    }

    int totalAuxiliarBufferBits = this->vector->addPaddingIfNecesary(auxiliarBuffer);
    std::cout << "AuxiliarBuffer : "<< auxiliarBuffer << std::endl;

    for (int i=0; i< totalAuxiliarBufferBits; i++){
        sendingBuffer[i+40] = auxiliarBuffer[i];
        lengthCounter++;
    }

    return lengthCounter;
}

void Block::printContent(){
    this->vector->printContent();
}



Block::~Block() {
    delete(this->vector);
}