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
        sprintf(buffer,"%g|%g",rx(),ry());
        std::string ret(buffer);
        return ret;
    }

    QPollarF & operator=(QPollarF rhs) {
        theta = rhs.getTheta();
        rho = rhs.getRho();
        setX(rhs.rx());
        setY(rhs.ry());
        return *this;
    }

    QPollarF & operator+=(QPollarF & rhs) {
        setX(rx() + rhs.rx());
        setY(ry() + rhs.ry());
        rho = (sqrt(pow(rx(), 2) + pow(ry(), 2)));
        theta = (atan(ry() / rx()));
        return *this;
    }

    double distQPollarF(QPollarF & rhs) {
        return sqrt(pow(rx() - rhs.rx(), 2) + pow(ry() - rhs.ry(), 2));
    }

    bool operator<(QPollarF & rhs) {
        if (rhs.rx() != rx()) {
            bool ret = rhs.rx() - rx() > 0 ? false : true;
            return ret;
        } else {
            bool ret = rhs.ry() - ry() > 0 ? false : true;
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
        if (rhs.rx() != lhs.rx()) {
            bool ret = rhs.rx() - lhs.rx() > 0 ? false : true;
            return ret;
        } else {
            bool ret = rhs.ry() - lhs.ry() > 0 ? false : true;
            return ret;
        }
    }
};

inline void sumQPollarF(QPollarF & A, QPollarF & B, QPollarF & C) {
    C.setX(A.rx() + B.rx());
    C.setY(A.ry() + B.ry());
    C.setRho(sqrt(pow(C.rx(), 2) + pow(C.ry(), 2)));
    C.setTheta(atan(C.ry() / C.rx()));
}

inline void subQPollarF(QPollarF & A, QPollarF & B, QPollarF & C) {
    C.setX(A.rx() - B.rx());
    C.setY(A.ry() - B.ry());
    C.setRho(sqrt(pow(C.rx(), 2) + pow(C.ry(), 2)));
    C.setTheta(atan(C.ry() / C.rx()));
}
#endif	/* QPOLLARF_H */

