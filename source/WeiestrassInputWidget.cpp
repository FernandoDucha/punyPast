/* 
 * File:   WeiestrassInputWidget.cpp
 * Author: fordem
 * 
 * Created on June 12, 2015, 1:26 PM
 */

#include <qt5/QtWidgets/qspinbox.h>

#include "WeiestrassInputWidget.h"

WeiestrassInputWidget::WeiestrassInputWidget(QWidget * parent) : IInputWidget(parent) {
    qGrdLay = new QGridLayout(this);
    H = 0.5;
    b = 2;
    sX = -1;
    eX = 1;
    L = 5000;
    //    lNWalks = new QLabel(this);
    //    lNWalks->setText("Only One!");
    //    lNWalks->setContentsMargins(0, 0, 0, 0);
    //    qGrdLay->addWidget(lNWalks, 0, 0, 1, 1, Qt::AlignCenter | Qt::AlignBottom);


    NWalks = new QLineEdit();
    NWalks->setValidator(new QIntValidator(1, pow(2, 30)));
    NWalks->setContentsMargins(0, 0, 0, 0);
    //    qGrdLay->addWidget(NWalks, 0, 1, 1, 1, Qt::AlignCenter | Qt::AlignBottom);
    //    NWalks->setDisabled(true);
    NWalks->setText("1");

    lWSize = new QLabel(this);
    lWSize->setText("Length:");
    lWSize->setContentsMargins(0, 0, 0, 0);
    qGrdLay->addWidget(lWSize, 0, 0, 1, 1, Qt::AlignCenter | Qt::AlignTop);

    WSize = new QLineEdit(this);
    WSize->setValidator(new QIntValidator(0, pow(2, 30)));
    WSize->setContentsMargins(0, 0, 0, 0);
    qGrdLay->addWidget(WSize, 0, 2, 1, 1, Qt::AlignCenter | Qt::AlignTop);
    //    WSize->setDisabled(true);

    lH = new QLabel(this);
    lH->setText("H:");
    lH->setContentsMargins(0, 0, 0, 0);
    qGrdLay->addWidget(lH, 1, 0, 1, 1, Qt::AlignCenter | Qt::AlignTop);

    eH = new QDoubleSpinBox(this);
    eH->setContentsMargins(0, 0, 0, 0);
    eH->setMaximum(1 - pow(10, -6));
    eH->setMinimum(pow(10, -6));
    eH->setSingleStep(pow(10, -4));
    eH->setButtonSymbols(QAbstractSpinBox::NoButtons);
    eH->setDecimals(6);
    qGrdLay->addWidget(eH, 1, 2, 1, 1, Qt::AlignCenter | Qt::AlignTop);


    lb = new QLabel(this);
    lb->setText("b:");
    lb->setContentsMargins(0, 0, 0, 0);
    qGrdLay->addWidget(lb, 2, 0, 1, 1, Qt::AlignCenter | Qt::AlignTop);

    eb = new QDoubleSpinBox(this);
    eb->setContentsMargins(0, 0, 0, 0);
    eb->setMaximum(pow(2, 30));
    eb->setMinimum(1 + pow(10, -6));
    eb->setSingleStep(pow(10, -4));
    eb->setButtonSymbols(QAbstractSpinBox::NoButtons);
    eb->setDecimals(6);
    qGrdLay->addWidget(eb, 2, 2, 1, 1, Qt::AlignCenter | Qt::AlignTop);


    lstart = new QLabel(this);
    lstart->setText("X start:");
    lstart->setContentsMargins(0, 0, 0, 0);
    qGrdLay->addWidget(lstart, 3, 0, 1, 1, Qt::AlignCenter | Qt::AlignTop);

    estart = new QDoubleSpinBox(this);
    estart->setContentsMargins(0, 0, 0, 0);
    estart->setMaximum(pow(2, 30));
    estart->setMinimum(-pow(2, 30));
    estart->setSingleStep(pow(10, -4));
    estart->setButtonSymbols(QAbstractSpinBox::NoButtons);
    estart->setDecimals(6);
    qGrdLay->addWidget(estart, 3, 2, 1, 1, Qt::AlignCenter | Qt::AlignTop);


    lend = new QLabel(this);
    lend->setText("X end:");
    lend->setContentsMargins(0, 0, 0, 0);

    qGrdLay->addWidget(lend, 4, 0, 1, 1, Qt::AlignCenter | Qt::AlignTop);

    eend = new QDoubleSpinBox(this);
    eend->setContentsMargins(0, 0, 0, 0);
    eend->setMaximum(pow(2, 30));
    eend->setMinimum(-pow(2, 30));
    eend->setSingleStep(pow(10, -4));
    eend->setButtonSymbols(QAbstractSpinBox::NoButtons);
    eend->setDecimals(6);
    qGrdLay->addWidget(eend, 4, 2, 1, 1, Qt::AlignCenter | Qt::AlignTop);

    QPixmap p("images/weiestrass.png");
    equation = new QLabel(this);
    equation->setPixmap(p.scaled(250, 70));
    equation->setMask(p.mask());
    qGrdLay->addWidget(equation, 0, 3, 4, 4, Qt::AlignCenter | Qt::AlignHCenter);
    eb->setValue(2);
    eH->setValue(0.5);
    estart->setValue(-1);
    eend->setValue(1);
    connect(WSize, SIGNAL(textChanged(QString)), this, SLOT(Ledit(QString)));
    connect(eH, SIGNAL(valueChanged(QString)), this, SLOT(Hedit(QString)));
    connect(eb, SIGNAL(valueChanged(QString)), this, SLOT(bedit(QString)));
    connect(eend, SIGNAL(valueChanged(QString)), this, SLOT(endedit(QString)));
    connect(estart, SIGNAL(valueChanged(QString)), this, SLOT(startedit(QString)));
}

