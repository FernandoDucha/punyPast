/* 
 * File:   IRWSet.h
 * Author: fordem
 *
 * Created on March 4, 2015, 6:10 PM
 */

#ifndef IRWSET_H
#define	IRWSET_H
#include <limits>
#include "IRWItem.h"
using namespace std;
template <class Type>class IRWSet {
public:
    IRWSet();
    virtual ~IRWSet();
    virtual void put(IRWItem<Type> * a) = 0;
    virtual IRWItem<Type> * getNext() = 0;
    virtual IRWItem<Type> * getElement(unsigned long int p) = 0;
    virtual unsigned long int getSize() const = 0;
    virtual void resetIterator() = 0;
    virtual Type getMin() const = 0;
    virtual Type getMax() const = 0;
    virtual void setTypeMin()=0;
    virtual void setTypeMax()=0;
protected:
    Type min, max;

};

template <class Type>IRWSet<Type>::IRWSet() {
    
}

template <class Type>IRWSet<Type>::~IRWSet() {
}
#endif	/* IRWSET_H */

