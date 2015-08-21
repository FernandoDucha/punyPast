/*
 * File:   GraphUi.cpp
 * Author: fernando
 *
 * Created on 24 de Abril de 2013, 19:15
 */

#include <qglobal.h>
#include <qwidget.h>
#include <qwt_scale_engine.h>
#include <qwt_legend.h>
#include <qt5/QtCore/qlogging.h>
#include "GraphUi.h"
#include "BufferedProbabilityBase.h"
#include "DataPointsDrawingEngine.h"
#include "BDDataPointsDrawingEngine.h"
#include "BinDrawingEngine.h"
#include "BDBinDrawingEngine.h"
#include "IntegralDrawingEngine.h"
#include "BDIntegralDrawingEngine.h"
#include "FittingDrawingEngine.h"
#include "WeierstrassDrawingEngine.h"
#include "DFAInputGui.h"
#include "BufferedPollarDrawingEngine.h"
#include <QFileDialog>
#include <qwt_plot_renderer.h>

GraphUi::GraphUi() {
    widget.setupUi(this);
    //   grid = new GridItem();
    nw = 0;
    ns = 0;
    QPixmap icon("images/seed.png");
    icon.scaled(30, 30, Qt::KeepAspectRatio);
    setWindowIcon(icon);
    //    randomwalkSize=prob_b->GetDatap()->getSize();
    //widget.thisScene->addItem(grid);
    widget.comboxtks->setDefault_value(widget.plotview->axisMaxMajor(widget.plotview->xBottom));
    widget.comboxtks->setValue(widget.plotview->axisMaxMajor(widget.plotview->xBottom));
    widget.comboxstp->setDefault_value(widget.plotview->axisMaxMinor(widget.plotview->xBottom));
    widget.comboxstp->setValue(widget.plotview->axisMaxMinor(widget.plotview->xBottom));
    widget.comboytks->setDefault_value(widget.plotview->axisMaxMajor(widget.plotview->yLeft));
    widget.comboytks->setValue(widget.plotview->axisMaxMajor(widget.plotview->xBottom));
    widget.comboystp->setDefault_value(widget.plotview->axisMaxMinor(widget.plotview->yLeft));
    widget.comboystp->setValue(widget.plotview->axisMaxMinor(widget.plotview->xBottom));
    chooseVal = widget.choose->currentIndex();
    widget.choose->setEnabled(false);
    widget.ThisOverLay->setVisible(false);
    MinRwk = 0;
    MaxRwk = 0;
    BinMaxRwk = 0;
    BinMinRwk = 0;
    IntMaxRwk = 0;
    IntMinRwk = 0;
    D2MaxRwk = 0;
    D2MinRwk = 0;

    connections();
    widget.grid->hide();
    prob = NULL;
    Yw = new DataPointsDouble();
    Xw = new DataPointsDouble();
    widget.rand_source->showMaximized();
}

