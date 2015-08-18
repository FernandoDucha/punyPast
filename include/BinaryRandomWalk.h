/* 
 * File:   BinaryRandomWalk.h
 * Author: fernando
 *
 * Created on 27 de Abril de 2013, 14:50
 */

#ifndef BINARYRANDOMWALK_H
#define	BINARYRANDOMWALK_H
#include <stdlib.h>
#include "FileRawBuffer.h"
#include "RWDpBase.h"
#include "RWVBase.h"
#include "IRandomWalk.h"
#include <math.h>
#include <iostream>

class BinaryRandomWalk : public IRandomWalk {
public:
    static unsigned char ** LookUpTable;
    static unsigned char * Mask;
    BinaryRandomWalk(FileRawBuffer * fbuffer);
    BinaryRandomWalk(FileRawBuffer * fbuffer, unsigned long int WS);
    BinaryRandomWalk(FileRawBuffer * fbuffer, unsigned long int WS, uint64_t NwalksBits);

    virtual ~BinaryRandomWalk();
    void SetWalkSize(unsigned long int walkSize);
    void SetNumberOfWalks(uint64_t numWalkSize);
    DataPointsDouble * performOneWalkByPoints();
    DataSetDouble * performAllWalksByPoints();
    RWVInt * performOneWalkByBits();
    RWVSInt * performAllWalksByBits();
    DataPointsDouble * performOneWalkByPointsOnLineRandom();
    DataSetDouble * performAllWalksByPointsOnLineRandom();
    RWVInt * performOneWalkByBitsOnLineRandom();
    RWVSInt * performAllWalksByBitsOnLineRandom();
    DataPointsDouble * performOneWalkByPointsOnLine();
    DataSetDouble * performAllWalksByPointsOnLine();
    RWVInt * performOneWalkByBitsOnLine();
    RWVSInt * performAllWalksByBitsOnLine();
    RWVInt * performWalkNByBits(uint64_t N);
    DataPointsDouble * performWalkNByPoints(uint64_t N);
    IRWItem<QPollarF> * perform2DWalk();
    IRWItem<QPollarF> * perform2DWalkNoCollision(int);
    static void createLookUpTable();
    static void createMaskTable();
    u_int64_t maximumPossibleWalks();
    unsigned long int GetWalkSize() const;
    void setNextRwkPos(int i);
    bool canProduceSets();
    void setup(FileRawBuffer * frb, unsigned long int WS, uint64_t NwalksBits);

    void resetSeed() {
        fbuffer->resetInitialPos();
    }

    bool prepareData() {
        fbuffer->generateBuffer(WalkByteSize * numberRandomWalks);
        return (fbuffer->getSize() > 0) ? true : false;
    }
    uint64_t GetNumberRandomWalks() const;
    double Double();
    uint_64t Integer();
private:
    FileRawBuffer * fbuffer;
    unsigned long int walkSize;
    unsigned char WalkMask;
    unsigned long int WalkByteSize;
    uint64_t numberRandomWalks;
};

inline void BinaryRandomWalk::SetWalkSize(unsigned long int walkSize) {
    this->walkSize = walkSize;
    if (this->walkSize % 8 != 0) {
        WalkMask = Mask[8 - (walkSize % 8)];
    }
    WalkByteSize = ceil((double) walkSize / 8);

}

inline void BinaryRandomWalk::SetNumberOfWalks(uint64_t NumberWalks) {
    numberRandomWalks = NumberWalks;
}
#endif	/* BINARYRANDOMWALK_H */

