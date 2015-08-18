/* 
 * File:   RWBufferedBase.h
 * Author: fordem
 *
 * Created on March 3, 2015, 10:19 PM
 */

#ifndef RWBUFFEREDDPBASE_H
#define	RWBUFFEREDDPBASE_H
#include "RWBufferedDp.h"
#include "RWBufferedDpSet.h"
typedef RWBufferedDpSet<long double> BufferedDpSetLD;
typedef RWBufferedDpSet<double> BufferedDpSetDouble;
typedef RWBufferedDpSet<long int> BufferedDpSetLI;
typedef RWBufferedDpSet<int> BufferedDpSetInt;
typedef RWBufferedDpSet<unsigned long int> BufferedDpSetULI;
typedef RWBufferedDpSet<unsigned int> BufferedDpSetUInt;
typedef RWBufferedDpSet<float> BufferedDpSetFloat;
typedef RWBufferedDpSet<short> BufferedDpSetShort;
typedef RWBufferedDpSet<unsigned short> BufferedDpSetUShort;
typedef RWBufferedDpSet<unsigned char> BufferedDpSetsUC;
//DataPoints Pre-Def Types
typedef RWBufferedDp<long double> BufferedDpLD;
typedef RWBufferedDp<double> BufferedDpDouble;
typedef RWBufferedDp<long int> BufferedDpLI;
typedef RWBufferedDp<int> BufferedDPInt;
typedef RWBufferedDp<unsigned long int> BufferedDpULI;
typedef RWBufferedDp<unsigned int> BufferedDpUInt;
typedef RWBufferedDp<float> BufferedDpFloat;
typedef RWBufferedDp<short> BufferedDpShort;
typedef RWBufferedDp<unsigned short> BufferedDpUShort;
typedef RWBufferedDp<unsigned char> BufferedDpUC;


#endif	/* RWBUFFEREDBASE_H */

