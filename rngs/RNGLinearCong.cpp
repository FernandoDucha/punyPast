/* 
 * File:   RNGLinearCong.cpp
 * Author: fordem
 * 
 * Created on February 26, 2015, 9:00 PM
 */

#include "RNGLinearCong.h"

RNGLinearCong::RNGLinearCong() {
    actualSeed = seed = 123;
    setType(LCG);
}

RNGLinearCong::RNGLinearCong(uint64_t s) {
    actualSeed = seed = s;
    setType(LCG);
}
bool RNGLinearCong::operator==(IRNG& rhs){
    if(getType()==rhs.getType()&&getSeed()==rhs.getSeed()){
        return true;
    }else{
        return false;
    }
}

RNGLinearCong::~RNGLinearCong() {
}

double RNGLinearCong::randd() {
    double aux, x;
    aux = 0.5 / iM;
    actualSeed = actualSeed * iA + iB;
    actualSeed%=(2*iM);
    x = actualSeed*aux;
    return x;
}

uint64_t RNGLinearCong::randi() {
    actualSeed = actualSeed * iA + iB;
    actualSeed%=(2*iM);
    return actualSeed;
}