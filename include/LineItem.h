/* 
 * File:   LineItem.h
 * Author: fernando
 *
 * Created on 4 de Maio de 2013, 15:31
 */

#ifndef LINEITEM_H
#define	LINEITEM_H
#include "QGraphItemAbstract.h"
#include "DPBase.h"
#include "RWVBase.h"
#include <QPainterPath>
class LineItem : public QGraphItemAbstract{
public:
    enum MODE{LINE=0,SCATTER=1};
    LineItem(DataPointsInt * dp);
    LineItem(RWVInt * rwv);
    LineItem(DataPointsDouble * dpd);

    LineItem(const LineItem& orig);
    LineItem();
    virtual QRectF boundingRect () const;
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );
    virtual ~LineItem();
    Axis  limits();
    RWVInt* getThisrwv() const;
    DataPointsInt* getThisdp() const;
    void setLineWidth(float lineWidth);
    float getLineWidth() const;
    void setThisrwv(RWVInt* thisrwv);
    void setThisdp(DataPointsInt* thisdp);
    void setMode(MODE m);
    void clear();
    void setThisdpd(DataPointsDouble* thisdpd);
    DataPointsDouble* getThisdpd() const;
private:
    DataPointsInt * thisdp;
    RWVInt * thisrwv;
    DataPointsDouble * thisdpd;
    QColor linecolor;
    float lineWidth;
    MODE mode;
};

#endif	/* LINEITEM_H */

