/* 
 * File:   GridFitting.h
 * Author: fordem
 *
 * Created on July 3, 2013, 9:06 AM
 */

#ifndef GRIDFITTING_H
#define	GRIDFITTING_H
#include "GridItem.h"
#include "DPBase.h"

class GridFitting : public QGraphItemAbstract {
public:
    QRectF boundingRect()const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    GridFitting(DataPointsDouble * x, DataPointsDouble * y);
    GridFitting(const GridFitting& orig);
    virtual ~GridFitting();
    void setGridOn(bool GridOn);
    bool isGridOn() const;
    void changedScaleX(double a);
    void changedTicksX(double a);
    void changedScaleY(double a);
    void changedTicksY(double a);
    double getSX() const;
    double getTX() const;
    double getSY() const;
    double getTY() const;
private:
    DataPointsDouble * xlabel, * ylabel;
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

#endif	/* GRIDFITTING_H */

