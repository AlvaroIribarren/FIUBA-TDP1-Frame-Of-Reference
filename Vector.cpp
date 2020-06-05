//
// Created by alvaro on 14/9/19.
//

#include <iostream>
#include <string>
#include "Vector.h"
#include <bits/stdc++.h>
#include <vector>

#define BYTE_SIZE 8
#define FOUR_BYTES_SIZE (4*BYTE_SIZE)


Vector::Vector(int N, const std::vector<uint32_t>& anotherVector):
        numbers(const_cast<std::vector<uint32_t> &>(anotherVector)),
        N(N), minimum(0), maxNumbersLengthInBits(0) {}

Vector::Vector(const Vector &other): numbers(other.numbers){
    this->minimum = other.minimum;
    this->N = other.N;
    this->maxNumbersLengthInBits = other.maxNumbersLengthInBits;
}


uint32_t Vector::findMaximum() {
    uint32_t max = 0;
    for (auto i: numbers) {
        if (i > max) {
            max = i;
        }
    }
    return max;
}

uint32_t Vector::findMinimum() {
    uint32_t min = numbers.front();
    for (auto i: numbers) {
        if (i!=0 && min > i) {
            min = i;
        }
    }

    this->minimum = min;
    return min;
}

uint8_t Vector::getBinaryLength(uint32_t number){
    int i=0;
    for (i=0; number>0; i++){
        number= number/2;
    }
    uint8_t binaryLength = i;
    return binaryLength;
}



void Vector::substractMinimum() {
    this->minimum = this->findMinimum();
    for (int i=0; i < N; i++){
        if (this->numbers.at(i))
            this->numbers.at(i) -= this->minimum;
    }
    this->maxNumbersLengthInBits = this->getBinaryLength(this->findMaximum());
}

void Vector::addPaddingIfNecesary(std::vector<char>& auxiliarBuffer) {
    int totalBits = N * maxNumbersLengthInBits;
    bool aligned = (totalBits % BYTE_SIZE == 0);

    while (!aligned){
        auxiliarBuffer.push_back('0');
        totalBits++;
        aligned = (totalBits % BYTE_SIZE == 0);
    }
}



void Vector::putNumbersTogetherAsString(std::vector<char>& auxiliarVector) {
    std::string actualString = "";

    for (int i = 0; i < this->N; i++) {
        uint32_t num = (uint32_t) this->numbers.at(i);

        std::bitset<FOUR_BYTES_SIZE> b1(num);
        actualString = b1.to_string();
        int zeros = FOUR_BYTES_SIZE - this->maxNumbersLengthInBits;

        for (int i = 0; i < this->maxNumbersLengthInBits; i++) {
            auxiliarVector.push_back(actualString[i + zeros]);
        }
    }
}

std::string Vector::getMinimumAsString() {
    std::bitset<FOUR_BYTES_SIZE> b1(this->minimum);
    std::string min = b1.to_string();
    return min;
}

std::string Vector::getMaxNumberLengthAsString() {
    std::string length = std::bitset<BYTE_SIZE>
            (this->maxNumbersLengthInBits).to_string();
    return length;
}


Vector::~Vector() {}




