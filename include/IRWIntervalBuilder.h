/* 
 * File:   IRWIntervalBuilder.h
 * Author: fordem
 *
 * Created on June 2, 2015, 11:06 PM
 */

#ifndef IRWINTERVALBUILDER_H
#define	IRWINTERVALBUILDER_H
#include "IRWItem.h"
#include "IRWSet.h"

template <class Type> class IRWIntervalBuilder {
public:

    IRWIntervalBuilder() {
    }

    virtual ~IRWIntervalBuilder() {
    }
    virtual IRWSet<Type>* getIntervals(IRWItem<Type>*, uint_32t) = 0;
    virtual IRWSet<Type>* getOverlapingIntervals(IRWItem<Type>*, uint_32t) = 0;
    virtual IRWSet<Type>* getOverlapingIntervals(IRWItem<Type>*, uint_32t, uint_32t) = 0;
    virtual IRWItem<Type>* getIntervalsI(IRWItem<Type>*, uint_32t, uint_32t) = 0;
    virtual IRWItem<Type>* getOverlapingIntervalsI(IRWItem<Type>*, uint_32t, uint_32t) = 0;
    virtual IRWItem<Type>* getOverlapingIntervalsI(IRWItem<Type>*, uint_32t, uint_32t, uint_32t) = 0;
    virtual uint_32t overlapingIntervals(IRWItem<Type>*, uint_32t);
    virtual uint_32t overlapingIntervals(IRWItem<Type>*, uint_32t, uint_32t);
    virtual uint_32t intervals(IRWItem<Type>*, uint_32t);
    virtual IRWItem<Type>* produceLinearInterval(double, double, double) = 0;
    virtual IRWItem<Type>* produceLogarithmicInterval(double, double, double) = 0;
private:

};
 template <class Type>uint_32t IRWIntervalBuilder<Type>::overlapingIntervals(IRWItem<Type>* Input, uint_32t N){
     return Input->getNpoints()-N+1;
 }
 template <class Type>uint_32t IRWIntervalBuilder<Type>::overlapingIntervals(IRWItem<Type>* Input, uint_32t N, uint_32t Increment){
     return ((double)Input->getNpoints()-N)/Increment+1;
 }
 template <class Type>uint_32t IRWIntervalBuilder<Type>::intervals(IRWItem<Type>* Input, uint_32t N){
     return (double)Input->getNpoints()/N;
 }
#endif	/* IRWINTERVALBUILDER_H */
