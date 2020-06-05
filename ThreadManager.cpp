//
// Created by alvaro on 20/9/19.
//

#include "ThreadManager.h"
#include "SafeQueue.h"
#include "ProcessorThread.h"
#include "WriterThread.h"
#include <vector>
#include <cmath>
#include <string>

#define BYTES_PER_NUMBER 4

ThreadManager::ThreadManager(){}

void ThreadManager::writeBlocksToFile(FileProtected& file, int N,
        int amountOfThreads, int maxQueueElements){
    std::vector<SafeQueue<std::string>*> queues;
    std::vector<ProcessorThread*> processors;

    int amountOfBytesPerBlock = BYTES_PER_NUMBER*N;
    //division de los flotantes y redondeo para arriba
    int amountOfBlocks = ceil(float(file.getReadingFileLength())
            /float(amountOfBytesPerBlock));


    for (int i=0; i<amountOfThreads; i++){
        auto* newQueue = new SafeQueue<std::string>(maxQueueElements);
        queues.push_back(newQueue);
        auto* newProcessor = new ProcessorThread(newQueue, file, N,
                                                 amountOfThreads, i);
        processors.push_back(newProcessor);
    }

    for (ProcessorThread*& actualProcessor: processors){
        actualProcessor->start();
    }

    WriterThread writer(queues, file, amountOfBlocks);
    writer.start();

    for (ProcessorThread*& actualProcessor: processors){
        actualProcessor->join();
    }

    writer.join();

    for (int i=0; i<amountOfThreads; i++){
        delete(queues.at(i));
        delete(processors.at(i));
    }
}

ThreadManager::~ThreadManager() {}

