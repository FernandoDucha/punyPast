/* 
 * File:   IRandomWalk.h
 * Author: fordem
 *
 * Created on February 15, 2015, 8:49 PM
 */

#ifndef IRANDOMWALK_H
#define	IRANDOMWALK_H
#include "RWVBase.h"
#include "RWDpBase.h"
#include "IRNG.h"
#include "QPollarF.h"
class IRandomWalk {
public:
    IRandomWalk();
    virtual ~IRandomWalk();
    virtual uint64_t GetNumberRandomWalks() const=0;
    virtual unsigned long int GetWalkSize() const=0;
    virtual void SetWalkSize(uint64_t) = 0;
    virtual void SetNumberOfWalks(uint64_t) = 0;
    virtual IRWSet<int> * performAllWalksByBitsOnLineRandom()=0;
    virtual IRWItem<int> * performOneWalkByBitsOnLine()=0;
    virtual IRWItem<int> * performOneWalkByBits()=0;
    virtual IRWSet<int> * performAllWalksByBits()=0;
    virtual IRWItem<double> * performOneWalkByPoints()=0;
    virtual bool canProduceSets()=0;
    virtual bool prepareData()=0;
    virtual IRWSet<double> * performAllWalksByPoints()=0;
    virtual IRWItem<int> * performWalkNByBits(uint64_t)=0;
    virtual IRWItem<double> * performWalkNByPoints(uint64_t)=0;
    virtual IRWItem<QPollarF> * perform2DWalk()=0;
    virtual IRWItem<QPollarF> * perform2DWalkNoCollision(int)=0;
    virtual void resetSeed()=0; 
    virtual double Double()=0;
    virtual uint_64t Integer()=0;
private:

};

#endif	/* IRANDOMWALK_H */

