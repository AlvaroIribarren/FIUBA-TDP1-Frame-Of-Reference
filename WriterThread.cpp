//
// Created by alvaro on 2/10/19.
//

#include "WriterThread.h"
#include "FileProtected.h"
#include <string>
#include <vector>


WriterThread::WriterThread(std::vector<SafeQueue<std::string>*>& queues,
                            FileProtected& file, int amountOfBlocks):
                            queues(queues), file(file),
                            amountOfBlocks(amountOfBlocks){}


void WriterThread::run() {
    int blocksWritten = 0;
    while (blocksWritten < amountOfBlocks){
        for (SafeQueue<std::string>*& actualQueue: queues){
            std::string message = actualQueue->pop();
            file.writeFile(message);
            blocksWritten++;
        }
    }
}


WriterThread::~WriterThread() {}
