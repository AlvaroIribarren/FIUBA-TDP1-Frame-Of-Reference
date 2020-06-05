//
// Created by alvaro on 2/10/19.
//

#ifndef UNTITLED_PROCESSORTHREAD_H
#define UNTITLED_PROCESSORTHREAD_H


#include "Thread.h"
#include "SafeQueue.h"
#include "Block.h"
#include "FileProtected.h"
#include <string>
#include <vector>

class ProcessorThread: public Thread{
private:
    SafeQueue<std::string>* queue;
    FileProtected &file;
    int N;
    int amountOfThreads;
    int initialBlock;
    std::mutex m;

public:
    //Crea un hilo procesador, recibe un puntero a la cola,
    ProcessorThread(SafeQueue<std::string>* otherQueue, FileProtected& file,
                            int N, int amountOfThreads, int initialBlock);

    //Corre el metodo processAndPush.
    virtual void run() override;

    //Proceso de lectura, lee los numeros del archivo y los mete en el vector.
    //Devuelve la cantidad de numeros leidos.
    int readingProcess(std::vector<uint32_t>& numbers, int seekGParameter);

    //Mete el vector en un bloque, lo procesa y lo devuelve como string
    std::string processBlock(std::vector<uint32_t>& numbers);

    //Realiza el proceso del bloque y pushea el string.
    void processAndPush();

    //Destructor vacio.
    ~ProcessorThread() override;
};


#endif //UNTITLED_PROCESSORTHREAD_H
