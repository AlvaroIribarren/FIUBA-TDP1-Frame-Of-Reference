//
// Created by alvaro on 14/9/19.
//

#include "File.h"
#include "Block.h"
#include "Binary.h"
#include<iostream>
#include <netinet/in.h>
#include <bitset>

#define BYTE_SIZE 8
#define BUFFER_SIZE 200


File::File(std::string openingFile, std::string outputStream) {
    this->openFile(openingFile);
    this->openOutputStream(outputStream);
}
void File::openFile(std::string openingFile){
    std::ifstream binary;
    binary.open (openingFile, std::ios::in | std::ios::binary);
    this->readingFile = dynamic_cast<std::basic_ifstream<char> &&>(binary);
    this->readingFile.seekg(0);

    if(!readingFile) {
        std::cout << "Cannot open readingFile!" << std::endl;
    }
}

int File::readNumbersFromFile(std::vector<uint32_t>* vector, int N) {
    int i= 0;
    if (this->readingFile.is_open()) {
        uint32_t val;

        while (!this->readingFile.eof() && i<N){
            this->readingFile.read(reinterpret_cast<char *>(&val), sizeof(val));
            if(!this->readingFile.eof()){
                val = ntohl(val);
                vector->at(i) = val;
                i++;
            }
        }
    }
    int amountOfNumbersRead = i;
    return amountOfNumbersRead;
}

void File::openOutputStream(std::string outputStream){
    std::ofstream myFile (outputStream, std::ios::out | std::ios::binary);
    this->outputFile = dynamic_cast<std::basic_ofstream<char> &&>(myFile);
}

static void getActualByte(char *sendingBuffer, char *actualByte, int& bufferPosition){
    for (int j = 0; j < BYTE_SIZE; j++) {
        actualByte[j] = sendingBuffer[bufferPosition];
        bufferPosition++;
    }
}

void File::writeBlockToFile(Block *block) {
    char sendingBuffer[100] = "";
    int bufferLength = block->getContentInBuffer(sendingBuffer);

    std::cout << "Buffer: " << sendingBuffer << std::endl;

    int bufferPosition = 0;
    char actualByte[BYTE_SIZE] = "";

    for (int i = 0; i < bufferLength; i += BYTE_SIZE) {
        getActualByte(sendingBuffer, actualByte, bufferPosition);
        std::bitset<8> b1(actualByte);
        char byte = (char) b1.to_ulong();
        this->outputFile.write(&byte, sizeof(byte));
    }
}

void File::writeToFile(char *byteToBeWritten){
    this->outputFile.write(byteToBeWritten, sizeof(byteToBeWritten));
}

//int File::getReadingFileLength(){
//    this->readingFile.seekg (0, readingFile.end);
//    int length = readingFile.tellg();
//    this->readingFile.seekg (0, this->readingFile.beg);
//    return length;
//}

bool File::eof() {
    return this->readingFile.eof();
}

File::~File(){
    this->readingFile.close();
    this->outputFile.close();
}



