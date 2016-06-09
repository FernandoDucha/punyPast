/* 
 * File:   IPolynom.cpp
 * Author: fordem
 * 
 * Created on June 3, 2015, 11:22 PM
 */

#include "IPolynom.h"

IPolynom::IPolynom() {
}
IPolynom::IPolynom(IPolynom & clone) {
    *this=clone;
}
IPolynom::~IPolynom() {
}

