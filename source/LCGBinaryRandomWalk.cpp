/* 
 * File:   LCGBinaryRandomWalk.cpp
 * Author: fordem
 * 
 * Created on February 26, 2015, 10:21 PM
 */

#include <qt5/QtCore/qlogging.h>
#include <stack>
#include "LCGBinaryRandomWalk.h"
#include <utility>
#include "VEdge.h"
#include "PollarSet.h"
#include "MemoryRandomWalk.h"
#include "PollarRwDpSet.h"
#include "BrownianMotion.h"

LCGBinaryRandomWalk::LCGBinaryRandomWalk() {
    RNG = NULL;
    numberOfWalks = -1;
    walksSize = -1;
}

LCGBinaryRandomWalk::LCGBinaryRandomWalk(IRNG * rng, unsigned long int ws, uint64_t nw) {
    RNG = rng;
    numberOfWalks = nw;
    walksSize = ws;
}

void LCGBinaryRandomWalk::setup(RNGLinearCong * rng, u_int64_t ws, u_int64_t nw) {
    if (RNG == NULL) {
        RNG = rng;
        this->numberOfWalks = nw;
        this->walksSize = ws;
    } else if (!(*RNG == *rng) || (numberOfWalks != nw) || (walksSize != ws)) {
        RNG = rng;
        this->numberOfWalks = nw;
        this->walksSize = ws;
    }
}

LCGBinaryRandomWalk::~LCGBinaryRandomWalk() {
}

uint64_t LCGBinaryRandomWalk::GetNumberRandomWalks() const {
    return this->numberOfWalks;
}

unsigned long int LCGBinaryRandomWalk::GetWalkSize() const {
    return this->walksSize;
}

void LCGBinaryRandomWalk::SetWalkSize(uint64_t ws) {
    this->walksSize = ws;
}

void LCGBinaryRandomWalk::SetNumberOfWalks(uint64_t nw) {
    this->numberOfWalks = nw;
}

RWVInt * LCGBinaryRandomWalk::performOneWalkByBits() {
    RWVInt * ret = new RWVInt();
    int * data = new int[walksSize];
    for (u_int64_t i = 0; i < walksSize; i++) {
        data[i] = (RNG->randd() > 0.5) ? 1 : -1;
    }
    ret->receiveData(data, walksSize);
    delete [] data;
    return ret;
}

DataPointsDouble * LCGBinaryRandomWalk::performOneWalkByPoints() {
    DataPointsDouble * ret = new DataPointsDouble();
    double * data = new double[walksSize];
    double acumulado = 0;
    for (u_int64_t i = 0; i < walksSize; i++) {
        acumulado += (RNG->randd() > 0.5) ? 1 : -1;
        data[i] = acumulado;
    }
    ret->receiveData(data, walksSize);
    delete [] data;
    return ret;
}

DataSetDouble * LCGBinaryRandomWalk::performAllWalksByPoints() {
    RNG->resetSeed();
    DataSetDouble * ret = new DataSetDouble(numberOfWalks);
    for (u_int64_t i = 0; i < numberOfWalks; i++) {
        ret->put(performOneWalkByPoints());
    }
    return ret;
}

RWVSInt * LCGBinaryRandomWalk::performAllWalksByBits() {
    RNG->resetSeed();
    RWVSInt * ret = new RWVSInt(numberOfWalks);
    for (u_int64_t i = 0; i < numberOfWalks; i++) {
        ret->put(performOneWalkByBits());
    }
    return ret;
}

bool LCGBinaryRandomWalk::prepareData() {
    return true;
}

bool LCGBinaryRandomWalk::canProduceSets() {
    return true;
}

RWVInt * LCGBinaryRandomWalk::performWalkNByBits(uint64_t) {
    return NULL;
}

DataPointsDouble * LCGBinaryRandomWalk::performWalkNByPoints(uint64_t) {
    return NULL;
}

IRWItem<QPollarF> * LCGBinaryRandomWalk::perform2DWalk() {
    QPollarF * data = new QPollarF[walksSize];
    for (int i = 1; i < walksSize; i++) {
        QPollarF a = QPollarF(1.0, RNG->randd()*2 * M_PI);
        sumQPollarF(data[i - 1], a, a);
        data[i] += a;
    }
    IRWItem<QPollarF> * ret = new PollarRwDp();
    ret->receiveData(data, walksSize);
    delete [] data;
    return ret;
}

double LCGBinaryRandomWalk::Double() {
    return RNG->randd();
}

uint_64t LCGBinaryRandomWalk::Integer() {
    return RNG->randi();
}

IRWItem<QPollarF> * LCGBinaryRandomWalk::perform2DWalkNoCollision(int divisor) {
    MemoryRandomWalk memrw(this, walksSize, divisor);
    return memrw.perform2DWalkNoCollision();
}

IRWItem<QPollarF> * LCGBinaryRandomWalk::brownianMotion(double diff) {
    BrownianMotion bm(RNG,1,walksSize,diff,walksSize);
    bm.simulateAllParticles();
    return bm.getParticleItem(0);
}

IRWSet<QPollarF>* LCGBinaryRandomWalk::multipleBrownianMotion(double diff) {
    RNG->resetSeed();
    PollarRwDpSet * ret = new PollarRwDpSet(numberOfWalks);
    for(int i=0;i<numberOfWalks;i++){
        ret->put(brownianMotion(diff));
    }
    return ret;
}
IRWItem<double> * LCGBinaryRandomWalk::brownianMotionDisplacement(double diff) {
    BrownianMotion bm(RNG,1,walksSize,diff,walksSize);
    bm.simulateAllParticles();
    return bm.getDisplacementItem(0);
}

IRWSet<double>* LCGBinaryRandomWalk::multipleBrownianMotionDisplacement(double diff) {
    RNG->resetSeed();
    IRWSet<double> * ret = new RWDpSet<double>(numberOfWalks);;
    for(int i=0;i<numberOfWalks;i++){
        ret->put(brownianMotionDisplacement(diff));
    }
    return ret;
}
RWVSInt * LCGBinaryRandomWalk::performAllWalksByBitsOnLineRandom() {
    RNG->resetSeed();
    return performAllWalksByBits();
}

RWVInt * LCGBinaryRandomWalk::performOneWalkByBitsOnLine() {
    return performOneWalkByBits();
}

