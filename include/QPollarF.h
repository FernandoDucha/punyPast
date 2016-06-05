/* 
 * File:   QPollarF.h
 * Author: fordem
 *
 * Created on March 18, 2015, 3:46 PM
 */

#ifndef QPOLLARF_H
#define	QPOLLARF_H
#include <QPointF>
#include <cmath>
#include <string>
#include <stdio.h>

class QPollarF : public QPointF {
public:

    QPollarF() {
        rho = 0;
        theta = 0;
        setX(rho * cos(theta));
        setY(rho * sin(theta));
    }

    QPollarF(double r, double t) {
        rho = r;
        theta = t;
        setX(rho * cos(theta));
        setY(rho * sin(theta));
    }

    float getRho() {
        return rho;
    }

    float getTheta() {
        return theta;
    }

    void setRho(double r) {
        rho = r;
    }

    void setTheta(double t) {
        theta = t;
    }

    virtual ~QPollarF() {
    }

    std::string toString() {
        
//        QString ret;
        char buffer[50];
        sprintf(buffer,"%g|%g",x(),y());
        std::string ret(buffer);
        return ret;
    }

    QPollarF & operator=(QPollarF rhs) {
        theta = rhs.getTheta();
        rho = rhs.getRho();
        setX(rhs.x());
        setY(rhs.y());
        return *this;
    }

    QPollarF & operator+=(QPollarF & rhs) {
        setX(x() + rhs.x());
        setY(y() + rhs.y());
        rho = (sqrt(pow(x(), 2) + pow(y(), 2)));
        theta = (atan(y() / x()));
        return *this;
    }

    double distQPollarF(QPollarF & rhs) {
        return sqrt(pow(x() - rhs.x(), 2) + pow(y() - rhs.y(), 2));
    }
    bool operator!=(QPollarF & rhs){
        if(x()!=rhs.x()||y()!=rhs.y()){
            return true;
        }else{
            return false;
        }
    }
    bool operator<(QPollarF & rhs) {
        if (rhs.x() != x()) {
            bool ret = rhs.x() - x() > 0 ? false : true;
            return ret;
        } else {
            bool ret = rhs.y() - y() > 0 ? false : true;
            return ret;
        }
    }

    void setIndice(int ind) {
        indice = ind;
    }

    int getIndice() {
        return indice;
    }
private:
    double rho, theta;
    int indice;
};

struct PollarFComp {

    bool operator() ( QPollarF  lhs,   QPollarF rhs) {
        if (rhs.x() != lhs.x()) {
            bool ret = rhs.x() - lhs.x() > 0 ? false : true;
            return ret;
        } else {
            bool ret = rhs.y() - lhs.y() > 0 ? false : true;
            return ret;
        }
    }
};

inline void sumQPollarF(QPollarF & A, QPollarF & B, QPollarF & C) {
    C.setX(A.x() + B.x());
    C.setY(A.y() + B.y());
    C.setRho(sqrt(pow(C.x(), 2) + pow(C.y(), 2)));
    C.setTheta(atan(C.y() / C.x()));
}

inline void subQPollarF(QPollarF & A, QPollarF & B, QPollarF & C) {
    C.setX(A.x() - B.x());
    C.setY(A.y() - B.y());
    C.setRho(sqrt(pow(C.x(), 2) + pow(C.y(), 2)));
    C.setTheta(atan(C.y() / C.x()));
}
#endif	/* QPOLLARF_H */

