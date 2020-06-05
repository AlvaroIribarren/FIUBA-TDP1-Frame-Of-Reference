//
// Created by alvaro on 2/10/19.
//

#ifndef UNTITLED_WRITERTHREAD_H
#define UNTITLED_WRITERTHREAD_H


#include "Block.h"
#include "Thread.h"
#include "SafeQueue.h"
#include "FileProtected.h"
#include <string>
#include <vector>

class WriterThread : public Thread{
private:
    std::vector<SafeQueue<std::string>*>& queues;
    FileProtected& file;
    int amountOfBlocks;
public:
    //Crea un hilo escritor, recibe el vector con las colas de los productores,
    //el archivo d
    WriterThread(std::vector<SafeQueue<std::string>*>& queues,
                    FileProtected& file, int amountOfBlocks);

    //Popea los bloques de las colas hasta que los respectivos productores
    //las van cerrando. Finalmente hace una última pasada para chequear si se
    //encuentran todas vacias.
    virtual void run() override;

    //Destructor vacio, el main libera el recurso de las colas.
    ~WriterThread() override;
};


#endif //UNTITLED_WRITERTHREAD_H