void GraphUi::connections() {
    connect(widget.comboxstp, SIGNAL(valueChanged(int)), this, SLOT(changedScaleX(int)));
    connect(widget.comboxtks, SIGNAL(valueChanged(int)), this, SLOT(changedTicksX(int)));
    connect(widget.comboystp, SIGNAL(valueChanged(int)), this, SLOT(changedScaleY(int)));
    connect(widget.comboytks, SIGNAL(valueChanged(int)), this, SLOT(changedTicksY(int)));
    connect(widget.gridOnOff, SIGNAL(stateChanged(int)), this, SLOT(gridOnOff(int)));
    connect(widget.quadDist, SIGNAL(stateChanged(int)), this, SLOT(quadDistCalled(int)));
    connect(widget.noColision, SIGNAL(stateChanged(int)), this, SLOT(memoryRwOlay(int)));
    connect(widget.spinmin, SIGNAL(valueChanged(int)), this, SLOT(spinMinVal(int)));
    connect(widget.spinmax, SIGNAL(valueChanged(int)), this, SLOT(spinMaxVal(int)));
    connect(widget.spinbinmin, SIGNAL(valueChanged(int)), this, SLOT(spinBinMinVal(int)));
    connect(widget.spinbinmax, SIGNAL(valueChanged(int)), this, SLOT(spinBinMaxVal(int)));
    connect(widget.spinintmin, SIGNAL(valueChanged(int)), this, SLOT(spinIntMinVal(int)));
    connect(widget.spinintmax, SIGNAL(valueChanged(int)), this, SLOT(spinIntMaxVal(int)));
    connect(widget.spin2dmin, SIGNAL(valueChanged(int)), this, SLOT(spin2DMinVal(int)));
    connect(widget.spin2dmax, SIGNAL(valueChanged(int)), this, SLOT(spin2DMaxVal(int)));
    connect(widget.choose, SIGNAL(currentIndexChanged(int)), this, SLOT(choose(int)));
    connect(widget.showall, SIGNAL(stateChanged(int)), this, SLOT(showall(int)));
    connect(widget.walks2d, SIGNAL(plotItem(IRWItem<QPollarF>*)), this, SLOT(plotMemoryWalk(IRWItem<QPollarF>*)));
    connect(this, SIGNAL(emitCallQDist(int)), this, SLOT(quadDistCalled(int)));
    connect(widget.ScreenShot, SIGNAL(pressed()), this, SLOT(animate()));
    connect(widget.rand_source, SIGNAL(choiceType(RS_TYPES)), this, SLOT(configureGuiRSChoice(RS_TYPES)));
    connect(widget.rand_source, SIGNAL(memAlloc(MEM_ALLOC)), this, SLOT(memAllocChosen(MEM_ALLOC)));
    connect(widget.expr_parse_wid, SIGNAL(createdRWK(IRandomWalk*)), this, SLOT(configureWidgetProbBase(IRandomWalk*)));
    connect(widget.file_qbrw_wid, SIGNAL(createdRWK(IRandomWalk*)), this, SLOT(configureWidgetProbBase(IRandomWalk*)));
    connect(widget.lcg_brn_wid, SIGNAL(createdRWK(IRandomWalk*)), this, SLOT(configureWidgetProbBase(IRandomWalk*)));
    connect(widget.weie_ndcf_wid, SIGNAL(createdRWK(IRandomWalk*)), this, SLOT(configureWidgetProbBase(IRandomWalk*)));
    connect(widget.randomSourceChoice, SIGNAL(pressed()), this, SLOT(randomSourceChoice()));
    connect(widget.weie_ndcf_wid, SIGNAL(weiestrassR(u_int32_t, double, double, double, double)), this, SLOT(receiveWeierstass(u_int32_t, double, double, double, double)));
}

void GraphUi::quadDistCalled(int a) {
    if (a == Qt::Checked) {
        switch (chooseVal) {
            case POINTS:
                normDrawing->paintQAverageDistance();
                break;
            case INTEGRAL_DFA:
                integralDrawing->paintQAverageDistance();
                break;
            default:
                return;
                break;
        }
    } else {

    }

}

void GraphUi::receiveWeierstass(u_int32_t L, double H, double B, double start, double end) {
    Yw = prob->buildWeiestrass(H, B, start, end, L);
    IRWIntervalBuilder<double> * rw = new RWDpIntervalBuilder<double>();
    Xw = rw->produceLinearInterval(start, end, (end - start) / (L));
    dynamic_cast<WeierstrassDrawingEngine<double>*> (weiersDrawing)->setYandX(Xw, Yw);
    weiersDrawing->paintAll();
}

void GraphUi::dfaPressedWeier() {
    if (Xw != NULL && Yw != NULL) {
        DFAInputGui thisDFA(Xw, Yw, this);
        thisDFA.exec();
    }
}

void GraphUi::dfaPressedRW() {
    DFAInputGui thisDFA(prob->getAverageWalkByPoints(), 0, prob->GetThisbrwk()->GetWalkSize(), prob->GetThisbrwk()->GetWalkSize(), this);
    thisDFA.exec();
}

