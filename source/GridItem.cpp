/* 
 * File:   GridItem.cpp
 * Author: fernando
 * 
 * Created on 27 de Abril de 2013, 10:45
 */

#include "GridItem.h"

GridItem::GridItem() {
    textFont = new QFont("Arial",8,QFont::Normal,false);
    background = QBrush(Qt::white);
    p_style=Qt::DashDotDotLine;
    gridpen.setStyle(p_style);
    gridpen.setWidth(1);
    gridpen.setColor(QColor(125,125,125));
    penbrush=QBrush(QColor(100,100,100));
    i_style=Qt::SolidLine;
    itempen.setStyle(p_style);
    itempen.setWidth(1);
    i_penbrush=QBrush(QColor(0,0,0));
    rW=0;
    rH=0;
    w=0;
    h=0;
    cw=0;
    ch=0;
    sX=10;
    tX=10;
    sY=5;
    tY=10;
    GridOn=true;
}
QRectF GridItem::boundingRect() const
 {
     return QRectF(0,0,w, h);
 }
void GridItem::paint(QPainter * painter, const QStyleOptionGraphicsItem *option,QWidget *widget){
        
        if(!cw){
            cw=widget->rect().width();
        }
        if(!ch){
            ch=widget->rect().height();
        }
        painter->setFont(*textFont);
        painter->fillRect(widget->rect(),background);
        double w1=0,h1=0;
        offset=30;
        w1=offset;
        
        if(widget->rect().width()!=w){
            if(w){                
                rW=(double)(cw/widget->rect().width());
            }else{
                rW=1;
            }
        }
        if(widget->rect().height()!=h){
            if(h){                
                rH=(double)(ch/widget->rect().height());
            }else{
                rH=1;
            }
        }
        w=widget->rect().width();
        h=widget->rect().height();
        h1=h-offset;
        painter->drawLine(QLineF(QPointF(0,h1),QPointF(w,h1)));
        painter->drawLine(QLineF(QPointF(offset,0),QPointF(offset,h)));
        
        w1=w-offset;
        h1=h-offset;
        int k=1,k1=1;

     
        Xintervalsw=w1/axis.x;
        double stepx=rW*sX*Xintervalsw;
        double ticksw=tX*stepx;
        for(double i=0;i<w;i+=Xintervalsw){
            QLineF a;
            if(i>=k*(ticksw)){
                a.setPoints(QPointF(offset+i,h1),QPointF(offset+i,h1-offset/5));
                QRectF text;
                text.setX(offset+i-ticksw/2);
                text.setY(h1);
                text.setWidth(ticksw);
                text.setHeight(20);
                QTextOption fmt(Qt::AlignTop|Qt::AlignCenter);
                double t = i/Xintervalsw+axis.Lx;
                painter->drawText(text,QString::number(t,10,1),fmt);                
                k++;
                k1++;
                painter->drawLine(a);
            }else if(i>=k1*stepx){
                a.setPoints(QPointF(i+offset,h1),QPointF(i+offset,h1-offset/10));
                painter->drawLine(a);
                k1++;
            }            
        }
        k=1;k1=1;
        Yintervalsh=h1/axis.y;
        ZeroPoint=axis.Hy*Yintervalsh;
        double stepy=rH*sY*Yintervalsh;
        double ticksh=tY*stepy;
        for(double i=0;i<h1;i+=Yintervalsh){
            QLineF a;
            if(i>=(k*ticksh)){
                a.setPoints(QPointF(offset,i),QPointF(offset+offset/5,i));
                QRectF text;
                text.setX(0);
                text.setY(i-ticksh/2);
                text.setWidth(offset);
                QTextOption fmt(Qt::AlignHCenter|Qt::AlignCenter);
                text.setHeight(ticksh);
                QString str = QString::number(axis.Hy-i/Yintervalsh,10,1);
                painter->drawText(text,str,fmt);                
                k++;
                k1++;
                painter->drawLine(a);
            }else if(i>=k1*stepy){
                a.setPoints(QPointF(offset,i),QPointF(offset+offset/10,i));
                painter->drawLine(a);
                k1++;
            }
        }
        if(isGridOn()){
            painter->setPen(gridpen);
            k=1;
            for(float i=0;i<axis.y;i++){
                QLineF a;
                if(i>=k*sY*tY){
                    a.setPoints(QPointF(offset,i*Yintervalsh),QPointF(w,i*Yintervalsh));
                    painter->drawLine(a);
                    k++;
                }
            }
            k=1;
            for(double i=0;i<w;i+=Xintervalsw){
                QLineF a;
                if(i>=k*ticksw){
                    a.setPoints(QPointF(offset+i,0),QPointF(offset+i,h1));                                
                    painter->drawLine(a);
                    k++;
                }           
            }
        }
       //exit(0);
}

GridItem::~GridItem() {
}
void GridItem::changedScaleX(double a){
    sX=a;
    update(boundingRect());
}
void GridItem::changedTicksX(double a){
    tX=a;
    update(boundingRect());
}
void GridItem::changedScaleY(double a){
    sY=a;
    update(boundingRect());
    
}
void GridItem::changedTicksY(double a){
    tY=a;
    update(boundingRect());
}
double GridItem::getSX() const {
    return sX;
}

double GridItem::getTX() const {
    return tX;
}

double GridItem::getSY() const {
    return sY;
}

double GridItem::getTY() const {
    return tY;
}
void GridItem::setGridOn(bool GridOn) {
    this->GridOn = GridOn;
    update(boundingRect());
}

bool GridItem::isGridOn() const {
    return GridOn;
}