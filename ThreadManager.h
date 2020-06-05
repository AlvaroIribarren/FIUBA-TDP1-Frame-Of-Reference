//
// Created by alvaro on 20/9/19.
//

#ifndef FRAMEOFREFERENCE_CONTROLLER_H
#define FRAMEOFREFERENCE_CONTROLLER_H


#include <mutex>
#include <vector>
#include "File.h"
#include "FileProtected.h"
#include "SafeQueue.h"
#include <condition_variable>

class ThreadManager {
public:
    //Realiza el proceso de inicializar las estructuras y crear los threads.
    ThreadManager();

    //Hace el proceso de escritura, donde crea tantos procesadores como
    //amountOfThreads indique y el hilo escritor. Tambien recibe el archivo
    // de donde se realiza la lectura y la cantidad maxima de elementos que
    // poseen las colas.
    void writeBlocksToFile(FileProtected& file, int N,
            int amountOfThreads, int maxQueueElements);

    //Destructor vacio, los recursos solicitados con new en la funcion anterior
    // se liberan en la misma para evitar leaks.
    ~ThreadManager();
};


#endif //FRAMEOFREFERENCE_CONTROLLER_H
