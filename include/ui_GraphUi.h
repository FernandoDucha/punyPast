/********************************************************************************
 ** Form generated from reading UI file 'GraphUi.ui'
 **
 ** Created: Thu Apr 25 19:25:36 2013
 **      by: Qt User Interface Compiler version 4.8.3
 **
 ** WARNING! All changes made in this file will be lost when recompiling UI file!
 ********************************************************************************/

#ifndef UI_GRAPHUI_H
#define UI_GRAPHUI_H

#include <QtCore/QVariant>
#include <qt5/QtGui/QTextCharFormat>
#include <qt5/QtWidgets/QAction>
#include <qt5/QtWidgets/QApplication>
#include <qt5/QtWidgets/QGraphicsView>
#include <qt5/QtWidgets/QGridLayout>
#include <qt5/QtWidgets/QMainWindow>
#include <qt5/QtWidgets/QWidget>
#include <qt5/QtWidgets/QLabel>
#include <qt5/QtWidgets/QTextEdit>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include "GULineEdit.h"
#include "GraphMagnifier.h"
#include  <qt5/QtWidgets/QCheckBox>
#include <qt5/QtWidgets/QSpinBox>
#include <qt5/QtWidgets/QComboBox>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_grid.h>
#include <qwt/qwt_plot_magnifier.h>
#include <GraphPicker.h>
#include <GraphPanner.h>
#include <QPixmap>
#include <Qt>
#include "Overlay.h"
#include "RandomSource.h"
#include "ExprParserWidget.h"
#include "FileQBRWWidget.h"
#include "LCGBinaryRandomWalk.h"
#include "LCGRngWidget.h"
#include "WeiestrassInputWidget.h"
#include "Walks2DOverlay.h"
QT_BEGIN_NAMESPACE

class Ui_GraphUi {
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGridLayout * controlsLayout;
    QwtPlot *plotview;
    QWidget * controlsW;
    QWidget * ctrlLines;
    QGridLayout * ctrlLinesLayout;

    QLabel * xstep, *xticks;
    QLabel * ystep, *yticks;
    GULineEdit *comboxtks, *comboxstp, *comboytks, *comboystp;
    QCheckBox * gridOnOff;
    QLabel * labelgrid, *state;
    QComboBox * choose;
    QSpinBox * spinmin, * spinmax;
    QSpinBox * spinbinmin, * spinbinmax;
    QSpinBox * spinintmin, * spinintmax;
    QSpinBox * spin2dmin, * spin2dmax;

