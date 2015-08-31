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

class RWPollarHistogram : public IRWIHistogram<QPollarF> {
public:
    RWPollarHistogram();
    virtual IRWItem<long long> * frequencies(IRWItem<QPollarF>*);
    virtual IRWItem<long long> * frequencies(IRWSet<QPollarF>*);
    virtual void setBins(double max, double min, double step);
    void setBins(QPollarF max, QPollarF min, double step);
    virtual ~RWPollarHistogram();
private:
    double ratio;
    int nBins;
    long long * freq;
    double _max, _min;
};

inline void RWPollarHistogram::setBins(QPollarF max, QPollarF min, double step) {
    _max = (max.rx() > max.ry()) ? max.rx() : max.ry();
    _min = (min.rx() > min.ry()) ? min.rx() : min.ry();
    setBins(_max, _min, step);
}

inline void RWPollarHistogram::setBins(double max, double min, double step) {
    nBins = (max - min) / step + 1;
    ratio = step;
    _max = max;
    _min = min;
    if (freq) {
        delete [] freq;
    }
    freq = new long long[nBins];
    for (int i = 0; i < nBins; i++) {
        freq[i] = 0;
    }
}

inline IRWItem<long long> * RWPollarHistogram::frequencies(IRWItem<QPollarF>*irwi) {
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
    response->receiveData(freq, nBins);
    for (int i = 0; i < irws->getSize(); i++) {
        IRWItem<long long> * r = frequencies(irws->getElement(i));
        *response += *r;
        delete r;
    }
    return response;
}

inline RWPollarHistogram::RWPollarHistogram() {
    freq=nullptr;
}

inline RWPollarHistogram::~RWPollarHistogram() {
}
#endif	/* RWPOLLARHISTOGRAM_H */

