/* 
 * File:   MemoryRandomWalk.h
 * Author: fordem
 *
 * Created on August 17, 2015, 9:46 PM
 */

#ifndef MEMORYRANDOMWALK_H
#define MEMORYRANDOMWALK_H
#include <vector>
#include "PollarSet.h"
#include "IRWItem.h"
#include <iostream>
#include "VEdge.h"
#include "PollarRwDp.h"
#include "IRandomWalk.h"
#include "MemAllocWidget.h"
#include <QThread>
#include <QTime>
#include <sys/resource.h>
#include <gsl/gsl_math.h>
using namespace std;

class MemoryRandomWalk : public QThread {
    Q_OBJECT
public:

    MemoryRandomWalk(IRandomWalk * IRw, uint_64t ws);
    MemoryRandomWalk(IRandomWalk * IRw, uint_64t ws, int disc);
    MemoryRandomWalk(const MemoryRandomWalk &);
    MemoryRandomWalk();
    virtual ~MemoryRandomWalk();
    void generatePointsDiscrete(int divisor);
    void setTime(uint_64t MaxTimeMS);
    void setIRandomWalk(IRandomWalk * IRw);
    uint64_t getWalksSize() const;
    IRandomWalk * getRW() const;
    IRWItem<QPollarF> * perform2DWalkNoCollision();
    void printVEdge(VEdge v, VEdge w);
    void printPath(QPollarF * p, int i);
    void run()Q_DECL_OVERRIDE;
signals:
    void point(QPollarF *, int, double);
private:
    bool prunePoints(QPollarF p, QPollarF actual);
    bool pruneEdge(VEdge v, QPollarF actual);
    bool recursiveSearch(QVector<QPollarF> & p, int i, int *& ai);
    uint64_t walksSize;
    uint64_t maxTimeMS;
    double discretM_PI;
    vector<QPollarF> discPollarF;
    PollarSet PSet;
    IRandomWalk * RNG;
    QTime tm;
};

inline void MemoryRandomWalk::setIRandomWalk(IRandomWalk * IRw) {
    RNG = IRw;
    walksSize = IRw->GetWalkSize();
}

inline MemoryRandomWalk::MemoryRandomWalk() {

}

inline MemoryRandomWalk::MemoryRandomWalk(const MemoryRandomWalk& clone) {
    walksSize = clone.getWalksSize();
    RNG = clone.getRW();
}

inline void MemoryRandomWalk::printVEdge(VEdge v, VEdge w) {
    cout << v.start.x() << " " << v.start.y() << " " << w.start.x() << " " << w.start.y() << endl;
    cout << v.end.x() << " " << v.end.y() << " " << w.end.x() << " " << w.end.y() << endl;

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
    maxTimeMS = 3600 * 1000;
}

inline MemoryRandomWalk::~MemoryRandomWalk() {
}

inline void MemoryRandomWalk::generatePointsDiscrete(int divisor) {
    discPollarF.clear();
    discretM_PI = 2 * M_PI / divisor;
    for (int i = 0; i < divisor; i++) {
        discPollarF.push_back(QPollarF(1.0, discretM_PI * i));
    }
}

inline bool MemoryRandomWalk::pruneEdge(VEdge v, QPollarF actual) {
    double d = dist_Point_to_Segment(actual, v);
//    double angle= 2 * M_PI / discPollarF.size();
//    QPollarF a(1.0,angle);
//    QPollarF b;
//    b.rx()--;
//    double dist = b.distQPollarF(a);
    if (d <= 2) {
        return true;
    }
    return false;
}

inline bool MemoryRandomWalk::prunePoints(QPollarF p, QPollarF actual) {
    if (p.distQPollarF(actual) <= 2.0) {
        return true;
    }
    return false;
}

inline void MemoryRandomWalk::printPath(QPollarF * p, int i) {
    for (int j = 1; j <= i; j++) {
        cout << p[j].x() << " " << p[j].y() << endl;
    }
}

inline bool MemoryRandomWalk::recursiveSearch(QVector<QPollarF> & p, int i, int *& ai) {
    QVector<QPollarF> bag = QVector<QPollarF>::fromStdVector(discPollarF);
    if (*ai >= walksSize + 1 && tm.elapsed() < maxTimeMS)
        return true;
    while (bag.size() > 0 && *ai < walksSize + 1 && tm.elapsed() < maxTimeMS) {
        int choice = RNG->Double() * bag.size();
        QPollarF t = bag.at(choice);
        bag.remove(choice);
        sumQPollarF(p[i - 1], t, p[i]);
        p[i].setIndice(i);
        VEdge end(p[i - 1], p[i]);
        bool flag = true;
        for (int k = 1; k <= i - 2; k++) {
            VEdge start(p[k], p[k + 1]);
            QPollarF x, y;
            if (start.end != end.start && start.end != end.start && (start.end != end.end && start.start != end.start)) {
                if (pruneEdge(start, p[i]) && pruneEdge(start, p[i - 1])) {
                    int r = intersect2D_2Segments(start, end, x, y);
                    if (r != 0) {
                        flag = false;
                    }
                }
            }
        }
        if (PSet.qtyPollar(p[i]) < 1 && flag) {
            PSet.addPollar(p[i]);
            *ai = ++i;
            emit point(p.data(), i, tm.elapsed() / 1000.0);
            if (!recursiveSearch(p, i, ai)) {
                *ai = --i;
            } else {
                return true;
            }
        }
    }
    return false;

}

inline IRWItem<QPollarF> * MemoryRandomWalk::perform2DWalkNoCollision() {
    PSet.clear();
    tm.start();
    //    QPollarF * data = new QPollarF[walksSize + 1];
    QVector<QPollarF> data(walksSize + 1);
    RNG->resetSeed();
    QPollarF a = QPollarF(1.0, RNG->Double()*2 * M_PI); //discPollarF[discPollarF.size()*RNG->Double()];
    sumQPollarF(data[0], a, a);
    data[0].setIndice(0);
    data[1] += a;
    data[1].setIndice(1);
    int * ai = new int[1];
    ai[0] = 2;
    PSet.addPollar(data[0]);
    PSet.addPollar(data[1]);
    recursiveSearch(data, *ai, ai);
    emit point(data.data(), *ai, tm.elapsed() / 1000.0);
    delete ai;
    IRWItem<QPollarF> * ret = new PollarRwDp();
    ret->receiveData(&data.data()[1], walksSize);
    return ret;
}
#endif /* MEMORYRANDOMWALK_H */

