/* 
 * File:   LCGRngWidget.h
 * Author: fordem
 *
 * Created on February 26, 2015, 11:20 PM
 */

#ifndef LCGRNGWIDGET_H
#define	LCGRNGWIDGET_H

#include "IInputWidget.h"
#include "LCGBinaryRandomWalk.h"
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>
#include <stdint.h>
class LCGRngWidget : public IInputWidget {
    Q_OBJECT
public:
    LCGRngWidget(QWidget * parent);
    virtual ~LCGRngWidget();
protected slots:
    void attemptToCreateRWK();
    void enableNwWsEditing(QString s);
private:
    LCGBinaryRandomWalk * LCGbrw;
    RNGLinearCong  LCGrng;
    QLabel * lSeed,* lConfig,* lMulti,* lInc,* lModulus;
    QLineEdit * seed,* multi,* inc,* modulus;
    QWidget * LCGconfig;
    QGridLayout * qGridConfig;
    
};

#endif	/* LCGRNGWIDGET_H */

