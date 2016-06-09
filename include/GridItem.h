/* 
 * File:   GridItem.h
 * Author: fernando
 *
 * Created on 27 de Abril de 2013, 10:45
 */

#ifndef GRIDITEM_H
#define	GRIDITEM_H
#include "BinaryRandomWalk.h"
#include "QGraphItemAbstract.h"
#include <QDebug>
class GridItem : public QGraphItemAbstract{
    //Q_OBJECT
public:
    GridItem();
    void paint(QPainter * painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
    virtual ~GridItem();
    QRectF boundingRect()const;
    void changedScaleX(double a);
    void changedTicksX(double a);
    void changedScaleY(double a);
    void changedTicksY(double a);
    double getSX() const;
    double getTX() const;
    double getSY() const;
    double getTY() const;
    void setGridOn(bool GridOn);
    bool isGridOn() const;
protected:
    QPen gridpen;
    Qt::PenStyle p_style;
    QBrush penbrush;
    QPen itempen;
    Qt::PenStyle i_style;
    QBrush i_penbrush;
    QFont * textFont;
    QBrush background;
    bool GridOn;
};

#endif	/* GRIDITEM_H */