void GraphUi::memAllocChosen(MEM_ALLOC val) {
    memAlloc = val;
}

void GraphUi::randomSourceChoice() {
    //    widget.rand_source->showMaximized();
    widget.rand_source->exec();
}

void GraphUi::configureWidgetProbBase(IRandomWalk* irwk) {
    if (irwk) {
        nw = irwk->GetNumberRandomWalks();
        ns = irwk->GetWalkSize();
        if (prob == NULL) {
            switch (memAlloc) {
                case ALL_MEM:
                    prob = new ProbabilityBase(irwk);
                    normDrawing = new DataPointsDrawingEngine<double>(widget.plotview);
                    normDrawing->setDataSet(prob->GetDatap());
                    noiseDrawing = new BinDrawingEngine<int>(widget.plotview);
                    noiseDrawing->setDataSet(prob->GetDatabinp());
                    integralDrawing = new IntegralDrawingEngine<int>(widget.plotview);
                    integralDrawing->setDataSet(prob->GetDatabinp());
                    fittingDrawing = new FittingDrawingEngine<int>(widget.plotview);
                    pollarDrawing = new PollarDrawingEngine(widget.plotview);
                    pollarDrawing->setDataSet(prob->getAll2DWalks());
                    widget.choose->setEnabled(true);
                    break;
                case ALL_DISK:
                    prob = new BufferedProbabilityBase(irwk);
                    normDrawing = new DataPointsDrawingEngine<double>(widget.plotview);
                    normDrawing->setDataSet(prob->GetDatap());
                    noiseDrawing = new BinDrawingEngine<int>(widget.plotview);
                    noiseDrawing->setDataSet(prob->GetDatabinp());
                    integralDrawing = new IntegralDrawingEngine<int>(widget.plotview);
                    integralDrawing->setDataSet(prob->GetDatabinp());
                    fittingDrawing = new FittingDrawingEngine<int>(widget.plotview);
                    pollarDrawing = new BufferedPollarDrawingEngine(widget.plotview);
                    pollarDrawing->setDataSet(prob->getAll2DWalks());
                    widget.choose->setEnabled(true);
                    break;
                case SQL_DB:
                    prob = new BDProbabilityBase(irwk);
                    normDrawing = new BDDataPointsDrawingEngine<double>(widget.plotview);
                    normDrawing->setDataSet(dynamic_cast<BDProbabilityBase*> (prob)->getBd());
                    noiseDrawing = new BDBinDrawingEngine<int>(widget.plotview);
                    noiseDrawing->setDataSet(dynamic_cast<BDProbabilityBase*> (prob)->getBd());
                    integralDrawing = new BDIntegralDrawingEngine<int>(widget.plotview);
                    integralDrawing->setDataSet(dynamic_cast<BDProbabilityBase*> (prob)->getBd());
                    fittingDrawing = new FittingDrawingEngine<int>(widget.plotview);
                    widget.choose->setEnabled(true);
                    break;
            }

        } else {
            DetachAll();
            widget.choose->setCurrentIndex(0);
            delete prob;
            delete normDrawing;
            delete integralDrawing;
            delete noiseDrawing;
            delete fittingDrawing;
            delete pollarDrawing;
            switch (memAlloc) {
                case ALL_MEM:
                    prob = new ProbabilityBase(irwk);
                    normDrawing = new DataPointsDrawingEngine<double>(widget.plotview);
                    normDrawing->setDataSet(prob->GetDatap());
                    noiseDrawing = new BinDrawingEngine<int>(widget.plotview);
                    noiseDrawing->setDataSet(prob->GetDatabinp());
                    integralDrawing = new IntegralDrawingEngine<int>(widget.plotview);
                    integralDrawing->setDataSet(prob->GetDatabinp());
                    fittingDrawing = new FittingDrawingEngine<int>(widget.plotview);
                    pollarDrawing = new PollarDrawingEngine(widget.plotview);
                    pollarDrawing->setDataSet(prob->getAll2DWalks());
                    widget.choose->setEnabled(true);
                    break;
                case ALL_DISK:
                    prob = new BufferedProbabilityBase(irwk);
                    normDrawing = new DataPointsDrawingEngine<double>(widget.plotview);
                    normDrawing->setDataSet(prob->GetDatap());
                    noiseDrawing = new BinDrawingEngine<int>(widget.plotview);
                    noiseDrawing->setDataSet(prob->GetDatabinp());
                    integralDrawing = new IntegralDrawingEngine<int>(widget.plotview);
                    integralDrawing->setDataSet(prob->GetDatabinp());
                    fittingDrawing = new FittingDrawingEngine<int>(widget.plotview);
                    pollarDrawing = new BufferedPollarDrawingEngine(widget.plotview);
                    pollarDrawing->setDataSet(prob->getAll2DWalks());
                    widget.choose->setEnabled(true);
                    break;
                case SQL_DB:
                    prob = new BDProbabilityBase(irwk);
                    normDrawing = new BDDataPointsDrawingEngine<double>(widget.plotview);
                    normDrawing->setDataSet(dynamic_cast<BDProbabilityBase*> (prob)->getBd());
                    noiseDrawing = new BDBinDrawingEngine<int>(widget.plotview);
                    noiseDrawing->setDataSet(dynamic_cast<BDProbabilityBase*> (prob)->getBd());
                    integralDrawing = new BDIntegralDrawingEngine<int>(widget.plotview);
                    integralDrawing->setDataSet(dynamic_cast<BDProbabilityBase*> (prob)->getBd());
                    fittingDrawing = new FittingDrawingEngine<int>(widget.plotview);
                    widget.choose->setEnabled(true);
                    break;
            }
        }
        weiersDrawing = new WeierstrassDrawingEngine<double>(widget.plotview);
    }
}

