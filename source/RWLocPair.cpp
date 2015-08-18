/* 
 * File:   RWLocationPair.cpp
 * Author: fordem
 * 
 * Created on March 6, 2015, 11:55 PM
 */

#include "RWLocPair.h"

RWLocPair::RWLocPair(uint64_t Pos, uint64_t Len) {
    pos = Pos;
    lenght = Len;
}

RWLocPair::~RWLocPair() {
}

uint64_t & RWLocPair::operator[](RWLocPair::LocP t) {
    switch (t) {
        case POS:
        {
            return pos;
            break;
        }
        case LEN:
        {
            return lenght;
            break;
        }
    }
}

