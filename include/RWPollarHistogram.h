/* 
 * File:   RWPollarHistogram.h
 * Author: fordem
 *
 * Created on August 30, 2015, 5:45 PM
 */

#ifndef RWPOLLARHISTOGRAM_H
#define	RWPOLLARHISTOGRAM_H
#include "IRWIHistogram.h"
#include "QPollarF.h"
#include "RWDpBase.h"
#include <limits>

class RWPollarHistogram : public IRWIHistogram<QPollarF> {
public:
    RWPollarHistogram();
    virtual IRWItem<long long> * frequencies(IRWItem<QPollarF>*);
    virtual IRWItem<long long> * frequencies(IRWSet<QPollarF>*);
    virtual void setBins(double max, double min, double step);
    void setBins(QPollarF max, QPollarF min, double step);
    virtual ~RWPollarHistogram();

    virtual IRWItem<double>* intervals();

private:
    double ratio;
    int nBins;
    long long * freq;
    double _max, _min;
};
inline IRWItem<double>* RWPollarHistogram::intervals(){
    return nullptr;
}
inline void RWPollarHistogram::setBins(QPollarF max, QPollarF min, double step) {
    double _tmax = (max.rx() > max.ry()) ? max.rx() : max.ry();
    double _tmin = (min.rx() > min.ry()) ? min.rx() : min.ry();
    setBins(_tmax, _tmin, step);
}

inline void RWPollarHistogram::setBins(double max, double min, double step) {
    if (ratio != step || _max != max || _min != min) {
        ratio = step;
        _max = max;
        _min = min;
        nBins = (max - min) / step + 1;
        if (freq){
            delete [] freq;
            freq=nullptr;
        }
        freq = new long long[nBins];
    }
    for (int i = 0; i < nBins; i++) {
        freq[i] = 0;
    }
}

inline IRWItem<long long> * RWPollarHistogram::frequencies(IRWItem<QPollarF>*irwi) {
    setBins(_max, _min, ratio);
    irwi->resetIterator();
    QPollarF a;
    while (irwi->getNext(a)) {
        int result1 = (double) a.rx() / ratio - _min / ratio;
        freq[result1]++;
        int result2 = (double) a.ry() / ratio - _min / ratio;
        freq[result2]++;
    }
    IRWItem<long long> * response = new DataPointsLI();
    response->receiveData(freq, nBins);
    return response;
}

inline IRWItem<long long> * RWPollarHistogram::frequencies(IRWSet<QPollarF>*irws) {
    IRWItem<long long> * response = new DataPointsLI();
    for (int i = 0; i < irws->getSize(); i++) {
        IRWItem<long long> * r = frequencies(irws->getElement(i));
        *response += *r;
        delete r;
    }
    return response;
}

inline RWPollarHistogram::RWPollarHistogram() {
    freq = nullptr;
    _max = std::numeric_limits<double>::max();
    _min = -std::numeric_limits<double>::min();
}

inline RWPollarHistogram::~RWPollarHistogram() {
}
#endif	/* RWPOLLARHISTOGRAM_H */

