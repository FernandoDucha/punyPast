/* 
 * File:   DataPointsSet.h
 * Author: fernando
 *
 * Created on 27 de Abril de 2013, 14:52
 */

#ifndef RWDPSET_H
#define	RWDPSET_H
#include <IRWSet.h>
#include <vector>
#include "RWDp.h"
#include <stdio.h>
#include "GeneralUsage.h"
using namespace std;
template <class Type> class IRWSet;

template <class type> class RWDpSet : public IRWSet<type> {
public:
    RWDpSet(unsigned long int size);
    virtual ~RWDpSet();
    void put(IRWItem<type> * a);
    IRWItem<type> * getNext();
    IRWItem<type> * getElement(unsigned long int p);
    unsigned long int getSize() const;
    void resetIterator();
    type getMin() const;
    type getMax() const;

    void setTypeMax() {
        this->max = numeric_limits<type>::min();
    }

    void setTypeMin() {
        this->min = numeric_limits<type>::max();
    }
private:
    IRWItem<type> ** list;
    unsigned long int size;
    unsigned long int pos, pos_temp;
};

template <class type> void RWDpSet<type>::put(IRWItem<type> * a) {
    if (pos < size) {
        list[pos] = a;
        if (a->getMax() > this->max) {
            this->max = a->getMax();
        }
        if (a->getMin() < this->min) {
            this->min = a->getMin();
        }
        pos++;
    } else {
        fprintf(stderr, "ERRO: Esse conjunto não suporta mais que %lu elementos.", size);
    }
}

template <class type> RWDpSet<type>::RWDpSet(unsigned long int size) {
    list = new IRWItem<type>*[size];
    for (unsigned int i = 0; i < size; i++) {
        list[i] = NULL;
    }
    this->size = size;
    pos_temp = pos = 0;
    setTypeMax();
    setTypeMin();
}

template <class type> RWDpSet<type>::~RWDpSet() {
    for (unsigned int i = 0; i < size; i++) {
        if (list[i] != NULL) {
            delete list[i];
        }
    }
    delete [] list;
}

template <class type>IRWItem<type> * RWDpSet<type>::getNext() {
    if (pos_temp <= pos) {
        int p = pos_temp;
        pos_temp++;
        return list[p];
    } else {
        pos_temp = 0;
        return NULL;
    }
}

template <class type>IRWItem<type> * RWDpSet<type>::getElement(unsigned long int p) {
    if (p < size) {
        return list[p];
    } else {
        return NULL;
    }
}

template <class type>unsigned long int RWDpSet<type>::getSize() const {
    return size;
}

template <class type> void RWDpSet<type>::resetIterator() {
    pos_temp = 0;
}

template <class type> type RWDpSet<type>::getMin() const {
    return this->min;
}

template <class type>type RWDpSet<type>::getMax() const {
    return this->max;
}
#endif	/* DATAPOINTSSET_H */

