/* 
 * File:   RWDpHistogram.h
 * Author: fordem
 *
 * Created on August 30, 2015, 9:14 AM
 */

#ifndef RWDPHISTOGRAM_H
#define	RWDPHISTOGRAM_H
#include "IRWIHistogram.h"
#include "IRWSet.h"
#include "RWDpBase.h"
#include <cmath>

template <class Type> class RWDpHistogram : public IRWIHistogram<Type> {
public:
    RWDpHistogram(double max, double min, double step);
    virtual ~RWDpHistogram();
    virtual void setBins(double max, double min, double step);
    virtual IRWItem<long long> * frequencies(IRWItem<Type> * irwi);
    virtual IRWItem<long long> * frequencies(IRWSet<Type> * irws);

private:
    double ratio;
    int nBins;
    long long * freq;
    double _max, _min;
};

template <class Type> IRWItem<long long> * RWDpHistogram<Type>::frequencies(IRWItem<Type>* irwi) {
    setBins(_max, _min, ratio);
    irwi->resetIterator();
    Type a;
    while (irwi->getNext(a)) {
        int result = (double) a / ratio - _min / ratio;
        freq[result]++;
    }
    IRWItem<long long> * response = new DataPointsLI();
    response->receiveData(freq, nBins);
    return response;
}

template <class Type> IRWItem<long long> * RWDpHistogram<Type>::frequencies(IRWSet<Type>* irws) {
    IRWItem<long long> * response = new DataPointsLI();
    response->receiveData(freq, nBins);
    for (int i = 0; i < irws->getSize(); i++) {
        IRWItem<long long> * r = frequencies(irws->getElement(i));
        *response += *r;
        delete r;
    }
    return response;
}

template <class Type> RWDpHistogram<Type>::RWDpHistogram(double max, double min, double step) {
    freq = nullptr;
    _max = std::numeric_limits<double>::max();
    _min = -std::numeric_limits<double>::min();
    ratio = std::numeric_limits<double>::max();
    setBins(max, min, step);
}

template <class Type> void RWDpHistogram<Type>::setBins(double max, double min, double step) {
    if (max != _max || min != _min || step != ratio) {
        nBins = (max - min) / step + 1;
        ratio = step;
        _max = max;
        _min = min;
        if (freq) {
            delete [] freq;
        }
        freq = new long long[nBins];
    }
    for (int i = 0; i < nBins; i++) {
        freq[i] = 0;
    }
}

template <class Type> RWDpHistogram<Type>::~RWDpHistogram() {
    delete [] freq;
}
#endif	/* RWDPHISTOGRAM_H */

