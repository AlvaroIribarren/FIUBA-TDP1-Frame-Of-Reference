#include "Vector.h"
#include "ThreadManager.h"
#include <math.h>
#include "FileProtected.h"
#include <string>

#define BYTES_PER_NUMBER 4

static int turnIntoInt(char* c){
    return atoi(c);
}

int main(int argc, char *argv[]){
    int N = turnIntoInt(argv[1]);
    int amountOfThreads = turnIntoInt(argv[2]);
    int maxQueueElements = turnIntoInt(argv[3]);

    char* inFile = argv[4];
    if (inFile[0] == '-'){
        inFile = (char*) stdin;
    }
    char* outFile = argv[5];
    if (outFile[0] == '-'){
        outFile = (char*) stdout;
    }

    try {
        FileProtected file(inFile, outFile);
        ThreadManager manager;
        manager.writeBlocksToFile(file, N, amountOfThreads,
                maxQueueElements);
    } catch(const std::exception &e) {
        printf("ERROR from main: %s", e.what());
    } catch(...) {
        printf("Unknown error from main");
    }
}



