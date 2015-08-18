/* 
 * File:   ExprBinaryRandomWalk.cpp
 * Author: fordem
 * 
 * Created on February 15, 2015, 7:47 PM
 */

#include "ExprBinaryRandomWalk.h"

ExprBinaryRandomWalk::ExprBinaryRandomWalk() {
    RNG = NULL;
    this->numberOfWalks = -1;
    this->walksSize = -1;
}

void ExprBinaryRandomWalk::setup(ExprRNG * rng, u_int64_t ws, u_int64_t nw) {
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

ExprBinaryRandomWalk::ExprBinaryRandomWalk(ExprRNG * rng, u_int64_t ws, u_int64_t nw) {
    RNG = rng;
    this->numberOfWalks = nw;
    this->walksSize = ws;
}

uint64_t ExprBinaryRandomWalk::GetNumberRandomWalks() const {
    return this->numberOfWalks;
}

unsigned long int ExprBinaryRandomWalk::GetWalkSize() const {
    return this->walksSize;
}

void ExprBinaryRandomWalk::SetWalkSize(uint64_t ws) {
    this->walksSize = ws;
}

void ExprBinaryRandomWalk::SetNumberOfWalks(uint64_t nw) {
    this->numberOfWalks = nw;
}

RWVInt * ExprBinaryRandomWalk::performOneWalkByBits() {
    RWVInt * ret = new RWVInt();
    int * data = new int[walksSize];
    for (u_int64_t i = 0; i < walksSize; i++) {
        data[i] = (RNG->generateNumber() % 2) ? 1 : -1;
    }
    ret->receiveData(data, walksSize);
    return ret;
}

DataPointsDouble * ExprBinaryRandomWalk::performOneWalkByPoints() {
    DataPointsDouble * ret = new DataPointsDouble();
    double * data = new double[walksSize];
    double acumulado = 0;
    for (u_int64_t i = 0; i < walksSize; i++) {
        acumulado += (RNG->generateNumber() % 2) ? 1 : -1;
        data[i] = acumulado;
    }
    ret->receiveData(data, walksSize);
    delete data;
    return ret;
}

DataSetDouble * ExprBinaryRandomWalk::performAllWalksByPoints() {
    RNG->resetSeed();
    DataSetDouble * ret = new DataSetDouble(numberOfWalks);
    for (u_int64_t i = 0; i < numberOfWalks; i++) {
        ret->put(performOneWalkByPoints());
    }
    return ret;
}

RWVSInt * ExprBinaryRandomWalk::performAllWalksByBits() {
    RNG->resetSeed();
    RWVSInt * ret = new RWVSInt(numberOfWalks);
    for (u_int64_t i = 0; i < numberOfWalks; i++) {
        ret->put(performOneWalkByBits());
    }
    return ret;
}

ExprBinaryRandomWalk::~ExprBinaryRandomWalk() {

}

bool ExprBinaryRandomWalk::prepareData() {
    return true;
}

bool ExprBinaryRandomWalk::canProduceSets() {
    return true;
}

RWVInt * ExprBinaryRandomWalk::performWalkNByBits(uint64_t) {
    return NULL;
}

DataPointsDouble * ExprBinaryRandomWalk::performWalkNByPoints(uint64_t) {
    return NULL;
}

IRWItem<QPollarF> * ExprBinaryRandomWalk::perform2DWalk() {
    QPollarF * data = new QPollarF[walksSize];
    long long max = std::numeric_limits<long long>::max();
    for (int i = 1; i < walksSize; i++) {
        double generated = (double) RNG->generateNumber() / max;
        QPollarF a = QPollarF(1.0, generated * 2 * M_PI);
        sumQPollarF(data[i - 1], a, a);
        data[i] += a;
    }
    IRWItem<QPollarF> * ret = new PollarRwDp();
    ret->receiveData(data, walksSize);
    return ret;
}

uint_64t ExprBinaryRandomWalk::Integer() {
    return RNG->generateNumber();
}

double ExprBinaryRandomWalk::Double() {
    long long max = std::numeric_limits<long long>::max();
    double generated = (double) RNG->generateNumber() / max;
    return generated;
}

IRWItem<QPollarF> * ExprBinaryRandomWalk::perform2DWalkNoCollision(int) {
    return nullptr;
}

RWVSInt * ExprBinaryRandomWalk::performAllWalksByBitsOnLineRandom() {
    RNG->resetSeed();
    return performAllWalksByBits();
}

RWVInt * ExprBinaryRandomWalk::performOneWalkByBitsOnLine() {
    return performOneWalkByBits();
}
