/* 
 * File:   GraphUi.h
 * Author: fernando
 *
 * Created on 24 de Abril de 2013, 19:15
 */

#ifndef _GRAPHUI_H
#define	_GRAPHUI_H
#include <stdio.h>
#include "ui_GraphUi.h"
#include "RWDpBase.h"
#include "RWVBase.h"
#include <QObject>
#include "ProbabilityBase.h"
#include <QImage>
#include <qwt/qwt_plot_curve.h>
#include <qwt/qwt_series_data.h>
#include "Tokenizer.h"
#include "Token.h"
#include <QString>
#include "BDProbabilityBase.h"
#include "IDrawingEngine.h"
#include "PollarDrawingEngine.h"
#include <QPrinter>
class GraphUi : public QMainWindow {

    Q_OBJECT
    enum TYPE {
        BIN = 0, POINTS = 1, FITTING = 2, NIL = 3, INTEGRAL_DFA = 4, D2_RW
    };
public:
    GraphUi();
    virtual ~GraphUi();

public slots:
    void changedScaleX(int a);
    void changedTicksX(int a);
    void changedScaleY(int a);
    void changedTicksY(int a);
    void gridOnOff(int state);
    void spinMinVal(int v);
    void spinMaxVal(int v);
    void spinBinMinVal(int v);
    void spinBinMaxVal(int v);
    void spinIntMinVal(int v);
    void spinIntMaxVal(int v);
    void spin2DMinVal(int v);
    void spin2DMaxVal(int v);
    void memoryRwOlay(int state);
    void plotMemoryWalk(IRWItem<QPollarF> *,QColor);
    void choose(int a);
    void connections();
    void showall(int a);
    void animate();
    void configureGuiRSChoice(RS_TYPES);
    void configureWidgetProbBase(IRandomWalk*);
    void randomSourceChoice();
    void memAllocChosen(MEM_ALLOC);
    void receiveWeierstass(u_int32_t L, double H, double B, double start, double end);
    void dfaPressedWeier();
    void dfaPressedRW();
    void quadDistCalled(int);
signals:
    void emitCallQDist(int);
protected:
    virtual void closeEvent(QCloseEvent*);
private:
    void DetachAll();
    void setVisibleIntegral(int init, int end);
    void setVisibleRWKL(int init, int end);
    void setVisibleRWKBL(int init, int end);
    void setVisible2DRWKL(int init, int end);
    void updateProb(TYPE a);
    void AcumuladoGUI(bool visible, int spinMax, int spinMin);
    void PassosGUI(bool visible, int spinMax, int spinMin);
    void IntegralGUI(bool visible, int spinMax, int spinMin);
    void D2RwGUI(bool visible, int spinMax, int spinMin);
    void CommonGui(bool visible);
    void setAxisToActualValues();

    Ui::GraphUi widget;
    //    RWVInt * noiseLine;
    int randomwalkSize;
    int MinRwk, MaxRwk;
    int BinMinRwk, BinMaxRwk;
    int IntMinRwk, IntMaxRwk;
    int D2MinRwk, D2MaxRwk;

    int chooseVal;
    IDrawingEngine<int> * fittingDrawing;
    IDrawingEngine<double> * normDrawing;
    IDrawingEngine<int> * noiseDrawing;
    IDrawingEngine<int> * integralDrawing;
    IDrawingEngine<double>* weiersDrawing;
    IDrawingEngine<QPollarF> * pollarDrawing;
    MEM_ALLOC memAlloc;
    IRWItem<double> *Xw, *Yw;
    u_int64_t nw, ns;
    //    ProbabilityBase * prob;
    IProbabilityBase<int, double> * prob;
};

#endif	/* _GRAPHUI_H */