void GraphUi::configureGuiRSChoice(RS_TYPES rs_type) {
    switch (rs_type) {
        case FA_QRNG:
            widget.weie_ndcf_wid->setMeVisible(false);
            widget.expr_parse_wid->setMeVisible(false);
            widget.file_qbrw_wid->setMeVisible(true);
            widget.lcg_brn_wid->setMeVisible(false);
            connect(widget.pDFA, SIGNAL(released()), this, SLOT(dfaPressedRW()));
            disconnect(widget.pDFA, SIGNAL(released()), this, SLOT(dfaPressedWeier()));
            widget.choose->setEnabled(false);
            break;
        case RNG_EP:
            widget.weie_ndcf_wid->setMeVisible(false);
            widget.file_qbrw_wid->setMeVisible(false);
            widget.expr_parse_wid->setMeVisible(true);
            widget.lcg_brn_wid->setMeVisible(false);
            connect(widget.pDFA, SIGNAL(released()), this, SLOT(dfaPressedRW()));
            disconnect(widget.pDFA, SIGNAL(released()), this, SLOT(dfaPressedWeier()));
            widget.choose->setEnabled(false);
            break;
        case RNG_CD:
            widget.weie_ndcf_wid->setMeVisible(false);
            widget.lcg_brn_wid->setMeVisible(true);
            widget.expr_parse_wid->setMeVisible(false);
            widget.file_qbrw_wid->setMeVisible(false);
            connect(widget.pDFA, SIGNAL(released()), this, SLOT(dfaPressedRW()));
            disconnect(widget.pDFA, SIGNAL(released()), this, SLOT(dfaPressedWeier()));
            widget.choose->setEnabled(false);
            break;
        case WEIES:
            widget.weie_ndcf_wid->setMeVisible(true);
            widget.expr_parse_wid->setMeVisible(false);
            widget.file_qbrw_wid->setMeVisible(false);
            widget.lcg_brn_wid->setMeVisible(false);
            disconnect(widget.pDFA, SIGNAL(released()), this, SLOT(dfaPressedRW()));
            connect(widget.pDFA, SIGNAL(released()), this, SLOT(dfaPressedWeier()));
            widget.choose->setEnabled(false);
            break;
        case NONE:
            widget.weie_ndcf_wid->setMeVisible(false);
            widget.expr_parse_wid->setMeVisible(false);
            widget.file_qbrw_wid->setMeVisible(false);
            widget.lcg_brn_wid->setMeVisible(false);
            widget.choose->setEnabled(false);
            break;
    };
}

