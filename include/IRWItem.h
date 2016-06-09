/* 
 * File:   IRWItem.h
 * Author: fordem
 *
 * Created on February 27, 2015, 7:28 PM
 */

#ifndef IRWITEM_H
#define	IRWITEM_H
#include <stdint.h>
#include <cmath>
#include "dieharder/brg_types.h"
template <class Type> class IRWSet;
template <class Type> class IRWItem {
public:
    typedef Type internType;
    IRWItem();
    virtual ~IRWItem();
    virtual void receiveData(Type * data, long unsigned int n)=0;
    virtual bool getNext(Type &)=0;
    virtual Type getElement(unsigned long int pos)=0;
    virtual unsigned long int getNpoints() const=0;
    virtual void resetIterator()=0;
    virtual Type getMin() const=0;
    virtual Type getMax() const=0;
    virtual void modulo()=0;
    virtual void setNpoints(unsigned long int Npoints)=0;
    virtual IRWItem<Type> & operator+=(IRWItem<Type> &)=0;
    virtual IRWItem<Type> & operator=(IRWItem<Type> &)=0;
    virtual IRWItem<Type> & operator-=(IRWItem<Type>&)=0;
    virtual bool operator==(IRWItem<Type>&)=0;
    virtual bool operator!=(IRWItem<Type>&)=0;
    virtual Type & operator[](uint32_t a)=0;
    virtual Type sum()=0;
    virtual unsigned long int getActualPoint()const=0;
    virtual void print()=0;
    virtual uint_32t getEpsilonN(double)=0;
//    virtual IRWSet<Type>* getIntervals(uint_32t)=0;
    virtual double average()=0;
    virtual IRWItem<double> * getIntegral()=0;
    virtual IRWItem<double> * power(double)=0;
    virtual Type * data() = 0;
private:

};
template <class Type> IRWItem<Type>::IRWItem(){
    
}
template <class Type> IRWItem<Type>::~IRWItem(){
    
}
#endif	/* IRWITEM_H */

