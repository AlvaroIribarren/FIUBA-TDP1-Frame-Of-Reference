//
// Created by alvaro on 20/9/19.
//

#include <iostream>
#include "Controller.h"
#include "SafeQueue.h"


Controller::Controller(FileProtected *file, int N) {
    this->queue = new SafeQueue<Block*>;
    this->file = file;
    this->N = N;
    this->numbersFromFile = new std::vector<uint32_t>(N);
}

int Controller::readingProcess(){
    std::unique_lock<std::mutex> locker(this->m);
    for(int i=0; i < N; i++) {
        this->numbersFromFile->at(i) = 0;
    }

    int amountOfNumbersRead = this->file->readNumbers(this->numbersFromFile, N);
    return amountOfNumbersRead;
}

Block Controller::processBlock(){
    std::unique_lock<std::mutex> locker(this->m);
    Block block(N);
    block.saveNumbers(numbersFromFile);

    block.printContent();
    block.substractMinimum();
    block.printContent();

    //Block* processedBlock = new Block(std::move(block));
   return std::move(block);
}

void Controller::doDrill() {
    int amountOfNumbersRead = readingProcess();

    Block processedBlock = processBlock();
    this->queue->push(&processedBlock);

    if (amountOfNumbersRead != 0) {
       controlQueue();
    }
}

void Controller::controlQueue(){
    std::unique_lock<std::mutex> locker(this->m);

    //El wait es interno a la cola
    Block* processedBlock = this->queue->pop();
    file->writeFile(processedBlock);
    //this->queue->popFrontAndDelete();
}


Controller::~Controller() {
    delete(this->numbersFromFile);
    delete(this->queue);
}