void GraphUi::updateProb(TYPE a) {
    if ((nw > 0) &&(ns > 0)) {
        if (a == NIL) {
            widget.plotview->insertLegend(NULL);
        } else if (a == BIN) {
            widget.plotview->insertLegend(NULL);
            widget.spinbinmax->setRange(0, prob->GetThisbrwk()->GetNumberRandomWalks());
            widget.spinbinmin->setRange(0, prob->GetThisbrwk()->GetNumberRandomWalks());
            widget.spinbinmin->setSingleStep(1);
            widget.spinbinmax->setSingleStep(1);
            randomwalkSize = prob->GetThisbrwk()->GetNumberRandomWalks();
        } else if (a == POINTS) {
            widget.plotview->insertLegend(NULL);
            widget.spinmax->setRange(0, prob->GetThisbrwk()->GetNumberRandomWalks());
            widget.spinmin->setRange(0, prob->GetThisbrwk()->GetNumberRandomWalks());
            widget.spinmin->setSingleStep(1);
            widget.spinmax->setSingleStep(1);
            randomwalkSize = prob->GetThisbrwk()->GetNumberRandomWalks();
        } else if (a == FITTING) {
            fittingDrawing->setDataSet(prob->CurveFitting());
            fittingDrawing->paintAll();
        } else if (a == INTEGRAL_DFA) {
            widget.plotview->insertLegend(NULL);
            widget.spinintmax->setRange(0, prob->GetThisbrwk()->GetNumberRandomWalks());
            widget.spinintmin->setRange(0, prob->GetThisbrwk()->GetNumberRandomWalks());
            widget.spinintmin->setSingleStep(1);
            widget.spinintmax->setSingleStep(1);
            randomwalkSize = prob->GetThisbrwk()->GetNumberRandomWalks();
        } else if (a == D2_RW) {
            widget.plotview->insertLegend(NULL);
            widget.spin2dmax->setRange(0, prob->GetThisbrwk()->GetNumberRandomWalks());
            widget.spin2dmin->setRange(0, prob->GetThisbrwk()->GetNumberRandomWalks());
            widget.spin2dmin->setSingleStep(1);
            widget.spin2dmax->setSingleStep(1);
            randomwalkSize = prob->GetThisbrwk()->GetNumberRandomWalks();
        }
    }
}

void GraphUi::DetachAll() {
    normDrawing->detach();
    noiseDrawing->detach();
    integralDrawing->detach();
    widget.picker->getPointClicked()->setVisible(false);
    widget.plotview->detachItems(QwtPlotItem::Rtti_PlotItem, false);
    widget.picker->renewPointSelected();
}

void GraphUi::changedScaleX(int a) {
    widget.plotview->setAxisMaxMinor(widget.plotview->xBottom, a);
    widget.plotview->replot();
}

void GraphUi::changedTicksX(int a) {
    widget.plotview->setAxisMaxMajor(widget.plotview->xBottom, a);
    widget.plotview->replot();
}

void GraphUi::changedScaleY(int a) {
    widget.plotview->setAxisMaxMinor(widget.plotview->yLeft, a);
    widget.plotview->replot();
}

void GraphUi::changedTicksY(int a) {
    widget.plotview->setAxisMaxMajor(widget.plotview->yLeft, a);
    widget.plotview->replot();
}

void GraphUi::setAxisToActualValues() {
    changedScaleX(widget.comboxstp->getActual_value());

    changedTicksX(widget.comboxtks->getActual_value());

    changedScaleY(widget.comboystp->getActual_value());

    changedTicksY(widget.comboytks->getActual_value());
}

