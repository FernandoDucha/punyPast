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
using namespace std;

class MemoryRandomWalk {
public:
    MemoryRandomWalk(IRandomWalk * IRw, uint_64t ws);
    MemoryRandomWalk(IRandomWalk * IRw, uint_64t ws, int disc);
    virtual ~MemoryRandomWalk();

    IRWItem<QPollarF> * perform2DWalkNoCollision();
private:
    void generatePointsDiscrete(int divisor);
    vector<QPollarF> prunePoints(QPollarF * p, int n, QPollarF actual);
    bool recursiveSearch(QPollarF * p, int i, int *& ai);
    u_int64_t walksSize;
    double discretM_PI;
    vector<QPollarF> discPollarF;
    PollarSet PSet;
    IRandomWalk * RNG;
};

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

inline vector<QPollarF> MemoryRandomWalk::prunePoints(QPollarF * p, int n, QPollarF actual) {
    vector<QPollarF> ret;
    for (int i = 0; i < n; i++) {
        if (p[i].distQPollarF(actual) < 2.0) {
            ret.push_back(p[i]);
        }
    }
    return ret;
}

inline bool MemoryRandomWalk::recursiveSearch(QPollarF * p, int i, int *& ai) {
    vector<QPollarF> bag;
    auto beg = discPollarF.begin();
    auto end = discPollarF.end();
    if (*ai >= walksSize)
        return true;
    for (; beg != end; beg++) {
        sumQPollarF(p[i - 1], *beg, p[i]);
        p[i].setIndice(i);
        bool flag = true;
        for (int k = 0; k < i - 2; k++) {
            VEdge start(p[k], p[k + 1]);
            VEdge end(p[i - 1], p[i]);
            QPollarF x, y;
            int resp = VEdge::intersect2D_2Segments(start, end, x, y);
            if (resp) {
                flag = false;
                break;
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
                cout << i << endl;
                *ai = ++i;
                if (!recursiveSearch(p, i, ai)) {
                    --i;
                }
            }
        } while (bag.size() > 0 && *ai < walksSize);
    } else {
        return false;
    }
}

inline IRWItem<QPollarF> * MemoryRandomWalk::perform2DWalkNoCollision() {
    QPollarF * data = new QPollarF[walksSize];
    QPollarF a = QPollarF(1.0, RNG->Double()*2 * M_PI);
    sumQPollarF(data[0], a, a);
    data[0].setIndice(0);
    data[1] += a;
    data[1].setIndice(1);
    int i = 2;
    int * ai = new int[1];
    ai[0] = 2;
    PSet.addPollar(data[0]);
    PSet.addPollar(data[1]);
    recursiveSearch(data, i, ai);
    IRWItem<QPollarF> * ret = new PollarRwDp();
    ret->receiveData(data, walksSize);
    return ret;
}
#endif	/* MEMORYRANDOMWALK_H */

