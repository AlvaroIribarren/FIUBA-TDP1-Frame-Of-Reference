//
// Created by alvaro on 21/9/19.
//

#include "FileProtected.h"
#include <vector>
#include <string>

FileProtected::FileProtected(const std::string& openingFile,
        const std::string& outputStream):
        file(openingFile, outputStream){
}

int FileProtected::readNumbers(std::vector<uint32_t>& vector,
        int N, int seekGParameter) {
    std::unique_lock<std::mutex> locker(this->m);
    int amountOfNumbersRead =
            this->file.readNumbersFromFile(vector, N, seekGParameter);
    return amountOfNumbersRead;
}

void FileProtected::writeFile(std::string& bufferToWrite) {
    std::unique_lock<std::mutex> locker(this->m);
    this->file.writeBlockToFile(bufferToWrite);
}

int FileProtected::getReadingFileLength() {
    std::unique_lock<std::mutex> locker(this->m);
    return this->file.getReadingFileLength();
}

bool FileProtected::eof() {
    std::unique_lock<std::mutex> locker(this->m);
    bool end = this->file.eof();
    return end;
}

FileProtected::~FileProtected() {
}