GraphUi::~GraphUi() {
}

void GraphUi::closeEvent(QCloseEvent* e) {
    delete prob;
    QMainWindow::closeEvent(e);
}

void GraphUi::gridOnOff(int state) {
    if (state == Qt::Checked) {
        widget.grid->attach(widget.plotview);
        widget.grid->show();
        widget.plotview->replot();
    } else {
        widget.grid->attach(widget.plotview);
        widget.grid->hide();
        widget.plotview->replot();
    }
}

void GraphUi::spinMaxVal(int v) {
    if (v >= MinRwk) {
        setVisibleRWKL(MinRwk, v);
        MaxRwk = v;
    } else {
        widget.spinmax->setValue(MaxRwk);
    }
    //    widget.lines->setText(QString::number(visible));
}

void GraphUi::spinMinVal(int v) {
    if (v <= MaxRwk) {
        setVisibleRWKL(v, MaxRwk);
        MinRwk = v;
    } else {
        widget.spinmin->setValue(MinRwk);
    }
    //    widget.lines->setText(QString::number(visible));
}

void GraphUi::spinBinMinVal(int v) {
    if (v <= BinMaxRwk) {
        setVisibleRWKBL(v, BinMaxRwk);
        BinMinRwk = v;
    } else {
        widget.spinbinmin->setValue(BinMinRwk);
    }
    //    widget.lines->setText(QString::number(visible));
}

void GraphUi::spinBinMaxVal(int v) {
    if (v >= BinMinRwk) {
        setVisibleRWKBL(BinMinRwk, v);
        BinMaxRwk = v;
    } else {
        widget.spinbinmax->setValue(BinMaxRwk);
    }
    //    widget.lines->setText(QString::number(visible));
}

void GraphUi::spinIntMinVal(int v) {
    if (v <= IntMaxRwk) {
        setVisibleIntegral(v, IntMaxRwk);
        IntMinRwk = v;
    } else {
        widget.spinintmin->setValue(IntMinRwk);
    }
}

void GraphUi::spinIntMaxVal(int v) {
    if (v >= IntMinRwk) {
        setVisibleIntegral(IntMinRwk, v);
        IntMaxRwk = v;
    } else {
        widget.spinintmax->setValue(IntMaxRwk);
    }
}

void GraphUi::spin2DMinVal(int v) {
    if (v <= D2MaxRwk) {
        setVisible2DRWKL(v, D2MaxRwk);
        D2MinRwk = v;
    } else {
        widget.spin2dmin->setValue(D2MinRwk);
    }
}

void GraphUi::spin2DMaxVal(int v) {
    if (v >= D2MinRwk) {
        setVisible2DRWKL(D2MinRwk, v);
        D2MaxRwk = v;
    } else {
        widget.spin2dmax->setValue(D2MaxRwk);
    }
}

void GraphUi::plotMemoryWalk(IRWItem<QPollarF> * item) {
    pollarDrawing->detach();
    pollarDrawing->addToPlot(item);
    delete item;
    widget.plotview->replot();
}

void GraphUi::memoryRwOlay(int state) {
    if (state == Qt::Checked) {
        MemoryRandomWalk * novo = new MemoryRandomWalk(prob->GetThisbrwk(), prob->GetThisbrwk()->GetWalkSize());
        widget.walks2d->setMemoryRW(novo);
        widget.walks2d->setVisible(true);
    } else {
        widget.walks2d->setMemoryRW(NULL);
        widget.walks2d->setVisible(false);

    }
}

