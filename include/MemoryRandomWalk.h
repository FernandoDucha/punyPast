/* 
 * File:   MemoryRandomWalk.h
 * Author: fordem
 *
 * Created on August 17, 2015, 9:46 PM
 */

#ifndef MEMORYRANDOMWALK_H
#define	MEMORYRANDOMWALK_H
#include <vector>
#include "PollarSet.h"
#include "IRWItem.h"
#include <iostream>
#include "VEdge.h"
#include "PollarRwDp.h"
#include "IRandomWalk.h"
#include <QThread>
#include <QTime>
#include <sys/resource.h>

using namespace std;

class MemoryRandomWalk : public QThread {
    Q_OBJECT
public:
    MemoryRandomWalk(IRandomWalk * IRw, uint_64t ws);
    MemoryRandomWalk(IRandomWalk * IRw, uint_64t ws, int disc);
    MemoryRandomWalk(const MemoryRandomWalk &);
    virtual ~MemoryRandomWalk();
    void generatePointsDiscrete(int divisor);
    void setTime(uint_64t MaxTimeMS);
    uint64_t getWalksSize() const;
    IRandomWalk * getRW() const;
    IRWItem<QPollarF> * perform2DWalkNoCollision();
    void run()Q_DECL_OVERRIDE;
signals:
    void point(QPollarF *, int, double);
private:
    bool prunePoints(QPollarF p, QPollarF actual);
    bool recursiveSearch(QPollarF * p, int i, int *& ai);
    uint64_t walksSize;
    uint64_t maxTimeMS;
    double discretM_PI;
    vector<QPollarF> discPollarF;
    PollarSet PSet;
    IRandomWalk * RNG;
    QTime tm;
};

inline MemoryRandomWalk::MemoryRandomWalk(const MemoryRandomWalk& clone) {
    walksSize = clone.getWalksSize();
    RNG = clone.getRW();
}

inline IRandomWalk * MemoryRandomWalk::getRW() const {
    return RNG;
}

inline uint64_t MemoryRandomWalk::getWalksSize() const {
    return walksSize;
}

inline void MemoryRandomWalk::setTime(uint_64t MaxTimeMS) {
    maxTimeMS = MaxTimeMS;
}

inline void MemoryRandomWalk::run() {
    IRWItem<QPollarF> * p = perform2DWalkNoCollision();
    delete p;
}

inline MemoryRandomWalk::MemoryRandomWalk(IRandomWalk * IRw, uint_64t ws) : MemoryRandomWalk(IRw, ws, 4) {
}

inline MemoryRandomWalk::MemoryRandomWalk(IRandomWalk * IRw, uint_64t ws, int disc) {
    RNG = IRw;
    walksSize = ws;
    generatePointsDiscrete(disc);
}

inline MemoryRandomWalk::~MemoryRandomWalk() {
}

inline void MemoryRandomWalk::generatePointsDiscrete(int divisor) {
    discretM_PI = 2 * M_PI / divisor;
    for (int i = 0; i < divisor; i++) {
        discPollarF.push_back(QPollarF(1.0, discretM_PI * i));
    }
}

inline bool MemoryRandomWalk::prunePoints(QPollarF p, QPollarF actual) {
    if (p.distQPollarF(actual) < 2.0) {
        return true;
    }
    return false;
}

inline bool MemoryRandomWalk::recursiveSearch(QPollarF * p, int i, int *& ai) {
    vector<QPollarF> bag;
    auto beg = discPollarF.begin();
    auto end = discPollarF.end();
    if (*ai >= walksSize && tm.elapsed() < maxTimeMS)
        return true;
    for (; beg != end; beg++) {
        sumQPollarF(p[i - 1], *beg, p[i]);
        p[i].setIndice(i);
        bool flag = true;
        for (int k = 0; k < i - 2; k++) {
            VEdge start(p[k], p[k + 1]);
            VEdge end(p[i - 1], p[i]);
            QPollarF x, y;
            if (prunePoints(p[k], p[i])) {
                int resp = VEdge::intersect2D_2Segments(start, end, x, y);
                if (resp) {
                    flag = false;
                    break;
                }
            }
        }
        if (flag) {
            bag.push_back(*beg);
        }
    }


    if (bag.size()) {
        do {
            int choice = RNG->Integer() % bag.size();
            QPollarF t = bag.at(choice);
            bag.erase(bag.begin() + choice);
            sumQPollarF(p[i - 1], t, p[i]);
            p[i].setIndice(i);
            if (PSet.qtyPollar(p[i]) < 1) {
                PSet.addPollar(p[i]);
                *ai = ++i;
                emit point(p, i, tm.elapsed() / 1000.0);
                if (!recursiveSearch(p, i, ai)) {
                    --i;
                }
            }
        } while (bag.size() > 0 && *ai < walksSize && tm.elapsed() < maxTimeMS);
    } else {
        return false;
    }
}

inline IRWItem<QPollarF> * MemoryRandomWalk::perform2DWalkNoCollision() {
    tm.start();
    QPollarF * data = new QPollarF[walksSize];
    QPollarF a = QPollarF(1.0, RNG->Double()*2 * M_PI);
    sumQPollarF(data[0], a, a);
    data[0].setIndice(0);
    data[1] += a;
    data[1].setIndice(1);
    int * ai = new int[1];
    ai[0] = 2;
    PSet.addPollar(data[0]);
    PSet.addPollar(data[1]);
    recursiveSearch(data, *ai, ai);
    IRWItem<QPollarF> * ret = new PollarRwDp();
    ret->receiveData(data, walksSize);
    return ret;
}
#endif	/* MEMORYRANDOMWALK_H */

