/* 
 * File:   RW2DFractalDimension.h
 * Author: fordem
 *
 * Created on August 22, 2015, 9:39 AM
 */

#ifndef RW2DFRACTALDIMENSION_H
#define RW2DFRACTALDIMENSION_H
#include "RWPollarDpIntervalBuilder.h"
#include "VEdge.h"

class RW2DFractalDimension {
public:
    RW2DFractalDimension(IRWItem<QPollarF>* irwp, int minb, int maxb, double r);
    virtual ~RW2DFractalDimension();
    void process();
    void edgeprocess();
private:
    int calculateBoxes(int minb, int maxb, double ratio);
    IRWItem<QPollarF> * item;
    u_int32_t * boxes;
    int maxBox, minBox;
    u_int32_t nBoxes;
    double ratio;
};

inline int RW2DFractalDimension::calculateBoxes(int minb, int maxb, double ratio) {
    int tBoxes = log10((double) maxb / minb) / log10(ratio) + 1.5;
    boxes = new u_int32_t[tBoxes + 1];
    long i = 1, j = 2, k = 0;
    for (boxes[1] = minb; j <= tBoxes && boxes[j - 1] < maxb; i++)
        if ((k = minb * pow(ratio, i) + 0.5) > boxes[j - 1])
            boxes[j++] = k;
    if (boxes[--j] > maxb) --j;
    return (j);
}

inline RW2DFractalDimension::RW2DFractalDimension(IRWItem<QPollarF>* irwp, int minb, int maxb, double r) {
    item = irwp;
    minBox = minb;
    maxBox = maxb;
    ratio =r;
    nBoxes=calculateBoxes(minBox,maxBox,ratio);
}
inline void RW2DFractalDimension::process(){
    for(int i=1;i<=nBoxes;i++){
        QPollarF origin;
        int count=0;
        for(int j=0;j<item->getNpoints();j++){
            QPollarF a = item->getElement(j);
            if(origin.distQPollarF(a)<=boxes[i]){
                count++;
            }
        }
        cout<<boxes[i]<<" "<<count<<endl;
    }
}
inline void RW2DFractalDimension::edgeprocess(){
    for(int i=1;i<=nBoxes;i++){
        QPollarF origin;
        int count=0;
        for(int j=0;j<item->getNpoints()-1;j++){
            QPollarF a = item->getElement(j);
            QPollarF b = item->getElement(j+1);
            if(origin.distQPollarF(a)<=boxes[i]&&origin.distQPollarF(b)<=boxes[i]){
                count++;
            }
        }
        cout<<boxes[i]<<" "<<count<<endl;
    }
}
inline RW2DFractalDimension::~RW2DFractalDimension() {
    
}
#endif /* RW2DFRACTALDIMENSION_H */

