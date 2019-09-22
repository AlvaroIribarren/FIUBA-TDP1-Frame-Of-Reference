//
// Created by alvaro on 14/9/19.
//

#include <iostream>
#include <sstream>
#include <cstring>
#include "Vector.h"
#include "Binary.h"
#include <bits/stdc++.h>

#define BYTE_SIZE 8
#define FOUR_BYTES_SIZE BYTE_SIZE*4


Vector::Vector(int N) {
    this->numbers = new std::vector<uint32_t> (N);
    this->N = N;
    this->minimum = 0;
    this->maxNumbersLengthInBits = 0;
}

void Vector::saveNumbers(std::vector<uint32_t> *anotherVector) {
    *numbers = *anotherVector;
}

void Vector::printContent() {
    for (auto i : *numbers) {
        std::cout << "Printing value: " << i  << std::endl;
    }
}

uint32_t Vector::findMaximum() {
    uint32_t max = 0;
    for (auto i: *numbers) {
        if (i > max ) {
            max = i;
        }
    }
    return max;
}

uint32_t Vector::findMinimum() {
    uint32_t min = numbers->front();
    for (auto i: *numbers) {
        if (i!=0 && min > i) {
            min = i;
        }
    }

    this->minimum = min;
    std::cout << "Min: " << min << std::endl;
    return min;
}



void Vector::substractMinimum() {
    this->minimum = this->findMinimum();
    for(int i=0; i < N; i++){
        if (this->numbers->at(i))
            this->numbers->at(i) -= this->minimum;
    }
    this->maxNumbersLengthInBits = getBinaryLength(this->findMaximum());
}

int Vector::addPaddingIfNecesary(char* auxiliarBuffer) {
    int totalBits = N * maxNumbersLengthInBits;
    bool aligned = (totalBits % BYTE_SIZE == 0);

    while(!aligned){
        auxiliarBuffer[totalBits] = '0';
        totalBits++;
        std::cout << "Trying to align, actual value: " << totalBits << std::endl;
        aligned = (totalBits % BYTE_SIZE == 0);
    }

    return totalBits;
}


void Vector::putNumbersTogetherAsString(char *auxiliarBuffer) {
    int actualPosition = 0;
    std::string actualString = "";

    char actualStringChar[N * maxNumbersLengthInBits];
    for (int i = 0; i < this->N; i++) {
        memset(actualStringChar, '\0', sizeof(actualStringChar));
        uint32_t num = this->numbers->at(i);

        std::bitset<FOUR_BYTES_SIZE> b1(num);
        actualString = b1.to_string();
        int zeros = FOUR_BYTES_SIZE - this->maxNumbersLengthInBits;

        for (int i = 0; i < this->maxNumbersLengthInBits; i++) {
            actualStringChar[i] = actualString[i + zeros];
        }

        std::cout << "Value in binarie: " << actualStringChar << std::endl;
        for (int i = 0; i < this->maxNumbersLengthInBits; i++) {
            auxiliarBuffer[actualPosition] = actualStringChar[i];
            actualPosition++;
        }
    }
}

std::string Vector::getMinimumAsString() {
    std::bitset<32> b1(this->minimum);
    std::string min = b1.to_string();
    return min;
}

std::string Vector::getMaxNumberLengthAsString() {
    std::string length = std::bitset<BYTE_SIZE>(this->maxNumbersLengthInBits).to_string();
    return length;
}


Vector::~Vector() {
    numbers->clear();
    std::vector<uint32_t>().swap(*numbers);
    delete(this->numbers);
}




