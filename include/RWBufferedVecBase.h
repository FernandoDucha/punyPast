/* 
 * File:   RWBufferedVecBase.h
 * Author: fordem
 *
 * Created on March 6, 2015, 10:32 AM
 */

#ifndef RWBUFFEREDVECBASE_H
#define	RWBUFFEREDVECBASE_H
#include "RWBufferedVec.h"
#include "RWBufferedVecSet.h"
typedef RWBufferedVecSet<long double> BufferedVecSetLD;
typedef RWBufferedVecSet<double> BufferedVecSetDouble;
typedef RWBufferedVecSet<long int> BufferedVecSetLI;
typedef RWBufferedVecSet<int> BufferedVecSetInt;
typedef RWBufferedVecSet<unsigned long int> BufferedVecSetULI;
typedef RWBufferedVecSet<unsigned int> BufferedVecSetUInt;
typedef RWBufferedVecSet<float> BufferedVecSetFloat;
typedef RWBufferedVecSet<short> BufferedVecSetShort;
typedef RWBufferedVecSet<unsigned short> BufferedVecSetUShort;
typedef RWBufferedVecSet<unsigned char> BufferedVecSetsUC;
//DataPoints Pre-Def Types
typedef RWBufferedVec<long double> BufferedVecLD;
typedef RWBufferedVec<double> BufferedVecDouble;
typedef RWBufferedVec<long int> BufferedVecLI;
typedef RWBufferedVec<int> BufferedVecInt;
typedef RWBufferedVec<unsigned long int> BufferedVecULI;
typedef RWBufferedVec<unsigned int> BufferedVecUInt;
typedef RWBufferedVec<float> BufferedVecFloat;
typedef RWBufferedVec<short> BufferedVecShort;
typedef RWBufferedVec<unsigned short> BufferedVecUShort;
typedef RWBufferedVec<unsigned char> BufferedVecUC;


#endif	/* RWBUFFEREDVECBASE_H */