void GraphUi::choose(int val) {
    if (val == 0) {
        if (chooseVal == 1) {
            AcumuladoGUI(false, 0, 0);
        } else if (chooseVal == 4) {
            IntegralGUI(false, 0, 0);
        } else if (chooseVal == 2) {
            PassosGUI(false, 0, 0);
        } else if (chooseVal == 5) {
            D2RwGUI(false, 0, 0);
        }
        DetachAll();
        CommonGui(false);
        updateProb(NIL);
        chooseVal = val;
    } else if (val == 1) {
        if (chooseVal == 2) {
            PassosGUI(false, 0, 0);
        } else if (chooseVal == 4) {
            IntegralGUI(false, 0, 0);
        } else if (chooseVal == 5) {
            D2RwGUI(false, 0, 0);
        }
        DetachAll();
        updateProb(POINTS);
        CommonGui(true);
        AcumuladoGUI(true, 0, 0);
        chooseVal = val;
    } else if (val == 2) {
        if (chooseVal == 1) {
            AcumuladoGUI(false, 0, 0);
        } else if (chooseVal == 4) {
            IntegralGUI(false, 0, 0);
        } else if (chooseVal == 5) {
            D2RwGUI(false, 0, 0);
        }
        DetachAll();
        updateProb(BIN);
        CommonGui(true);
        PassosGUI(true, 0, 0);
        chooseVal = val;
    } else if (val == 3) {
        if (chooseVal == 2) {
            PassosGUI(false, 0, 0);
        } else if (chooseVal == 1) {
            AcumuladoGUI(false, 0, 0);
        } else if (chooseVal == 4) {
            IntegralGUI(false, 0, 0);
        } else if (chooseVal == 5) {
            D2RwGUI(false, 0, 0);
        }
        DetachAll();
        CommonGui(false);
        updateProb(FITTING);
        chooseVal = val;
    } else if (val == 4) {
        if (chooseVal == 2) {
            PassosGUI(false, 0, 0);
        } else if (chooseVal == 1) {
            AcumuladoGUI(false, 0, 0);
        } else if (chooseVal == 5) {
            D2RwGUI(false, 0, 0);
        }
        DetachAll();
        CommonGui(true);
        IntegralGUI(true, 0, 0);
        updateProb(INTEGRAL_DFA);
        chooseVal = val;
    } else if (val == 5) {
        if (chooseVal == 2) {
            PassosGUI(false, 0, 0);
        } else if (chooseVal == 4) {
            IntegralGUI(false, 0, 0);
        } else if (chooseVal == 1) {
            AcumuladoGUI(false, 0, 0);
        }
        DetachAll();
        updateProb(D2_RW);
        CommonGui(true);
        D2RwGUI(true, 0, 0);
        chooseVal = val;
    }
}

void GraphUi::AcumuladoGUI(bool visible, int spinMax, int spinMin) {
    widget.noColision->setVisible(false);
    widget.lblNoColision->setVisible(false);
    widget.quadDist->setVisible(visible);
    widget.lblQuadDist->setVisible(visible);
    widget.spinmax->setVisible(visible);
    widget.spinmin->setVisible(visible);
    widget.spinmax->setValue(spinMax);
    widget.spinmin->setValue(spinMin);
    widget.linesLbl->setText(QString("Lines:"));
}

void GraphUi::D2RwGUI(bool visible, int spinMax, int spinMin) {
    if (!visible) {
        widget.noColision->setChecked(false);
    }
    widget.noColision->setVisible(visible);
    widget.lblNoColision->setVisible(visible);
    widget.quadDist->setVisible(visible);
    widget.lblQuadDist->setVisible(visible);
    widget.spin2dmax->setVisible(visible);
    widget.spin2dmin->setVisible(visible);
    widget.spin2dmax->setValue(spinMax);
    widget.spin2dmin->setValue(spinMin);
    spinBinMaxVal(0);
    widget.linesLbl->setText(QString(" N Rw's:"));
}

void GraphUi::PassosGUI(bool visible, int spinMax, int spinMin) {
    widget.noColision->setVisible(false);
    widget.lblNoColision->setVisible(false);
    widget.quadDist->setVisible(visible);
    widget.lblQuadDist->setVisible(visible);
    widget.spinbinmax->setVisible(visible);
    widget.spinbinmin->setVisible(visible);
    widget.spinbinmax->setValue(spinMax);
    widget.spinbinmin->setValue(spinMin);
    spinBinMaxVal(0);
    widget.linesLbl->setText(QString("Sums:"));
}

