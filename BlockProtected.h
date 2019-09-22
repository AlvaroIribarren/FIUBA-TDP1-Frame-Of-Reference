//
// Created by alvaro on 21/9/19.
//

#ifndef FRAMEOFREFERENCE_BLOCKPROTECTED_H
#define FRAMEOFREFERENCE_BLOCKPROTECTED_H


#include <mutex>
#include "Block.h"

class BlockProtected {
private:
    std::mutex m;
    Block *block;
public:
    BlockProtected(int N, std::vector<uint32_t> *anotherVector);
    void substractMinimum();
    int returnContentAsBuffer(char* sending);
    void printContent();
    ~BlockProtected();
};


#endif //FRAMEOFREFERENCE_BLOCKPROTECTED_H
