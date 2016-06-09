/* 
 * File:   QGLGraphWidget.h
 * Author: fernando
 *
 * Created on 24 de Abril de 2013, 14:42
 */

#ifndef QGLGRAPHWIDGET_H
#define	QGLGRAPHWIDGET_H
#include <qt5/QtWidgets/QGraphicsView>
#include <qt5/QtWidgets/QWidget>

#include "GraphScene.h"
#include <qt5/QtCore/QDebug>
#include "QGraphItemAbstract.h"
class QGraphWidget : public QGraphicsView
 {
     Q_OBJECT

 public:
     QGraphWidget(GraphScene *scene);
 protected:
     //void paintEvent(QPaintEvent *event);
 private:
     int elapsed;
     int intervals;
 };

#endif	/* QGLGRAPHWIDGET_H */

