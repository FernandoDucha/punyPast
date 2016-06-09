/* 
 * File:   GraphMagnifier.cpp
 * Author: fordem
 * 
 * Created on July 14, 2013, 7:37 PM
 */

#include <qt5/QtGui/qevent.h>
#include <qt5/QtCore/qdebug.h>

#include "GraphMagnifier.h"

GraphMagnifier::GraphMagnifier(QwtPlotCanvas * canvas) : QwtPlotMagnifier(canvas) {
    deltaold = 0;
    this->setMouseButton(Qt::NoButton);
   /// this->setWheelFactor(-this->wheelFactor());
    this->setZoomInKey(Qt::Key_Equal,Qt::ControlModifier);
    this->setZoomOutKey(Qt::Key_Minus,Qt::ControlModifier);
    
    scale = 1;
    scalecount = 1;
}

GraphMagnifier::~GraphMagnifier() {
}

//void GraphMagnifier::widgetMouseMoveEvent(QMouseEvent* evnt) {
//
//}

//void GraphMagnifier::widgetKeyPressEvent(QKeyEvent * event) {
////     qDebug()<<hex<<event->key()<<"---"<<event->modifiers();
////     qDebug()<<hex<<Qt::Key_0<<"---"<<Qt::ControlModifier;
//    if ((event->key() == Qt::Key_0)&&(event->modifiers().testFlag(Qt::ControlModifier))) {
//        scale = 1;
//        rescale(scale);
//    } else if ((event->key() == Qt::Key_Equal)&&(event->modifiers().testFlag(Qt::ControlModifier))) {
//        scale +=(scalecount*keyFactor());
//        scalecount++;
//        scale += keyFactor();
//        rescale(scale);
//    } else if ((event->key() == Qt::Key_Minus)&&(event->modifiers().testFlag(Qt::ControlModifier))) {
//        scale -=(scalecount*keyFactor());
//        scalecount--;
//        rescale(scale);
//    }
//    qDebug()<<scale;
//}