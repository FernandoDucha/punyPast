/* 
 * File:   RandomNumberGenerator.cpp
 * Author: fernando
 * 
 * Created on June 1, 2013, 4:25 PM
 */

#include <gmp.h>

#include "RandomNumberGenerator.h"
#include "BinaryRandomWalk.h"

RandomNumberGenerator::RandomNumberGenerator() {
    generateLookUpTable();
    BinaryRandomWalk::createMaskTable();
}
RandomNumberGenerator::RandomNumberGenerator(FileRawBuffer* frwb):RandomNumberGenerator(){
    rawbuffer=frwb;
}
RandomNumberGenerator::~RandomNumberGenerator() {
    //delete rawbuffer;
}
mpz_class RandomNumberGenerator::getNumberExactBits(ulong nbits){
    mpz_class ret = getNumberWithMaxBits(nbits);
    mpz_class temp;
    mpz_pow_ui(temp.get_mpz_t(),mpz_class(2).get_mpz_t(),nbits-1);
    if(ret<temp){
        ret+=temp;
    }
    return ret;
}
mpz_class RandomNumberGenerator::getNumberWithMaxBits(ulong nbits){
    ulong bytes=((nbits%8)==0)?(nbits/8):(nbits/8+1);
    uint8_t WalkMask=BinaryRandomWalk::Mask[8-(nbits%8)];
    uint8_t * ret=rawbuffer->getBytesFromFileRandom(bytes);
    ret[bytes-1]&=WalkMask;
    string temp="";
    for(ulong i=0;i<bytes;i++){
        temp=lookUpTable[ret[i]]+temp;
    }
    return mpz_class(temp,16);
}
void RandomNumberGenerator::generateLookUpTable(){
    for(int i=0;i<256;i++){
        char buffer[4];
        sprintf(buffer,"%02X",i);
        memcpy(lookUpTable[i],buffer,3);
    }
}
