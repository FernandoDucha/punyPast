/* 
 * File:   IRWIHistogram.h
 * Author: fordem
 *
 * Created on August 30, 2015, 8:56 AM
 */

#ifndef IRWIHISTOGRAM_H
#define	IRWIHISTOGRAM_H
#include "IRWItem.h"
#include "IRWSet.h"
template <class Type> class IRWIHistogram {
public:
    IRWIHistogram();
    virtual IRWItem<long long> * frequencies(IRWItem<Type>*)=0;
    virtual IRWItem<long long> * frequencies(IRWSet<Type>*)=0;
    virtual void setBins(double max,double min,double step)=0;
    virtual ~IRWIHistogram();
private:

};
template <class Type> IRWIHistogram<Type>::IRWIHistogram() {
}

template <class Type> IRWIHistogram<Type>::~IRWIHistogram() {
}
#endif	/* IRWIHISTOGRAM_H */