    QLabel * lines, *nrLinhasInf, *nrLinhasSup, *linesLbl;
    Overlay * ThisOverLay;
    QCheckBox * showall, *quadDist;
    QLabel * labelshowall, *lblQuadDist;
    QwtPlotGrid * grid;
    GraphPicker * picker;
    GraphMagnifier * qwtpmag;
    GraphPanner * qwtpanner;
    RandomSource * rand_source;
    ExprParserWidget * expr_parse_wid;
    FileQBRWWidget * file_qbrw_wid;
    LCGRngWidget * lcg_brn_wid;
    WeiestrassInputWidget * weie_ndcf_wid;
    QPushButton * randomSourceChoice;
    QPushButton * pDFA;
    QPushButton * ScreenShot;
    QCheckBox * noColision;
    QLabel * lblNoColision;
    Walks2DOverlay * walks2d;
    void setupUi(QMainWindow *GraphUi) {
        if (GraphUi->objectName().isEmpty())
            GraphUi->setObjectName(QString::fromUtf8("GraphUi"));
        GraphUi->resize(800, 600);
        centralwidget = new QWidget(GraphUi);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setMaximumSize(QSize(800, 575));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setSizeConstraint(QLayout::SetMaximumSize);
        plotview = new QwtPlot(centralwidget);
        plotview->setObjectName(QString::fromUtf8("graphicsView"));
        plotview->setCanvasBackground(QColor(Qt::white));
        picker = new GraphPicker(dynamic_cast<QwtPlotCanvas*> (plotview->canvas()));
        qwtpmag = new GraphMagnifier(dynamic_cast<QwtPlotCanvas*> (plotview->canvas()));
        qwtpanner = new GraphPanner(dynamic_cast<QwtPlotCanvas*> (plotview->canvas()));
        gridLayout->addWidget(plotview, 0, 0, 10, 10);
        controlsW = new QWidget(centralwidget);
        expr_parse_wid = new ExprParserWidget(controlsW);
        expr_parse_wid->setContentsMargins(0, 0, 0, 0);
        expr_parse_wid->setMeVisible(false);
        file_qbrw_wid = new FileQBRWWidget(controlsW);
        file_qbrw_wid->setContentsMargins(0, 0, 0, 0);
        file_qbrw_wid->setMeVisible(false);
        lcg_brn_wid = new LCGRngWidget(controlsW);
        lcg_brn_wid->setContentsMargins(0, 0, 0, 0);
        lcg_brn_wid->setMeVisible(false);
        weie_ndcf_wid = new WeiestrassInputWidget(controlsW);
        weie_ndcf_wid->setContentsMargins(0, 0, 0, 0);
        weie_ndcf_wid->setMeVisible(false);
        randomSourceChoice = new QPushButton(controlsW);
        randomSourceChoice->setContentsMargins(0, 0, 0, 0);
        QPixmap chooseSeed = QPixmap("images/xhair1.png");
        chooseSeed.scaled(50, 50, Qt::KeepAspectRatio);
        QIcon * temp = new QIcon(chooseSeed);
        randomSourceChoice->setIcon(*temp);
        randomSourceChoice->setIconSize(QSize(50, 50));
        randomSourceChoice->setToolTip("Open RNG source you wish to study.");
        //        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        //        sizePolicy.setHorizontalStretch(0);
        //        sizePolicy.setVerticalStretch(0);
        //        controlsW->setSizePolicy(sizePolicy2);
        controlsW->setContentsMargins(0, 0, 0, 0);
        xstep = new QLabel(controlsW);
        xstep->setText("Ticks Min X:");
        xstep->setContentsMargins(0, 0, 0, 0);
        xticks = new QLabel(controlsW);
        xticks->setText("Ticks Major X:");
        xticks->setContentsMargins(0, 0, 0, 0);
        comboxstp = new GULineEdit(controlsW);
        comboxtks = new GULineEdit(controlsW);
        comboxstp->setContentsMargins(0, 0, 0, 0);
        comboxtks->setContentsMargins(0, 0, 0, 0);
        ThisOverLay = new Overlay(centralwidget);
        expr_parse_wid->setOverlay(ThisOverLay);
        walks2d = new Walks2DOverlay(centralwidget);
        walks2d->setVisible(false);
        ystep = new QLabel(controlsW);
        ystep->setText("Ticks Min Y:");
        ystep->setContentsMargins(0, 0, 0, 0);
        yticks = new QLabel(controlsW);
        yticks->setText("Ticks Major Y:");
        yticks->setContentsMargins(0, 0, 0, 0);
        comboystp = new GULineEdit(controlsW);
        comboytks = new GULineEdit(controlsW);
        comboystp->setContentsMargins(0, 0, 0, 0);
        comboytks->setContentsMargins(0, 0, 0, 0);
        labelgrid = new QLabel("Grid?");
        labelgrid->setContentsMargins(0, 0, 0, 0);
        gridOnOff = new QCheckBox(controlsW);
        gridOnOff->setContentsMargins(0, 0, 0, 0);
        state = new QLabel("Type:");
        state->setContentsMargins(0, 0, 0, 0);
        choose = new QComboBox(controlsW);
        choose->addItem("", QVariant(-1));
        choose->addItem("Random Walk", QVariant(0));
        choose->addItem("White Noise", QVariant(1));
        choose->addItem("Fitting", QVariant(2));
        choose->addItem("Integral DFA", QVariant(3));
        choose->addItem("2D-RW", QVariant(4));

        //choose->addItem("Animate",QVariant(1));

        spinmax = new QSpinBox(NULL);
        spinmax->setContentsMargins(0, 0, 0, 0);
        spinmin = new QSpinBox(NULL);
        spinmin->setContentsMargins(0, 0, 0, 0);
        spinbinmax = new QSpinBox(NULL);
        spinbinmax->setContentsMargins(0, 0, 0, 0);
        spinbinmin = new QSpinBox(NULL);
        spinbinmin->setContentsMargins(0, 0, 0, 0);

        spinintmax = new QSpinBox(NULL);
        spinintmax->setContentsMargins(0, 0, 0, 0);
        spinintmin = new QSpinBox(NULL);
        spinintmin->setContentsMargins(0, 0, 0, 0);

        spin2dmax = new QSpinBox(NULL);
        spin2dmax->setContentsMargins(0, 0, 0, 0);
        spin2dmin = new QSpinBox(NULL);
        spin2dmin->setContentsMargins(0, 0, 0, 0);

        lines = new QLabel("");
        lines->setContentsMargins(0, 0, 0, 0);
        nrLinhasSup = new QLabel("Upper");
        nrLinhasSup->setContentsMargins(0, 0, 0, 0);
        nrLinhasInf = new QLabel("Lower");
        nrLinhasInf->setContentsMargins(0, 0, 0, 0);
        linesLbl = new QLabel(QString("Lines:"));
        linesLbl->setContentsMargins(0, 0, 0, 0);
        quadDist = new QCheckBox(NULL);
        quadDist->setContentsMargins(0, 0, 0, 0);
        lblQuadDist = new QLabel("D^2:");
        lblQuadDist->setContentsMargins(0, 0, 0, 0);
        noColision = new QCheckBox(NULL);
        noColision->setContentsMargins(0, 0, 0, 0);
        lblNoColision = new QLabel("No Collision:");
        lblNoColision->setContentsMargins(0,0,0,0);
        
        showall = new QCheckBox(NULL);
        showall->setContentsMargins(0, 0, 0, 0);
        labelshowall = new QLabel("Show All:");
        labelshowall->setContentsMargins(0, 0, 0, 0);
        pDFA = new QPushButton(controlsW);
        pDFA->setText("DFA");
        ScreenShot = new QPushButton(NULL);
        ScreenShot->setContentsMargins(0, 0, 0, 0);
        ScreenShot->setText("ScreeShot");
        spinbinmax->setVisible(false);
        spinbinmin->setVisible(false);
        spinmax->setVisible(false);
        spinmin->setVisible(false);
        spinintmax->setVisible(false);
        spinintmin->setVisible(false);
        spin2dmax->setVisible(false);
        spin2dmin->setVisible(false);
        ScreenShot->setVisible(false);
        nrLinhasInf->setVisible(false);
        nrLinhasSup->setVisible(false);
        lines->setVisible(false);
        linesLbl->setVisible(false);
        showall->setVisible(false);
        labelshowall->setVisible(false);
        quadDist->setVisible(false);
        lblQuadDist->setVisible(false);
        lblNoColision->setVisible(false);
        noColision->setVisible(false);
        grid = new QwtPlotGrid();
        QPen p;
        p.setBrush(QColor(125, 125, 125));
        p.setStyle(Qt::DashLine);
        grid->setMinorPen(p);
        QPen p1;
        p1.setBrush(QColor(200, 200, 200));
        p1.setStyle(Qt::DashDotDotLine);
        grid->setMajorPen(p);
        grid->setMinorPen(p1);

        grid->enableX(true);
        grid->enableY(true);
        grid->enableXMin(true);
        grid->enableYMin(true);
        grid->attach(plotview);

        ctrlLines = new QWidget(centralwidget);

        ctrlLinesLayout = new QGridLayout(ctrlLines);

        controlsLayout = new QGridLayout(controlsW);
        controlsLayout->addWidget(xstep, 1, 0, Qt::AlignLeft);
        controlsLayout->addWidget(xticks, 2, 0, Qt::AlignLeft);
        controlsLayout->addWidget(comboxstp, 1, 1, Qt::AlignLeft);
        controlsLayout->addWidget(comboxtks, 2, 1, Qt::AlignLeft);
        controlsLayout->addWidget(ystep, 1, 2, Qt::AlignLeft);
        controlsLayout->addWidget(yticks, 2, 2, Qt::AlignLeft);
        controlsLayout->addWidget(comboystp, 1, 3, Qt::AlignLeft);
        controlsLayout->addWidget(comboytks, 2, 3, Qt::AlignLeft);

        controlsLayout->addWidget(ctrlLines, 1, 4, 2, 6, Qt::AlignCenter | Qt::AlignHCenter);

        ctrlLinesLayout->addWidget(labelgrid, 0, 0, Qt::AlignCenter);
        ctrlLinesLayout->addWidget(gridOnOff, 1, 0, Qt::AlignTop | Qt::AlignCenter);
        ctrlLinesLayout->addWidget(state, 0, 1, Qt::AlignCenter);
        ctrlLinesLayout->addWidget(choose, 1, 1, Qt::AlignTop | Qt::AlignCenter);
        ctrlLinesLayout->addWidget(nrLinhasSup, 0, 2, Qt::AlignTop | Qt::AlignCenter);
        ctrlLinesLayout->addWidget(nrLinhasInf, 1, 2, Qt::AlignTop | Qt::AlignCenter);
        ctrlLinesLayout->addWidget(spinmax, 0, 3, Qt::AlignTop | Qt::AlignCenter);
        ctrlLinesLayout->addWidget(spinmin, 1, 3, Qt::AlignTop | Qt::AlignCenter);
        ctrlLinesLayout->addWidget(spinbinmax, 0, 3, Qt::AlignTop | Qt::AlignCenter);
        ctrlLinesLayout->addWidget(spinbinmin, 1, 3, Qt::AlignTop | Qt::AlignCenter);
        ctrlLinesLayout->addWidget(spinintmax, 0, 3, Qt::AlignTop | Qt::AlignCenter);
        ctrlLinesLayout->addWidget(spinintmin, 1, 3, Qt::AlignTop | Qt::AlignCenter);
        ctrlLinesLayout->addWidget(spin2dmax, 0, 3, Qt::AlignTop | Qt::AlignCenter);
        ctrlLinesLayout->addWidget(spin2dmin, 1, 3, Qt::AlignTop | Qt::AlignCenter);
        ctrlLinesLayout->addWidget(ScreenShot, 2, 2,1,2, Qt::AlignTop | Qt::AlignCenter);
        
        ctrlLinesLayout->addWidget(linesLbl, 0, 4, Qt::AlignCenter | Qt::AlignTop);
        ctrlLinesLayout->addWidget(lines, 0, 5, Qt::AlignCenter | Qt::AlignTop);

        ctrlLinesLayout->addWidget(labelshowall, 1, 4, Qt::AlignCenter | Qt::AlignHCenter);
        ctrlLinesLayout->addWidget(showall, 1, 5, Qt::AlignCenter | Qt::AlignHCenter);
        ctrlLinesLayout->addWidget(lblQuadDist, 2, 4, Qt::AlignCenter | Qt::AlignHCenter);
        ctrlLinesLayout->addWidget(quadDist, 2, 5, Qt::AlignCenter | Qt::AlignHCenter);
        ctrlLinesLayout->addWidget(lblNoColision, 3, 4, Qt::AlignCenter | Qt::AlignHCenter);
        ctrlLinesLayout->addWidget(noColision, 3, 5, Qt::AlignCenter | Qt::AlignHCenter);
        
        //        file_qbrw_wid->setMinimumSize(400,150);
        controlsLayout->addWidget(file_qbrw_wid, 1, 10, 2, 3, Qt::AlignCenter | Qt::AlignHCenter);
        controlsLayout->addWidget(expr_parse_wid, 1, 10, 2, 3, Qt::AlignCenter | Qt::AlignHCenter);
        controlsLayout->addWidget(lcg_brn_wid, 1, 10, 2, 3, Qt::AlignCenter | Qt::AlignHCenter);
        controlsLayout->addWidget(weie_ndcf_wid, 1, 10, 2, 3, Qt::AlignCenter | Qt::AlignHCenter);
        controlsLayout->addWidget(randomSourceChoice, 1, 13, 1, 1, Qt::AlignCenter | Qt::AlignHCenter);
        controlsLayout->addWidget(pDFA, 2, 13, 1, 1, Qt::AlignCenter | Qt::AlignHCenter);

        //        fileWidAnim->set
        //        controlsLayout->addWidget(numWalkslbl, 1, 10, Qt::AlignCenter | Qt::AlignHCenter);
        //        controlsLayout->addWidget(numstepslbl, 2, 10, Qt::AlignCenter | Qt::AlignHCenter);
        //        controlsLayout->addWidget(numwalks, 1, 11, Qt::AlignCenter | Qt::AlignHCenter);
        //        controlsLayout->addWidget(numsteps, 2, 11, Qt::AlignCenter | Qt::AlignHCenter);
        //        controlsLayout->addWidget(linCongTitle,1,12,1,2,Qt::AlignCenter | Qt::AlignHCenter);
        //        controlsLayout->addWidget(linCongInput,2,12,1,2,Qt::AlignCenter | Qt::AlignHCenter);
        controlsLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->addWidget(controlsW, 11, 0);
        gridLayout->addWidget(ThisOverLay, 0, 0, 10, 0, Qt::AlignCenter | Qt::AlignHCenter);
        gridLayout->addWidget(walks2d,0,0,10,0,Qt::AlignCenter|Qt::AlignHCenter);
        //        controlsLayout->addWidget(enableExpression,1,14,2,1,Qt::AlignCenter | Qt::AlignTop);
        //        controlsLayout->addWidget(allowExpression,2,14,1,2,Qt::AlignLeft | Qt::AlignTop);
        //        controlsLayout->addWidget(okNoLabel,2,14,1,1,Qt::AlignCenter | Qt::AlignBottom);
        rand_source = new RandomSource(centralwidget);
        GraphUi->setCentralWidget(centralwidget);
        retranslateUi(GraphUi);

        QMetaObject::connectSlotsByName(GraphUi);
    } // setupUi

    void retranslateUi(QMainWindow *GraphUi) {
        GraphUi->setWindowTitle("Ramdom Walk Studies");
    } // retranslateUi

};

namespace Ui {

    class GraphUi : public Ui_GraphUi {
    };
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHUI_H
