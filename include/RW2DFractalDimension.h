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
    RW2DFractalDimension(IRWItem<QPollarF>* irwp);
    virtual ~RW2DFractalDimension();
private:
    IRWIntervalBuilder<QPollarF> * rwpib;
    IRWItem<QPollarF> * item;
    QPollarF max;
    QPollarF min;
    
};
inline RW2DFractalDimension::RW2DFractalDimension(IRWItem<QPollarF>* irwp) {
    rwpib = new RWPollarDpIntervalBuilder();
    item = irwp;
    max = irwp->getMax();
    min = irwp->getMin();
}
inline RW2DFractalDimension::~RW2DFractalDimension() {
    delete rwpib;
}
#endif	/* RW2DFRACTALDIMENSION_H */

