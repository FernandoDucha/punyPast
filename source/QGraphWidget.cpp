/* 
 * File:   QGLGraphWidget.cpp
 * Author: fernando
 * 
 * Created on 24 de Abril de 2013, 14:42
 */

#include "QGraphWidget.h"


 QGraphWidget::QGraphWidget(GraphScene *scene)
     :QGraphicsView(scene)
 {
     elapsed = 0;     
     setAlignment(Qt::AlignTop|Qt::AlignLeft);
     //setFixedSize(200, 200);
     intervals=0;
 }
// void QGraphWidget::paintEvent(QPaintEvent *event)
// {
//     QPainter painter;
//     painter.begin(this);
//     helper->paint(&painter,event);
//     painter.end();
// }
