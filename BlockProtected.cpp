//
// Created by alvaro on 21/9/19.
//

#include "BlockProtected.h"


BlockProtected::BlockProtected(int N, std::vector<uint32_t> *anotherVector) {
    std::unique_lock<std::mutex> locker(this->m);
    this->block = new Block(N);
    this->block->saveNumbers(anotherVector);
}


void BlockProtected::substractMinimum() {
    std::unique_lock<std::mutex> locker(this->m);
    this->block->substractMinimum();
}

int BlockProtected::returnContentAsBuffer(char *sending) {
    std::unique_lock<std::mutex> locker(this->m);
    this->block->getContentInBuffer(sending);
}

void BlockProtected::printContent() {
    std::unique_lock<std::mutex> locker(this->m);
    this->block->printContent();
}

BlockProtected::~BlockProtected() {
    delete(this->block);
}