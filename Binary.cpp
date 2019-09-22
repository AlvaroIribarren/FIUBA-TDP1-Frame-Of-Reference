//
// Created by alvaro on 14/9/19.
//

#include <sstream>
#include <iostream>
#include <bitset>
#include <cstring>
#include "Binary.h"
using namespace std;

string getHexaAsString(uint32_t number){
    std::stringstream ss;
    ss<< std::hex << number;
    std::string res (ss.str());
    return res;
}


uint8_t getBinaryLength(uint32_t number){
    int n1[32];
    int i=0;
    for(i=0; number>0; i++){
        n1[i]=number%2;
        number= number/2;
    }
    uint8_t binaryLength = i;
    return binaryLength;
}




