/* 
 * File:   RWPset.h
 * Author: fernando
 *
 * Created on 30 de Abril de 2013, 18:46
 */

#ifndef RWDPBASE_H
#define	RWDPBASE_H
#include "RWDp.h"
#include "RWDpSet.h"
//DataPointsSet Pre-Def Types
typedef RWDpSet<long double> DataSetLD;
typedef RWDpSet<double> DataSetDouble;
typedef RWDpSet<long int> DataSetLI;
typedef RWDpSet<int> DataSetInt;
typedef RWDpSet<unsigned long int> DataSetULI;
typedef RWDpSet<unsigned int> DataSetUInt;
typedef RWDpSet<float> DataSetFloat;
typedef RWDpSet<short> DataSetShort;
typedef RWDpSet<unsigned short> DataSetUShort;
typedef RWDpSet<unsigned char> DataSetsUC;
//DataPoints Pre-Def Types
typedef RWDp<long double> DataPointsLD;
typedef RWDp<double> DataPointsDouble;
typedef RWDp<long int> DataPointsLI;
typedef RWDp<int> DataPointsInt;
typedef RWDp<unsigned long int> DataPointsULI;
typedef RWDp<unsigned int> DataPointsUInt;
typedef RWDp<float> DataPointsFloat;
typedef RWDp<short> DataPointsShort;
typedef RWDp<unsigned short> DataPointsUShort;
typedef RWDp<unsigned char> DataPointsUC;


#endif	/* RWPSET_H */

