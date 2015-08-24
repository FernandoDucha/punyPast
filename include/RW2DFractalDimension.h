/* 
 * File:   RW2DFractalDimension.h
 * Author: fordem
 *
 * Created on August 22, 2015, 9:39 AM
 */

#ifndef RW2DFRACTALDIMENSION_H
#define	RW2DFRACTALDIMENSION_H
#include "RWPollarDpIntervalBuilder.h"

class RW2DFractalDimension {
public:
    RW2DFractalDimension(IRWItem<QPollarF>* irwp, double deltaX, double deltaY);
    virtual ~RW2DFractalDimension();
private:
    IRWIntervalBuilder<QPollarF> * rwpib;
    IRWItem<QPollarF> * item;
    QPollarF max;
    QPollarF min;
    double dx, dy;
    double * boxesX, *boxesY;
    long nBoxesX, nBoxesY;
};

inline RW2DFractalDimension::RW2DFractalDimension(IRWItem<QPollarF>* irwp, double scaleX, double scaleY) {
    rwpib = new RWPollarDpIntervalBuilder();
    item = irwp;
    max = irwp->getMax();
    min = irwp->getMin();
    dx = scaleX;
    dy = scaleY;

    double maxBoxX = max.rx() - min.rx();
    double maxBoxY = max.ry() - min.ry();
    long i, j;
    double k, k1;
    long i1, j1;
    do {
        j = 2;
        j1 = 2;
        i = 1;
        i1 = 1;
        k = 0;
        k1 = 0;
        int tBoxesX = log10((double) maxBoxX) / log10(dx) + 1.5;
        boxesX = new double[tBoxesX + 1];
        for (boxesX[1] = 1; j <= tBoxesX && boxesX[j - 1] < maxBoxX; i++)
            if ((k = pow(dx, i) + 0.5) > boxesX[j - 1])
                boxesX[j++] = k;
        if (boxesX[--j] > maxBoxX) --j;
        int tBoxesY = log10((double) maxBoxY) / log10(dy) + 1.5;
        boxesY = new double[tBoxesY + 1];
        for (boxesY[1] = 1; j1 <= tBoxesY && boxesY[j1 - 1] < maxBoxY; i1++)
            if ((k1 = pow(dy, i1) + 0.5) > boxesY[j1 - 1])
                boxesY[j1++] = k1;
        if (boxesY[--j1] > maxBoxY) --j1;
        if (j != j1) {
            if (j < j1) {
                dx -= 0.01 * dx;
            } else {
                dy -= 0.01 * dy;
            }
            delete [] boxesX;
            delete [] boxesY;
        }
    } while (j != j1);
    nBoxesX = j;
    nBoxesY = j1;
}

inline RW2DFractalDimension::~RW2DFractalDimension() {
    delete rwpib;
}
#endif	/* RW2DFRACTALDIMENSION_H */

