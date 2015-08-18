/* 
 * File:   DFAInputGui.cpp
 * Author: fordem
 * 
 * Created on June 17, 2015, 8:03 PM
 */




#include <qt5/QtWidgets/qpushbutton.h>
#include <qt5/QtCore/qnamespace.h>
#include <qt5/QtCore/qstring.h>
#include <qt5/QtWidgets/qcheckbox.h>
#include <QDebug>
#include "DFAInputGui.h"

DFAInputGui::DFAInputGui(IRWItem<double>* X, IRWItem<double> * Y, QWidget * parent) : thisX(X), thisY(Y), QDialog(parent) {
    thisDFA = NULL;
    interval = NULL;
    this->configureGui();
    thisTimer = new QTimer();
    thisTimer->setInterval(1000);
    connect(pRun, SIGNAL(released()), this, SLOT(attemptToRun()));
    connect(thisTimer, SIGNAL(timeout()), this, SLOT(processRunning()));
    connect(cFrctDim, SIGNAL(stateChanged(int)), this, SLOT(changeFromToFrctDim(int)));
    thisDEngine = new FittingDrawingEngine<double>(thisPlot);

}

DFAInputGui::DFAInputGui(IRWItem<double>* Y, double start, double end, u_int32_t length, QWidget * parent) : thisY(Y), QDialog(parent) {
    interval = new RWDpIntervalBuilder<double>();
    thisX = interval->produceLinearInterval(start, end, (end - start) / length);
    //    qDebug()<<thisY->getNpoints();
    //    qDebug()<<thisX->getNpoints();
    thisDFA = NULL;
    interval = NULL;
    this->configureGui();
    thisTimer = new QTimer();
    thisTimer->setInterval(1000);
    connect(pRun, SIGNAL(released()), this, SLOT(attemptToRun()));
    connect(thisTimer, SIGNAL(timeout()), this, SLOT(processRunning()));
    connect(cFrctDim, SIGNAL(stateChanged(int)), this, SLOT(changeFromToFrctDim(int)));
    thisDEngine = new FittingDrawingEngine<double>(thisPlot);
}

DFAInputGui::~DFAInputGui() {
    delete thisDEngine;
    if (interval) {
        delete thisX;
        delete interval;
    }

}

void DFAInputGui::attemptToRun() {
    u_int32_t min = eMinBox->text().toInt();
    u_int32_t max = eMaxBox->text().toInt();
    double ratio = eRatio->text().toDouble();
    if ((ratio > 1)&&(min < max)&&(max < thisY->getNpoints())) {
        if (thisDFA)
            delete thisDFA;
        thisDFA = new DFA(min, max, ratio);
        thisXtemp = new DataPointsDouble();
        thisYtemp = new DataPointsDouble();
        *thisXtemp = *thisX;
        *thisYtemp = *thisY;
        thisDFA->receiveData(thisYtemp, thisXtemp);
        actualBox = 1;
        Xtemp.clear();
        Ytemp.clear();

        thisTimer->start();
        cFrctDim->setEnabled(false);

    }

}

