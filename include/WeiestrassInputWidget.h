/* 
 * File:   WeiestrassInputWidget.h
 * Author: fordem
 *
 * Created on June 12, 2015, 1:26 PM
 */

#ifndef WEIESTRASSINPUTWIDGET_H
#define	WEIESTRASSINPUTWIDGET_H
#include "IInputWidget.h"
#include "LCGBinaryRandomWalk.h"
#include <QtGui>
#include <QDoubleSpinBox>

class WeiestrassInputWidget : public IInputWidget {
    Q_OBJECT
public:
    WeiestrassInputWidget(QWidget * parent);
    virtual ~WeiestrassInputWidget();

protected slots:
    void Hedit(QString);
    void bedit(QString);
    void startedit(QString);
    void endedit(QString);
    void Ledit(QString);
private:
    bool WeierstrassOK();
    LCGBinaryRandomWalk * LCGbrw;
    RNGLinearCong LCGrng;
    QLabel *lH, *lb, *lstart, *lend, *equation;
    QDoubleSpinBox *eH, *eb, *estart, *eend;
    double H, b, sX, eX;
    u_int32_t L;
signals:
    void weiestrassR(u_int32_t L, double H, double B, double start, double end);
};

#endif	/* WEIESTRASSINPUTWIDGET_H */