void WeiestrassInputWidget::Hedit(QString hin) {
    H = hin.toDouble();
    if (WeierstrassOK()) {
        LCGbrw = new LCGBinaryRandomWalk(&this->LCGrng, 1, 1);
        emit createdRWK(LCGbrw);
        emit weiestrassR(L, H, b, sX, eX);
    }
}

void WeiestrassInputWidget::bedit(QString bin) {
    b = bin.toDouble();
    if (WeierstrassOK()) {
        LCGbrw = new LCGBinaryRandomWalk(&this->LCGrng, 1, 1);
        emit createdRWK(LCGbrw);
        emit weiestrassR(L, H, b, sX, eX);
    }
}

void WeiestrassInputWidget::endedit(QString ein) {
    eX = ein.toDouble();
    if (WeierstrassOK()) {
        LCGbrw = new LCGBinaryRandomWalk(&this->LCGrng, 1, 1);
        emit createdRWK(LCGbrw);
        emit weiestrassR(L, H, b, sX, eX);
    }
}

void WeiestrassInputWidget::startedit(QString sin) {
    sX = sin.toDouble();
    if (WeierstrassOK()) {
        LCGbrw = new LCGBinaryRandomWalk(&this->LCGrng, 1, 1);
        emit createdRWK(LCGbrw);
        emit weiestrassR(L, H, b, sX, eX);
    }
}

void WeiestrassInputWidget::Ledit(QString lin) {
    L = lin.toInt();
    if (WeierstrassOK()) {
        LCGbrw = new LCGBinaryRandomWalk(&this->LCGrng, 1, 1);
        emit createdRWK(LCGbrw);
        emit weiestrassR(L, H, b, sX, eX);
    }
}

bool WeiestrassInputWidget::WeierstrassOK() {
    return ((L != 0)&&(sX != eX)&&(sX<eX));
}

WeiestrassInputWidget::~WeiestrassInputWidget() {
}

