/* 
 * File:   BrownianMotion.cpp
 * Author: fordem
 * 
 * Created on May 22, 2015, 3:04 PM
 */



#include "BrownianMotion.h"

BrownianMotion::BrownianMotion(IRNG * r,double ts, double d, double tt) {
    Nts = ts;
    diffusionCoef = d;
    totaltime = tt;
    rng=r;
//    rng = gsl_rng_alloc(gsl_rng_mt19937);
//    gsl_rng_set(rng, s);
}

BrownianMotion::BrownianMotion(IRNG * r,int part, double ts, double d, double tt) : BrownianMotion(r,ts, d, tt) {
    particles = part;
}

BrownianMotion::~BrownianMotion() {
}

QVector<QPollarF> BrownianMotion::BrownianMotionSimulation() {
    double dt;
    QPollarF dx;
    int j;
    double norm_dx;
    double s;
    QVector<QPollarF> x(Nts + 1);
    dt = totaltime / (double) (Nts - 1);
    x[0].setX(0.0);
    x[0].setY(0.0);
    for (j = 1; j < Nts; j++) {
        s = sqrt(diffusionCoef * dt) * gsl_ran_ugaussian_pdf(rng->randd());
        dx = gaussianUniform01();
        norm_dx = 0.0;
        norm_dx = norm_dx + pow(dx.x(), 2);
        norm_dx = norm_dx + pow(dx.y(), 2);

        norm_dx = sqrt(norm_dx);
        dx.setX(s * dx.x() / norm_dx);
        dx.setY(s * dx.y() / norm_dx);
        x[j].setX(x[j - 1].x() + dx.x());
        x[j].setY(x[j - 1].y() + dx.y());

    }
    return x;

}

void BrownianMotion::simulateAllParticles() {
    for (int i = 0; i < particles; i++) {
        AllParticles.push_back(BrownianMotionSimulation());
    }
    for (int i = 0; i < particles; i++) {
        double temp = 0.0;
        AllDisplacement.push_back(QVector<double>());
        for (int j = 0; j < Nts; j++) {
            temp = pow(AllParticles[i][j].x(), 2) + pow(AllParticles[i][j].y(), 2);
            AllDisplacement[i].push_back(temp);
        }
    }
}

QPollarF BrownianMotion::gaussianUniform01() {
    return QPollarF(gsl_ran_ugaussian_pdf(rng->randd()), gsl_ran_ugaussian_pdf(rng->randd()));
}

void BrownianMotion::clearSimulations() {
    AllDisplacement.clear();
    AllParticles.clear();
}

void BrownianMotion::setParticles(int p) {
    particles = p;
}

void BrownianMotion::setNTimeSteps(int nst) {
    Nts = nst;
}

void BrownianMotion::setDiffusionCoef(double d) {
    diffusionCoef = d;
}

void BrownianMotion::setTotalTime(double tt) {
    totaltime = tt;
}

void BrownianMotion::setSeed(int seed) {
//    gsl_rng_set(rng, seed);
    rng->setSeed(seed);
}

int BrownianMotion::getParticles() {
    return particles;
}

int BrownianMotion::getNTimeSteps() {
    return Nts;
}

double BrownianMotion::getDiffusionCoef() {
    return diffusionCoef;
}

double BrownianMotion::getTotalTime() {
    return totaltime;
}

QVector<QPollarF> BrownianMotion::getParticle(int partp) {
    if (AllParticles.size() > partp) {
        return AllParticles[partp];
    }
}

QVector<double> BrownianMotion::getDisplacement(int partp) {
    if (AllDisplacement.size() > partp) {
        return AllDisplacement[partp];
    }
}
IRWItem<double> * BrownianMotion::getDisplacementItem(int partp){
    IRWItem<double> * ret = new RWDp<double>();
    QVector<double> temp= getDisplacement(partp);
    ret->receiveData(temp.data(),temp.size());
    return ret;
}
IRWItem<QPollarF> * BrownianMotion::getParticleItem(int partp){
    IRWItem<QPollarF> * ret = new PollarRwDp();
    QVector<QPollarF> temp= getParticle(partp);
    ret->receiveData(temp.data(),temp.size());
    return ret;
}