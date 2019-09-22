//
// Created by alvaro on 20/9/19.
//

#ifndef FRAMEOFREFERENCE_CONTROLLER_H
#define FRAMEOFREFERENCE_CONTROLLER_H


#include <mutex>
#include "File.h"
#include "Thread.h"
#include "FileProtected.h"
#include "SafeQueue.h"
#include <condition_variable>

class Controller {
private:
    SafeQueue<Block*>* queue;
    FileProtected *file;
    int N;
    std::mutex m;
    std::vector<uint32_t>* numbersFromFile;
public:
    Controller(FileProtected *file, int N);

    Block processBlock();

    int readingProcess();

    void doDrill();

    ~Controller();

    void controlQueue();
};


#endif //FRAMEOFREFERENCE_CONTROLLER_H
