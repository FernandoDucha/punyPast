/* 
 * File:   IRNG.cpp
 * Author: fordem
 * 
 * Created on February 26, 2015, 8:40 PM
 */

#include <stdint.h>

#include "IRNG.h"

IRNG::IRNG() {
}

IRNG::~IRNG() {
}

uint64_t IRNG::getSeed() {
    return seed;
}
void IRNG::resetSeed(){
    actualSeed = seed;
}
void IRNG::setSeed(uint64_t s) {
    actualSeed = seed = s;
}
IRNG_TYPE IRNG::getType(){
    return type;
}
void IRNG::setType(IRNG_TYPE tp){
    type=tp;
}