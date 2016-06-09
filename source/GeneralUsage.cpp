#include <qt5/QtWidgets/qapplication.h>

#include "GeneralUsage.h"
#include "GraphUi.h"
QColor randomColor(unsigned long int seed){
    if(seed>0)
        qsrand(seed);
    return QColor(qrand()%256,qrand()%256,qrand()%256);
}
Axis & operator+(Axis & a, Axis & b){
    Axis * ret = new Axis();
    if(a.Hx>b.Hx){
        ret->Hx=a.Hx;
    }else{
        ret->Hx=b.Hx;
    }
    if(a.Ly>b.Ly){
        ret->Ly=b.Ly;
    }else{
        ret->Ly=a.Ly;
    }
    ret->x=ret->Hx-ret->Lx;
    ret->y=ret->Hy-ret->Ly;
    return *ret;
}
Axis & Axis::operator=(Axis & rhs){
    this->x=rhs.x;
    this->y=rhs.y;
    this->Hx=rhs.Hx;
    this->Lx=rhs.Lx;
    this->Hy=rhs.Hy;
    this->Ly=rhs.Ly;
    
    return *this;
}
Axis & Axis::operator+=(Axis & rhs){
    if(this->Hx<rhs.Hx){
        this->Hx=rhs.Hx;
    }
    if(this->Lx>rhs.Lx){
        this->Lx=rhs.Lx;
    }
    if(this->Hy<rhs.Hy){
        this->Hy=rhs.Hy;
    }
    if(this->Ly>rhs.Ly){
        this->Ly=rhs.Ly;
    }
    this->x=this->Hx-this->Lx;
    this->y=this->Hy-this->Ly;    
    return *this;

}