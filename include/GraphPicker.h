/* 
 * File:   GraphPicker.h
 * Author: fordem
 *
 * Created on July 12, 2013, 5:57 AM
 */

#ifndef GRAPHPICKER_H
#define	GRAPHPICKER_H
#include <qwt/qwt_plot_picker.h>
#include <qwt/qwt_plot_canvas.h>
#include <qwt/qwt_plot_curve.h>
#include <qwt/qwt_picker_machine.h>
#include <qwt/qwt_symbol.h>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_seriesitem.h>
#include <qwt/qwt_plot_curve.h>
#include <qt5/QtGui/qpainter.h>
#include <limits.h>
#include <float.h>
#include <QDebug>
#include <QLabel>
#include <QMouseEvent>

class GraphPicker : public QwtPlotPicker {
public:
    GraphPicker(QwtPlotCanvas * canvas);
    virtual ~GraphPicker();

    QLabel* getPointClicked() const {
        return pointClicked;
    }

    void renewPointSelected() {
        pointSelected = new QwtPlotCurve();
        pointSelected->setStyle(QwtPlotCurve::Dots);
        QwtSymbol * sym = new QwtSymbol(QwtSymbol::Ellipse);
        sym->setBrush(QColor(Qt::black));
        pointSelected->setSymbol(sym);
        pselected.setColor(QColor(Qt::black));
        pselected.setWidth(8);
        pointSelected->setPen(pselected);
        SweepWindow = new QwtPlotCurve();
        SweepWindow->setStyle(QwtPlotCurve::Lines);
        sym->setSize(12,12);
        SweepWindow->setSymbol(sym);
        pselected.setWidth(4);
        SweepWindow->setPen(pselected);
    }
protected:
    void widgetMousePressEvent(QMouseEvent *);
    void widgetMouseMoveEvent(QMouseEvent *);
//    void widgetKeyPressEvent(QKeyEvent*);
//    void widgetKeyReleaseEvent(QKeyEvent*);
    bool onlyShiftPressed;
    int oldx;
    QLabel * pointClicked;
    QwtPlotCurve * pointSelected;
    QwtPlotCurve * SweepWindow;
    QList<QLabel*>  SweepWindowIntersections;
    QPen pselected;
    int cInd, indexBest;
private:
};

#endif	/* GRAPHPICKER_H */

