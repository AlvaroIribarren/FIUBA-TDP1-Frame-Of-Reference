//
// Created by alvaro on 2/10/19.
//

#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "ProcessorThread.h"

#define BYTES_PER_NUMBER 4


ProcessorThread::ProcessorThread(SafeQueue<std::string>* otherQueue,
        FileProtected& file, int N, int amountOfThreads, int initialBlock):
        queue(otherQueue), file(file), N(N), amountOfThreads(amountOfThreads),
                                initialBlock(initialBlock){}

void ProcessorThread::run() {
    try {
        this->processAndPush();
    } catch(const std::exception &e) {
        printf("ERROR from processor %d: %s", initialBlock, e.what());
    } catch(...) {
        printf("Unknown error from processor %d", initialBlock);
    }
}

int ProcessorThread::readingProcess(std::vector<uint32_t>& numbers,
        int seekGParameter){
    int amountOfNumbersRead =this->file.readNumbers(numbers,
            N, seekGParameter);
    return amountOfNumbersRead;
}

std::string ProcessorThread::processBlock(std::vector<uint32_t>& numbers){
    Block block(N, numbers);
    block.substractMinimum();
    return block.getContentInBuffer();
}

void ProcessorThread::processAndPush(){
    std::unique_lock<std::mutex> locker(this->m);
    int amountOfBytesPerBlock = BYTES_PER_NUMBER * N;
    int fileLength = file.getReadingFileLength();
    int amountOfBlocks = ceil(float(fileLength)
                              /float(amountOfBytesPerBlock));

    for (int i = initialBlock; i < amountOfBlocks; i += amountOfThreads) {
        std::vector<uint32_t> numbers(N);
        int seekGParameter = i * amountOfBytesPerBlock;
        int amountRead = readingProcess(numbers, seekGParameter);

        if (amountRead != 0){
            std::string processedBlock = processBlock(numbers);
            queue->push(processedBlock);
        }
    }
}

ProcessorThread::~ProcessorThread() {}
