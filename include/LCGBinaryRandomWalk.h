/* 
 * File:   LCGBinaryRandomWalk.h
 * Author: fordem
 *
 * Created on February 26, 2015, 10:21 PM
 */

#ifndef LCGBINARYRANDOMWALK_H
#define	LCGBINARYRANDOMWALK_H
#include "IRandomWalk.h"
#include "RNGLinearCong.h"
#include <QDebug>
#include "PollarRwDp.h"
#include <QPollarF.h>
#include "QPointFSLC.h"
#include "PollarSet.h"

class LCGBinaryRandomWalk : public IRandomWalk {
public:
    LCGBinaryRandomWalk();
    LCGBinaryRandomWalk(RNGLinearCong * rng, unsigned long int WS, u_int64_t nw);
    ~LCGBinaryRandomWalk();
    uint64_t GetNumberRandomWalks() const;
    unsigned long int GetWalkSize() const;
    void SetWalkSize(uint64_t);
    void SetNumberOfWalks(uint64_t);
    RWVSInt * performAllWalksByBitsOnLineRandom();
    RWVInt * performOneWalkByBitsOnLine();
    RWVInt * performOneWalkByBits();
    RWVSInt * performAllWalksByBits();
    DataPointsDouble * performOneWalkByPoints();
    bool canProduceSets();
    bool prepareData();
    DataSetDouble * performAllWalksByPoints();
    RWVInt * performWalkNByBits(uint64_t);
    DataPointsDouble * performWalkNByPoints(uint64_t);
    IRWItem<QPollarF> * perform2DWalk();
    void setup(RNGLinearCong * rng, u_int64_t ws, u_int64_t nw);
    double Double();
    uint_64t Integer();
    void resetSeed() {
        RNG->resetSeed();
    }
    IRWItem<QPollarF> * perform2DWalkNoCollision(int divisor);
private:
    IRNG * RNG;
    u_int64_t numberOfWalks;
    u_int64_t walksSize;
};

#endif	/* LCGBINARYRANDOMWALK_H */

