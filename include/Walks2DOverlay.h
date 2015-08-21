/* 
 * File:   Walks2DOverlay.h
 * Author: fordem
 *
 * Created on February 9, 2015, 11:56 PM
 */

#ifndef WALKS2DOVERLAY_H
#define	WALKS2DOVERLAY_H
#include <QWidget>
#include <QGridLayout>
#include <QTextEdit>
#include <QLabel>
#include <QDebug>
#include <QSpinBox>
#include <QPushButton>
#include <QPalette>
#include "MemoryRandomWalk.h"
#include <QTimer>

class Walks2DOverlay : public QWidget {
    Q_OBJECT
public:
    Walks2DOverlay(QWidget * Parent);
    virtual ~Walks2DOverlay();
    void setMemoryRW(MemoryRandomWalk *);
public slots:
    void point(QPollarF * p, int n,double);
    void plot();
    void runPushed();
    void stopPushed();
private:
    QGridLayout* thisLayout;
    QLabel * LblDisc;
    QSpinBox * Disc;
    QLabel * LblMaxTime;
    QDoubleSpinBox* MaxTime;
    QPushButton * Run;
    QPushButton * Stop;
    QPushButton * Plot;
    QLabel * actualSize;
    QLabel * Adepth,* Tspent;
    MemoryRandomWalk * thismemrw;
    QPollarF * data;
    int nData;
signals:
    void plotItem(IRWItem<QPollarF>*);
};

inline void Walks2DOverlay::point(QPollarF* p, int n, double t) {
    for (int i = 0; i < n; i++) {
        data[i] = p[i];
    }
    nData = n;
    Adepth->setText(QString::number(n));
    Tspent->setText(QString::number(t));    
}

inline void Walks2DOverlay::setMemoryRW(MemoryRandomWalk* memRw) {
    thismemrw = memRw;
}

inline Walks2DOverlay::Walks2DOverlay(QWidget* Parent) : QWidget(Parent) {
    data = NULL;
    QPalette pal;
    pal.setBrush(QPalette::Window, QColor(255, 0, 0, 128));
    this->setAutoFillBackground(true);
    this->resize(400, 400);
    this->setPalette(pal);
    thisLayout = new QGridLayout(this);
    LblDisc = new QLabel(this);
    LblDisc->setText("Angle Disc.:");
    Disc = new QSpinBox(this);
    Disc->setButtonSymbols(QAbstractSpinBox::NoButtons);
    Disc->setMaximum(360 * 16);
    Disc->setMinimum(4);
    Disc->setValue(4);
    LblMaxTime = new QLabel(this);
    LblMaxTime->setText("Available Time(s):");
    MaxTime = new QDoubleSpinBox(this);
    MaxTime->setButtonSymbols(QAbstractSpinBox::NoButtons);
    MaxTime->setMaximum(36000000);
    MaxTime->setMinimum(1);
    MaxTime->setValue(1);
    Run = new QPushButton(this);
    Run->setText("Run!");
    Plot = new QPushButton(this);
    Plot->setText("Plot!");
    Stop = new QPushButton(this);
    Stop->setText("Stop!");
    Adepth = new QLabel("");
    Tspent = new QLabel("");
    thisLayout->addWidget(LblDisc, 0, 0, Qt::AlignCenter | Qt::AlignHCenter);
    thisLayout->addWidget(Disc, 0, 1, Qt::AlignCenter | Qt::AlignHCenter);
    thisLayout->addWidget(LblMaxTime, 1, 0, Qt::AlignCenter | Qt::AlignHCenter);
    thisLayout->addWidget(MaxTime, 1, 1, Qt::AlignCenter | Qt::AlignHCenter);
    thisLayout->addWidget(Run, 2, 0, 1, 2, Qt::AlignCenter | Qt::AlignHCenter);
    thisLayout->addWidget(Plot, 3, 0, 1, 2, Qt::AlignCenter | Qt::AlignHCenter);
    thisLayout->addWidget(Stop, 4, 0, 1, 2, Qt::AlignCenter | Qt::AlignHCenter);
    thisLayout->addWidget(Adepth, 5, 0, 1, 1, Qt::AlignCenter | Qt::AlignHCenter);
    thisLayout->addWidget(Tspent, 5, 1, 1, 1, Qt::AlignCenter | Qt::AlignHCenter);
    connect(Run, SIGNAL(released()), this, SLOT(runPushed()));
    connect(Plot, SIGNAL(released()), this, SLOT(plot()));
    connect(Stop, SIGNAL(released()), this, SLOT(stopPushed()));
    Stop->setEnabled(false);
}

inline void Walks2DOverlay::plot() {
    if (data) {
        IRWItem<QPollarF> * emitting = new PollarRwDp();
        emitting->receiveData(data, nData);
        emit plotItem(emitting);
    }
}

inline Walks2DOverlay::~Walks2DOverlay() {

}

inline void Walks2DOverlay::runPushed() {
    MemoryRandomWalk * aux = new MemoryRandomWalk(*thismemrw);
    delete thismemrw;
    thismemrw = aux;
    thismemrw->generatePointsDiscrete(Disc->value());
    if (data == NULL) {
        data = new QPollarF[thismemrw->getWalksSize()];
    } else {
        delete [] data;
        data = new QPollarF[thismemrw->getWalksSize()];
    }
    connect(thismemrw, SIGNAL(point(QPollarF*, int, double)), this, SLOT(point(QPollarF*, int, double)));
    thismemrw->setTime(MaxTime->value()*1000);
    thismemrw->start();
    Run->setEnabled(false);
    Stop->setEnabled(true);
}

inline void Walks2DOverlay::stopPushed() {
    thismemrw->terminate();
    Run->setEnabled(true);
    Stop->setEnabled(false);
}
#endif	/* WALKS2DOVERLAY_H */

