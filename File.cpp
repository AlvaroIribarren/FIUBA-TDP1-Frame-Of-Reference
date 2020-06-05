//
// Created by alvaro on 14/9/19.
//

#include "File.h"
#include "Block.h"
#include<iostream>
#include <netinet/in.h>
#include <bitset>
#include <vector>
#include <string>

#define BYTE_SIZE 8


File::File(const std::string& openingFile, const std::string& outputStream) {
    this->openFile(openingFile);
    this->openOutputStream(outputStream);
}
void File::openFile(const std::string& openingFile){
        std::ifstream binary;
        binary.open(openingFile, std::ios::in | std::ios::binary);
        this->readingFile = dynamic_cast<std::basic_ifstream<char> &&>(binary);
        this->readingFile.seekg(0);

        if (!readingFile) {
            throw std::runtime_error("Error opening file");
        }
}

int File::readNumbersFromFile(std::vector<uint32_t>& vector,
        int N, int seekGParameter) {
    int i= 0;
    if (this->readingFile.is_open()) {
        uint32_t val;
        this->readingFile.seekg(seekGParameter);
        while (!this->readingFile.eof() && i<N){
            this->readingFile.read(reinterpret_cast<char *>(&val), sizeof(val));
            if (!this->readingFile.eof()){
                val = ntohl(val);
                vector.at(i) = val;
                i++;
            }
        }
    }
    int amountOfNumbersRead = i;
    return amountOfNumbersRead;
}

void File::openOutputStream(const std::string& outputStream){
    std::ofstream myFile(outputStream, std::ios::out | std::ios::binary);
    this->outputFile = dynamic_cast<std::basic_ofstream<char> &&>(myFile);
}

static void getActualByte(std::string& sendingBuffer,
                          std::string& actualByte, int& bufferPosition){
    for (int j = 0; j < BYTE_SIZE; j++) {
        actualByte[j] = sendingBuffer[bufferPosition];
        bufferPosition++;
    }
}

void File::writeByte(std::string& byte){
    std::bitset<BYTE_SIZE> b1(byte);
    char byteAsChar = (char) b1.to_ulong();
    this->outputFile.write(&byteAsChar, sizeof(byteAsChar));
}

void File::writeBlockToFile(std::string& finalBuffer) {
    int bufferLength = finalBuffer.size();
    int bufferPosition = 0;

    //Como el tamaño de un byte es constante, reservo las 8 posiciones.
    std::string actualByte(BYTE_SIZE, '0');
    for (int i = 0; i < bufferLength; i += BYTE_SIZE) {
        getActualByte(finalBuffer, actualByte, bufferPosition);
        this->writeByte(actualByte);
    }
}


int File::getReadingFileLength(){
    this->readingFile.seekg(0, std::ios::end);
    int length = readingFile.tellg();
    this->readingFile.seekg(0, this->readingFile.beg);
    return length;
}

bool File::eof() {
    return this->readingFile.eof();
}

File::~File(){
    this->readingFile.close();
    this->outputFile.close();
}



