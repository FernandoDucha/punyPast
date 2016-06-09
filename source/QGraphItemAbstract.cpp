/* 
 * File:   QGraphItemAbstract.cpp
 * Author: fernando
 * 
 * Created on 4 de Maio de 2013, 10:18
 */

#include <qt5/QtCore/qvector.h>

#include "QGraphItemAbstract.h"
double QGraphItemAbstract::tX=0;
double QGraphItemAbstract::sX=0;
double QGraphItemAbstract::tY=0;
double QGraphItemAbstract::sY=0;    
double QGraphItemAbstract::rW=0;
double QGraphItemAbstract::rH=0;
double QGraphItemAbstract::w=0;
double QGraphItemAbstract::h=0;
double QGraphItemAbstract::cw=0;
double QGraphItemAbstract::ch=0;
double QGraphItemAbstract::offset=0;
double QGraphItemAbstract::Xintervalsw=0;
double QGraphItemAbstract::Yintervalsh=0;
double QGraphItemAbstract::ZeroPoint=0;
Axis QGraphItemAbstract::axis=Axis();
QGraphItemAbstract::QGraphItemAbstract() {
}
QGraphItemAbstract::~QGraphItemAbstract() {
}
void QGraphItemAbstract::setAxis(Axis novo){
    axis+=novo;
}
void QGraphItemAbstract::resetAxis(){
    Axis a;
    axis=a;
}
void QGraphItemAbstract::atributeAxis(Axis atrib){
    axis=atrib;
}