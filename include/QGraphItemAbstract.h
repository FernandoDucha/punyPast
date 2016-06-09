/* 
 * File:   QGraphItemAbstract.h
 * Author: fernando
 *
 * Created on 4 de Maio de 2013, 10:18
 */

#ifndef QGRAPHITEMABSTRACT_H
#define	QGRAPHITEMABSTRACT_H
#include <qt5/QtWidgets/QGraphicsItem>
#include <qt5/QtWidgets/QWidget>
#include <qt5/QtGui/QPainter>
#include <qt5/QtWidgets/QStyleOptionGraphicsItem>
#include "GeneralUsage.h"
class QGraphItemAbstract: public QGraphicsItem {
public:
    QGraphItemAbstract();
    virtual QRectF boundingRect () const = 0;
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 )=0;
    virtual ~QGraphItemAbstract();
    void setAxis(Axis novo);
    void atributeAxis(Axis atrib);
    void resetAxis();
private:
protected:
    
    static double tX;
    static double sX;
    static double tY;
    static double sY;    
    static double rW;
    static double rH;
    static double w;
    static double h;
    static double cw;
    static double ch;
    static double offset;
    static double Xintervalsw;
    static double Yintervalsh;
    static Axis axis;
    static double ZeroPoint;
};

#endif	/* QGRAPHITEMABSTRACT_H */

