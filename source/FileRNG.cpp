/* 
 * File:   FileRNG.cpp
 * Author: fordem
 * 
 * Created on March 11, 2015, 11:45 AM
 */

#include "FileRNG.h"

FileRNG::FileRNG(FileRawBuffer * frb, uint64_t seed) {
    thisfrb = frb;
    this->actualSeed = this->seed = seed;
    type = FRNG;
    thisfrb->setFilePosition(seed);
}

FileRNG::~FileRNG() {
}



double FileRNG::randd() {
    unsigned char * buff = thisfrb->getBytesFromFile(4);
    uint32_t denominator = numeric_limits<uint32_t>::max();
    uint32_t numerator = 0;
    for (int i = 0; i < 4; i++) {
        reinterpret_cast<char*> (&numerator)[i] = reinterpret_cast<char*> (buff)[i];
    }
    double ret = (double) numerator / denominator;
    return ret;
}

uint64_t FileRNG::randi() {
    unsigned char * buff = thisfrb->getBytesFromFile(4);
    uint32_t ret = 0;
    for (int i = 0; i < 4; i++) {
        reinterpret_cast<char*> (&ret)[i] = reinterpret_cast<char*> (buff)[i];
    }
    return ret;
}

bool FileRNG::operator==(IRNG& rhs) {
    if(getType()==rhs.getType()&&getSeed()==rhs.getSeed()){
        return true;
    }else{
        return false;
    }
}


