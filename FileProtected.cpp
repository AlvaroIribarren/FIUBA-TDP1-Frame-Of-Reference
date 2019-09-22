//
// Created by alvaro on 21/9/19.
//

#include "FileProtected.h"
#include <vector>
#include <string>

FileProtected::FileProtected(std::string openingFile,
        std::string outputStream) {
    this->file = new File(std::move(openingFile)
            , std::move(outputStream));
}

int FileProtected::readNumbers(std::vector<uint32_t> *vector, int N) {
    std::unique_lock<std::mutex> locker(this->m);
    int amountOfNumbersRead = this->file->readNumbersFromFile(vector, N);
    return amountOfNumbersRead;
}

void FileProtected::writeFile(Block *block) {
    std::unique_lock<std::mutex> locker(this->m);
    this->file->writeBlockToFile(block);
}

bool FileProtected::eof() {
    std::unique_lock<std::mutex> locker(this->m);
    bool end = this->file->eof();
    return end;
}

FileProtected::~FileProtected() {
    delete(this->file);
}
