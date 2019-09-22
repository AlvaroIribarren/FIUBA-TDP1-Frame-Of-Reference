//
// Created by alvaro on 21/9/19.
//

#ifndef FRAMEOFREFERENCE_FILEPROTECTED_H
#define FRAMEOFREFERENCE_FILEPROTECTED_H


#include <mutex>
#include "File.h"

class FileProtected {
private:
    File* file;
    std::mutex m;
public:
    FileProtected(std::string openingFile, std::string outputStream);
    int readNumbers(std::vector<uint32_t>* vector, int N);
    void writeFile(Block *block);
    bool eof();
    ~FileProtected();


};






#endif //FRAMEOFREFERENCE_FILEPROTECTED_H