void DFAInputGui::configureGui() {
    grdLayOut = new QGridLayout(this);
    thisPlot = new QwtPlot(this);
    grdLayOut->addWidget(thisPlot, 0, 0, 10, 10);
    inputControls = new QWidget(this);
    inputControls->setMinimumSize(QSize(250, 150));
    inputControls->setMaximumSize(QSize(350, 200));
    grdLayOut->addWidget(inputControls, 11, 0, 1, 1);
    grdControls = new QGridLayout(inputControls);
    lMinBox = new QLabel(inputControls);
    lMinBox->setContentsMargins(0, 0, 0, 0);
    lMinBox->setText("Min Box Size:");
    grdControls->addWidget(lMinBox, 0, 0, 1, 1);
    lMaxBox = new QLabel(inputControls);
    lMaxBox->setContentsMargins(0, 0, 0, 0);

    lMaxBox->setText("Max Box Size:");
    grdControls->addWidget(lMaxBox, 1, 0, 1, 1);
    lRatio = new QLabel(inputControls);
    lRatio->setText("Ratio:");
    lRatio->setContentsMargins(0, 0, 0, 0);

    grdControls->addWidget(lRatio, 2, 0, 1, 1);
    eMinBox = new QLineEdit(inputControls);
    eMinBox->setContentsMargins(0, 0, 0, 0);

    grdControls->addWidget(eMinBox, 0, 1, 1, 1);
    eMaxBox = new QLineEdit(inputControls);
    eMaxBox->setContentsMargins(0, 0, 0, 0);

    grdControls->addWidget(eMaxBox, 1, 1, 1, 1);
    eRatio = new QDoubleSpinBox(inputControls);
    eRatio->setContentsMargins(0, 0, 0, 0);
    eRatio->setMaximum(20);
    eRatio->setMinimum(1);
    eRatio->setSingleStep(pow(10, -6));
    eRatio->setButtonSymbols(QAbstractSpinBox::NoButtons);
    eRatio->setDecimals(6);
    grdControls->addWidget(eRatio, 2, 1, 1, 1);
    pRun = new QPushButton(inputControls);
    pRun->setContentsMargins(0, 0, 0, 0);
    pRun->setText("Run Analysis");
    grdControls->addWidget(pRun, 3, 0, 1, 2, Qt::AlignCenter | Qt::AlignTop);
    lFrctDim = new QLabel(inputControls);
    lFrctDim->setContentsMargins(0, 0, 0, 0);
    lFrctDim->setText("F. Dimension:");
    grdControls->addWidget(lFrctDim, 0, 3, 1, 1);
    cFrctDim = new QCheckBox(inputControls);
    cFrctDim->setContentsMargins(0, 0, 0, 0);
    grdControls->addWidget(cFrctDim, 0, 4, 1, 1);
    lProgress = new QLabel(inputControls);
    lProgress->setText("Progress:");
    lProgress->setContentsMargins(0, 0, 0, 0);
    grdControls->addWidget(lProgress, 1, 3, 1, 1);
    lProgressing = new QLabel(inputControls);
    lProgressing->setContentsMargins(0, 0, 0, 0);
    grdControls->addWidget(lProgressing, 1, 4, 1, 1, Qt::AlignCenter);
    thisPlot->setCanvasBackground(Qt::white);
}

void DFAInputGui::updateProgressing(u_int32_t prog) {
    QString str = QString::number(100 * (double) prog / thisDFA->getNBoxes());
    str += "%";
    lProgressing->setText(str);
}

void DFAInputGui::changeFromToFrctDim(int state) {
    if (state) {
        disconnect(thisTimer, SIGNAL(timeout()), this, SLOT(processRunning()));
        connect(thisTimer, SIGNAL(timeout()), this, SLOT(processRunningFrctDim()));
    } else {
        connect(thisTimer, SIGNAL(timeout()), this, SLOT(processRunning()));
        disconnect(thisTimer, SIGNAL(timeout()), this, SLOT(processRunningFrctDim()));
    }
}

void DFAInputGui::processRunningFrctDim() {
    if (actualBox < thisDFA->getNBoxes()) {
        double x, y;
        thisDFA->performAnalysisScale(x, y, actualBox++);
        Xtemp.push_back(log10(1 / x));
        Ytemp.push_back(log10(y / pow(x, 2)));
        updateProgressing(actualBox);
        IRWItem<double> * xt = new DataPointsDouble();
        xt->receiveData(Xtemp.data(), Xtemp.size());
        IRWItem<double> * yt = new DataPointsDouble();
        yt->receiveData(Ytemp.data(), Ytemp.size());
        thisPolFit = new LinearFit(xt, yt);
        thisPolFit->performFit();
        thisDEngine->detach();
        thisDEngine->setDataSet(thisPolFit);
        thisDEngine->paintAll();
        delete thisPolFit;
        delete xt;
        delete yt;
    } else {
        thisPolFit = NULL;
        thisDEngine->setDataSet(thisPolFit);
        cFrctDim->setEnabled(true);
        thisTimer->stop();
        delete thisYtemp;
    }
}

void DFAInputGui::processRunning() {
    if (actualBox < thisDFA->getNBoxes()) {
        double x, y;
        thisDFA->performAnalysisScale(x, y, actualBox++);
        Xtemp.push_back(log10(x));
        Ytemp.push_back(log10(y));
        updateProgressing(actualBox);
        IRWItem<double> * xt = new DataPointsDouble();
        xt->receiveData(Xtemp.data(), Xtemp.size());
        IRWItem<double> * yt = new DataPointsDouble();
        yt->receiveData(Ytemp.data(), Ytemp.size());
        IPolyfit * pol = new LinearFit(xt, yt);
        pol->performFit();
        thisDEngine->detach();
        thisDEngine->setDataSet(pol);
        thisDEngine->paintAll();
        delete pol;
        delete xt;
        delete yt;
    } else {
        thisPolFit = NULL;
        thisDEngine->setDataSet(thisPolFit);
        cFrctDim->setEnabled(true);
        thisTimer->stop();
        delete thisYtemp;
    }

}
