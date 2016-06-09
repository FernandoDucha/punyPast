/* 
 * File:   LineItem.cpp
 * Author: fernando
 * 
 * Created on 4 de Maio de 2013, 15:31
 */

#include <qt5/QtCore/QDebug>
#include <qt5/QtGui/qcolor.h>

#include "LineItem.h"

LineItem::LineItem(DataPointsInt * dp) {
    if (dp) {
        thisdp = dp;
        thisrwv = NULL;
        thisdpd = NULL;
        linecolor = randomColor(0);
    } else {
        thisrwv = NULL;
        thisdpd = NULL;
        thisdp = NULL;
    }
    lineWidth = 1;
    mode = LINE;
}

LineItem::LineItem(RWVInt * rwv) {
    if (rwv) {
        thisdp = NULL;
        thisrwv = rwv;
        thisdpd = NULL;
        linecolor = randomColor(0);
    } else {
        thisdpd = NULL;
        thisdp = NULL;
        thisrwv = NULL;
    }
    lineWidth = 1;
}

LineItem::LineItem(DataPointsDouble * dpd) {
    if (dpd) {
        thisdp = NULL;
        thisdpd = dpd;
        thisrwv = NULL;
        linecolor = randomColor(0);
    } else {
        thisdpd = NULL;
        thisdp = NULL;
        thisrwv = NULL;
    }
    lineWidth = 1;
}

LineItem::LineItem() {
    thisdp = NULL;
    thisrwv = NULL;
}

void LineItem::clear() {
    if (thisdp) {
        delete thisdp;
        thisdp = new DataPointsInt();
    } else if (thisrwv) {
        delete thisrwv;
        thisrwv = new RWVInt();
    }
}

void LineItem::setThisdpd(DataPointsDouble* thisdpd) {
    if (thisdpd) {
        if (this->thisdpd) {
            delete this->thisdpd;
            this->thisdpd = thisdpd;
        } else {
            this->thisdpd = thisdpd;
        }
    } else {
        this->thisdpd = NULL;
    }
}

DataPointsDouble* LineItem::getThisdpd() const {
    return thisdpd;
}

void LineItem::setMode(MODE m) {
    switch (m) {
        case LINE:
            mode = LINE;
            break;
        case SCATTER:
            mode = SCATTER;
            break;
    }
}

QRectF LineItem::boundingRect() const {
    return QRectF(0, 0, w, h);
}

void LineItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) {
    switch (mode) {
        case LINE:
            if (thisdp) {
                painter->setRenderHint(QPainter::HighQualityAntialiasing);
                QPen t;
                t.setColor(linecolor);
                t.setWidth(lineWidth);
                painter->setPen(t);
                QLineF temp;
                double x = offset + (axis.Lx) * Xintervalsw;
                double yelement = thisdp->getElement(0);
                double y = (yelement < 0) ? (abs(yelement) * Yintervalsh + ZeroPoint) : (ZeroPoint - yelement * Yintervalsh);
                temp.setP1(QPointF(x, y));

                for (unsigned int i = 1; i < thisdp->getNpoints(); i++) {
                    x = offset + (axis.Lx + i) * Xintervalsw;
                    yelement = thisdp->getElement(i);
                    y = (yelement < 0) ? (abs(yelement) * Yintervalsh + ZeroPoint) : (ZeroPoint - yelement * Yintervalsh);
                    temp.setP2(QPointF(x, y));
                    painter->drawLine(temp);
                    temp.setP1(temp.p2());
                }
            } else if (thisrwv) {
                QPen t;
                t.setColor(linecolor);
                t.setWidth(lineWidth);
                painter->setPen(t);
                QLineF temp;
                double x = offset + (axis.Lx) * Xintervalsw;
                double yelement = thisrwv->getElement(0);
                double y = (yelement < 0) ? (abs(yelement) * Yintervalsh + ZeroPoint) : (ZeroPoint - yelement * Yintervalsh);
                temp.setP1(QPointF(x, y));

                for (unsigned int i = 1; i < thisrwv->getSize(); i++) {
                    x = offset + (axis.Lx + i) * Xintervalsw;
                    yelement = thisrwv->getElement(i);
                    y = (yelement < 0) ? (abs(yelement) * Yintervalsh + ZeroPoint) : (ZeroPoint - yelement * Yintervalsh);
                    temp.setP2(QPointF(x, y));
                    painter->drawLine(temp);
                    temp.setP1(temp.p2());
                }
            }
            break;
        case SCATTER:
            if (thisdpd) {
                ZeroPoint=h-offset;
                painter->setRenderHint(QPainter::HighQualityAntialiasing);
                QPen t;
                double radius=1;
                t.setColor(Qt::red);
                t.setWidth(lineWidth);
                painter->setPen(t);
                double x = offset + (axis.Lx) * Xintervalsw;
                double yelement = (thisdpd->getElement(0)-thisdpd->getMin())/(axis.y);
                double y = ZeroPoint - yelement * Yintervalsh;
                painter->drawEllipse(QPointF(x,y),radius,radius);
                qDebug()<<x<<"--"<<y;
                for (unsigned int i = 1; i < thisdpd->getNpoints(); i++) {
                    x = offset + log(i+1)*Xintervalsw;
                    yelement = (thisdpd->getElement(i)-thisdpd->getMin())/(axis.y);;
                    y = ZeroPoint - yelement * Yintervalsh;
                    painter->drawEllipse(QPointF(x,y),radius,radius);
                    cout<<x<<","<<y<<"--"<<log(i+1)<<","<<thisdpd->getElement(i)<<endl;                    
                  
                } 
            }
            break;
    }
}

LineItem::~LineItem() {
    // delete thisdp;
}

Axis LineItem::limits() {
    if (thisdp) {
        return Axis(0, thisdp->getNpoints(), thisdp->getMin(), thisdp->getMax());
    } else {
        return Axis(0, thisrwv->getSize(), thisrwv->GetMin(), thisrwv->GetMax());
    }
}

RWVInt* LineItem::getThisrwv() const {
    return thisrwv;
}

DataPointsInt* LineItem::getThisdp() const {
    return thisdp;
}

void LineItem::setLineWidth(float lineWidth) {
    this->lineWidth = lineWidth;
}

float LineItem::getLineWidth() const {
    return lineWidth;
}

void LineItem::setThisrwv(RWVInt* thisrwv) {
    if (thisrwv) {
        if (this->thisrwv) {
            delete this->thisrwv;
            this->thisrwv = thisrwv;
        } else {
            this->thisrwv = thisrwv;
        }
    } else {
        this->thisrwv = NULL;
    }

}

void LineItem::setThisdp(DataPointsInt* thisdp) {
    if (thisdp) {
        if (this->thisdp) {
            delete this->thisdp;
            this->thisdp = thisdp;
        } else {
            this->thisdp = thisdp;
        }
    } else {
        this->thisdp = NULL;
    }
}