void GraphUi::IntegralGUI(bool visible, int spinMax, int spinMin) {
    widget.noColision->setVisible(false);
    widget.lblNoColision->setVisible(false);
    widget.quadDist->setVisible(visible);
    widget.lblQuadDist->setVisible(visible);
    widget.spinintmax->setVisible(visible);
    widget.spinintmin->setVisible(visible);
    widget.spinintmax->setValue(spinMax);
    widget.spinintmin->setValue(spinMin);
    widget.linesLbl->setText(QString("Integral DFA:"));
}

void GraphUi::CommonGui(bool visible) {
    widget.noColision->setVisible(false);
    widget.lblNoColision->setVisible(false);
    widget.lines->setVisible(visible);
    widget.linesLbl->setVisible(visible);
    widget.nrLinhasInf->setVisible(visible);
    widget.nrLinhasSup->setVisible(visible);
    widget.labelshowall->setVisible(visible);
    widget.showall->setVisible(visible);
    widget.showall->setChecked(false);
    widget.ScreenShot->setVisible(visible);

}

void GraphUi::showall(int a) {
    if (a == Qt::Checked) {
        if (chooseVal == 1) {
            normDrawing->paintAll();
        } else if (chooseVal == 2) {
            noiseDrawing->paintAll();
        } else if (chooseVal == 4) {
            integralDrawing->paintAll();
        }
    } else if (a == Qt::Unchecked) {
        if (chooseVal == 1) {
            normDrawing->detach();
        } else if (chooseVal == 2) {
            noiseDrawing->detach();
        } else if (chooseVal == 4) {
            integralDrawing->detach();
        }
    }
    widget.plotview->replot();
}

void GraphUi::animate() {


    QFileDialog D(this, "Escolha o nome do arquivo.", "./");
    D.setAcceptMode(QFileDialog::AcceptSave);
    QStringList s;
    QStringList filters;
    filters << "pdf (*.pdf)"
            << "png (*.png)";
    D.setNameFilters(filters);
    if (D.exec()) {
        QRectF bound;
        s = D.selectedFiles();
        QwtPlotRenderer * qwtr = new QwtPlotRenderer();
        qwtr->setDiscardFlag(QwtPlotRenderer::DiscardNone);
        qwtr->setLayoutFlag(QwtPlotRenderer::FrameWithScales);
        if (D.selectedNameFilter() == filters[0]) {
            qwtr->renderDocument(widget.plotview, s.at(0), "pdf", widget.plotview->canvas()->size(), 75);
        }else if (D.selectedNameFilter() == filters[1]) {
            qwtr->renderDocument(widget.plotview, s.at(0), "png", widget.plotview->canvas()->size(), 75);
        }
    }
}

void GraphUi::setVisibleIntegral(int init, int end) {
    integralDrawing->paintFromTo(init, end);
    widget.lines->setText(QString::number(end - init));
    widget.plotview->replot();
    emit quadDistCalled(widget.quadDist->isChecked() ? Qt::Checked : 0);
}

void GraphUi::setVisibleRWKL(int init, int end) {
    normDrawing->paintFromTo(init, end);
    widget.lines->setText(QString::number(end - init));
    widget.plotview->replot();
    emit quadDistCalled(widget.quadDist->isChecked() ? Qt::Checked : 0);

}

void GraphUi::setVisibleRWKBL(int init, int end) {
    noiseDrawing->paintFromTo(init, end);
    widget.lines->setText(QString::number(end - init));
    widget.plotview->replot();
}

void GraphUi::setVisible2DRWKL(int init, int end) {
    pollarDrawing->paintFromTo(init, end);
    widget.lines->setText(QString::number(end - init));
    widget.plotview->replot();
}