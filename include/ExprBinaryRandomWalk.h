/* 
 * File:   ExprBinaryRandomWalk.h
 * Author: fordem
 *
 * Created on February 15, 2015, 7:47 PM
 */

#ifndef EXPRBINARYRANDOMWALK_H
#define	EXPRBINARYRANDOMWALK_H

#include "IRandomWalk.h"
#include "ExprRNG.h"
#include "PollarRwDp.h"
class ExprBinaryRandomWalk : public IRandomWalk {
public:
    ExprBinaryRandomWalk();
    ExprBinaryRandomWalk(ExprRNG * rng, u_int64_t ws, u_int64_t nw);
    virtual ~ExprBinaryRandomWalk();
    uint64_t GetNumberRandomWalks() const;
    unsigned long int GetWalkSize() const;
    void SetWalkSize(uint64_t);
    void SetNumberOfWalks(uint64_t);
    RWVSInt * performAllWalksByBitsOnLineRandom();
    RWVInt * performOneWalkByBitsOnLine();
    RWVInt * performOneWalkByBits();
    DataSetDouble * performAllWalksByPoints();
    RWVSInt * performAllWalksByBits();
    DataPointsDouble * performOneWalkByPoints();
    bool canProduceSets();
    bool prepareData();
    RWVInt * performWalkNByBits(uint64_t);
    DataPointsDouble * performWalkNByPoints(uint64_t);
    IRWItem<QPollarF> * perform2DWalk();
    IRWItem<QPollarF> * perform2DWalkNoCollision(int);
    void setup(ExprRNG * rng, u_int64_t ws, u_int64_t nw);
    void resetSeed() {
        RNG->resetSeed();
    }
    uint_64t Integer();
    double Double();
private:
    ExprRNG * RNG;
    u_int64_t numberOfWalks;
    u_int64_t walksSize;

};

#endif	/* EXPRBINARYRANDOMWALK_H */

