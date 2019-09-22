//
// Created by alvaro on 14/9/19.
//

#ifndef FRAMEOFREFERENCE_FILE_H
#define FRAMEOFREFERENCE_FILE_H

#include <fstream>
#include "Block.h"

class File {
private:
    std::ifstream readingFile;
    std::ofstream outputFile;
public:
    File(std::string openingFile, std::string outputStream);

    void openFile(std::string openingFile);

    int readNumbersFromFile(std::vector<uint32_t>* vector , int N);

    void writeToFile(char *byteToBeWritten);

    void writeBlockToFile(Block *block);

    void openOutputStream(std::string outputStream);

    bool eof();

    ~File();
};



#endif //FRAMEOFREFERENCE_FILE_H
