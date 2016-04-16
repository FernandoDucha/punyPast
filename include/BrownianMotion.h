/* 
 * File:   BrownianMotion.h
 * Author: fordem
 *
 * Created on May 22, 2015, 3:04 PM
 */

#ifndef BROWNIANMOTION_H
#define	BROWNIANMOTION_H
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <cmath>
#include <iostream>
#include <QPointF>
#include <QVector>
#include "IRWItem.h"
#include "RWDp.h"
#include "PollarRwDp.h"
#include "QPollarF.h"
#include "IRNG.h"
using namespace std;

class BrownianMotion {
public:
    BrownianMotion(IRNG* r,double ts, double d, double tt);
    BrownianMotion(IRNG* r,int part, double ts, double d, double tt);
    virtual ~BrownianMotion();
    void simulateAllParticles();
    void clearSimulations();
    void setParticles(int);
    void setNTimeSteps(int);
    void setDiffusionCoef(double);
    void setTotalTime(double);
    void setSeed(int);
    int getParticles();
    int getNTimeSteps();
    double getDiffusionCoef();
    double getTotalTime();
    QVector<QPollarF> getParticle(int);
    QVector<double> getDisplacement(int);
    IRWItem<double> * getDisplacementItem(int);
    IRWItem<QPollarF> * getParticleItem(int);
    
private:
    QVector<QPollarF>BrownianMotionSimulation();
    QPollarF gaussianUniform01();
    int particles;
    int Nts;
    double diffusionCoef;
    double totaltime;
//    gsl_rng * rng;
    IRNG * rng;
    QVector<QVector<QPollarF>> AllParticles;
    QVector<QVector<double>> AllDisplacement;

};

#endif	/* BROWNIANMOTION_H */

