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
    virtual IRWItem<double> * intervals();
private:
    inline bool difference(double a, int result,int result1){
        if(fabs((a-_intervals[result]))<this->threshold){
            return true;
        }else if(fabs((a-_intervals[result1]))<this->threshold){
            return true;
        }else if(a > _intervals[result] && a < _intervals[result1]){
            return true;
        }else{
            std::cout<<"Merda!!"<<std::endl;
            return false;
        }       
    }
    double ratio;
    int nBins;
    long long * freq;
    double * _intervals;
    double _max, _min;
};

template <class Type> IRWItem<double> * RWDpHistogram<Type>::intervals() {
    IRWItem<double> * response = new DataPointsDouble();
    response->receiveData(_intervals, nBins);
    return response;
}

template <class Type> IRWItem<long long> * RWDpHistogram<Type>::frequencies(IRWItem<Type>* irwi) {
    setBins(_max, _min, ratio);
    irwi->resetIterator();
    Type a;
    int counter = 0;
    while (irwi->getNext(a)) {
        int result = (double) a / ratio - _min / ratio;
        if(difference(a,result,result+1)){
            freq[result]++;
            counter++;
        }
    }
    if (counter != irwi->getNpoints()) {
        std::cerr << "Couldn't count all on Histogram!!! " <<counter<< std::endl;
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
    _intervals = nullptr;
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
            delete [] _intervals;
        }
        freq = new long long[nBins];
        _intervals = new double[nBins + 1];
    }
    for (int i = 0; i < nBins; i++) {
        freq[i] = 0;
        _intervals[i] = _min + i*ratio;
    }
    _intervals[nBins] = min + nBins*ratio;
}

template <class Type> RWDpHistogram<Type>::~RWDpHistogram() {
    delete [] freq;
}
#endif	/* RWDPHISTOGRAM_H */

