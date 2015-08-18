/* 
 * File:   DFAInputGui.h
 * Author: fordem
 *
 * Created on June 17, 2015, 8:03 PM
 */

#ifndef DFAINPUTGUI_H
#define	DFAINPUTGUI_H
#include "IRWItem.h"
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <qwt_plot.h>
#include <QWidget>
#include "RWDpIntervalBuilder.h"
#include "DFA.h"
#include <QTimer>
#include "FittingDrawingEngine.h"
#include <QCheckBox>

class DFAInputGui : public QDialog {
    Q_OBJECT
public:
    DFAInputGui(IRWItem<double>* X, IRWItem<double> * Y, QWidget * parent);
    DFAInputGui(IRWItem<double>* Y, double start, double end, u_int32_t length, QWidget * parent);
    virtual ~DFAInputGui();
protected slots:
    void attemptToRun();
    void processRunning();
    void changeFromToFrctDim(int);
    void processRunningFrctDim();
    
private:
    void configureGui();
    void updateProgressing(u_int32_t prog);
    FittingDrawingEngine<double> * thisDEngine;
    vector<double> Xtemp,Ytemp;
    IRWItem<double> * thisX,*thisXtemp, *thisY,*thisYtemp;
    IRWIntervalBuilder<double> * interval;
    DFA * thisDFA;
    QWidget * inputControls;
    QGridLayout * grdControls;
    QGridLayout * grdLayOut;
    QCheckBox * cFrctDim;
    QLabel * lFrctDim;
    QLabel * lMinBox;
    QLabel * lMaxBox;
    QLabel * lRatio;
    QLabel * lProgress;
    QLabel * lProgressing;
    QLineEdit * eMinBox;
    QLineEdit * eMaxBox;
    QDoubleSpinBox * eRatio;
    QPushButton * pRun;
    QwtPlot * thisPlot;
    QTimer * thisTimer;
    u_int32_t actualBox;
    IPolyfit * thisPolFit;
};

#endif	/* DFAINPUTGUI_H */

