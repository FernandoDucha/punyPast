/* 
 * File:   BDDataPointsDrawingEngine.h
 * Author: fordem
 *
 * Created on June 13, 2015, 5:44 PM
 */

#ifndef BDDATAPOINTSDRAWINGENGINE_H
#define	BDDATAPOINTSDRAWINGENGINE_H

#include "IDrawingEngine.h"
#include <qwt_plot_curve.h>
#include <qwt_plot.h>

template <class Type> class BDDataPointsDrawingEngine : public IDrawingEngine<Type> {
public:
    BDDataPointsDrawingEngine(QwtPlot * plot);
    virtual ~BDDataPointsDrawingEngine();
    virtual void setNPlots(u_int32_t N);
    virtual void setDataSet(IRWSet<Type>*);
    virtual void setDataSet(IRWBd*);
    virtual void addToPlot(IRWItem<Type>*);
    virtual void detach();
    virtual void paintItem(u_int32_t);
    virtual void paintAll();
    virtual void paintFromTo(u_int32_t, u_int32_t);
    virtual void addToPlot(IRWItem<Type>*, QColor);

    /**
     * For all classes other than Fitting*DrawingEngine BDFitting*DrawingEngine, this method has no use.
     * @param poly
     */
    virtual void setDataSet(IPolyfit*) {
        return;
    }
    virtual void paintQAverageDistance();

    virtual void setMaxForType() {
        this->max = std::numeric_limits<Type>::min();
    }

    virtual void setMinForType() {
        this->min = std::numeric_limits<Type>::max();
    }
private:
    IRWBd * thisBD;
    QVector<QColor> colors;
    QMap<u_int32_t, QwtPlotCurve*> curves;
    QwtPlotCurve * quadraticCurve;
};

template <class Type> void BDDataPointsDrawingEngine<Type>::paintQAverageDistance() {
    auto beg = curves.begin();
    auto end = curves.end();
    IRWItem<Type> * sum = new RWDp<double>();
    int visible = 0;
    for (; beg != end; beg++) {
        if (curves[beg.key()]->plot()) {
            RWDp<Type> dp = thisBD->selectDpItem(beg.key());
            *sum += *dp.power(2);
            visible++;
        }
    }
    *sum = *dynamic_cast<RWDp<double> *> (sum) / visible;
    IRWItem<double> * t = sum->power(0.5);
    *sum = *t;
    delete t;
    QVector<QPointF> d;
    for (uint64_t k = 0; k < sum->getNpoints(); k++) {
        d.push_back(QPointF(k, sum->getElement(k)));
    }
    QwtPointSeriesData * temp = new QwtPointSeriesData(d);
    QPen p;
    p.setStyle(Qt::DashDotLine);
    p.setWidth(6);
    if (!quadraticCurve) {
        quadraticCurve = new QwtPlotCurve();
        quadraticCurve->setPaintAttribute(QwtPlotCurve::PaintAttribute::ClipPolygons, true);
        quadraticCurve->setRenderHint(QwtPlotCurve::RenderHint::RenderAntialiased, true);
        p.setColor(randomColor(qrand()));
        quadraticCurve->setPen(p);
        quadraticCurve->setStyle(QwtPlotCurve::Lines);
    } else {
        quadraticCurve->setPen(p);
    }

    quadraticCurve->setData(temp);
    quadraticCurve->attach(this->thisPlot);
    this->thisPlot->replot();
    delete sum;
}

template <class Type> BDDataPointsDrawingEngine<Type>::~BDDataPointsDrawingEngine() {
}

template <class Type> void BDDataPointsDrawingEngine<Type>::paintItem(u_int32_t i) {
    RWDp<Type> a = thisBD->selectDpItem(i);

    QVector<QPointF> d;
    for (uint64_t k = 0; k < a.getNpoints(); k++) {
        d.push_back(QPointF(k, a.getElement(k)));
    }
    QwtPointSeriesData * temp = new QwtPointSeriesData(d);
    QwtPlotCurve * c = new QwtPlotCurve();
    c->setPaintAttribute(QwtPlotCurve::PaintAttribute::ClipPolygons, true);
    c->setRenderHint(QwtPlotCurve::RenderHint::RenderAntialiased, true);
    c->setData(temp);
    c->setStyle(QwtPlotCurve::Lines);
    QPen p;
    p.setColor(colors.at(i));
    p.setWidth(2);
    c->setPen(p);
    c->attach(this->thisPlot);
    curves.insert(i, c);
}

/**
 * If this class is anything else other than BDDataPointsDrawingEngine,BDBinDrawingEngine, this method has no functionality.
 * @param 
 */
template <class Type> void BDDataPointsDrawingEngine<Type>::setDataSet(IRWBd* db) {
    thisBD = db;
    this->Nplots = db->getNWalks();
    colors.clear();
    for (int i = 0; i < this->Nplots; i++) {
        colors.push_back(randomColor(qrand()));
    }
}

template <class Type> void BDDataPointsDrawingEngine<Type>::detach() {
    auto beg = curves.begin();
    auto end = curves.begin();
    while (curves[beg.key()] != NULL) {
        curves[beg.key()]->detach();
        beg++;
    }
    curves.clear();
}

template <class Type> void BDDataPointsDrawingEngine<Type>::setNPlots(u_int32_t N) {
    this->Nplots = N;
    colors.clear();
    for (int i = 0; i < this->Nplots; i++) {
        colors.push_back(randomColor(qrand()));
    }
}

template <class Type> void BDDataPointsDrawingEngine<Type>::paintFromTo(u_int32_t beg, u_int32_t end) {
    Type max = numeric_limits<Type>::min();
    Type min = numeric_limits<Type>::max();
    for (int i = 0; i < beg; i++) {
        if (curves.contains(i) && curves.value(i)->plot() != NULL) {
            curves.value(i)->detach();
        }
    }

    Type x = thisBD->getWalkS();
    for (int i = beg; i < end; i++) {
        Type maxt = 0, mint = 0;
        if (!curves.contains(i)) {
            paintItem(i);
            maxt = curves.value(i)->maxYValue();
            mint = curves.value(i)->minYValue();
        } else if (curves.value(i)->plot() == NULL) {
            curves.value(i)->attach(this->thisPlot);
            maxt = curves.value(i)->maxYValue();
            mint = curves.value(i)->minYValue();
        } else {
            maxt = curves.value(i)->maxYValue();
            mint = curves.value(i)->minYValue();
        }
        if (maxt > max) {
            max = maxt;
        }
        if (mint < min) {
            min = mint;
        }
    }
    for (int i = end; curves.contains(i); i++) {
        if (curves.value(i)->plot() != NULL) {
            curves.value(i)->detach();
        }
    }
    this->thisPlot->setAxisScale(QwtPlot::yLeft, min, max);
    this->thisPlot->setAxisScale(QwtPlot::xBottom, 0, x);
}

/**
 * If this method is called in any Bd Drawing engine it wont matter at all. NO EFFECt.
 * @param irws
 */
template <class Type> void BDDataPointsDrawingEngine<Type>::setDataSet(IRWSet<Type>*) {
    return;

}

template <class Type> BDDataPointsDrawingEngine<Type>::BDDataPointsDrawingEngine(QwtPlot * plot) : IDrawingEngine<Type>(plot) {
    thisBD = NULL;
    quadraticCurve = NULL;
}

template <class Type> void BDDataPointsDrawingEngine<Type>::addToPlot(IRWItem<Type>* irwi) {
    addToPlot(irwi,randomColor(qrand()));
}

template <class Type> void BDDataPointsDrawingEngine<Type>::addToPlot(IRWItem<Type>* irwi, QColor color) {
    Type max = numeric_limits<Type>::min();
    Type min = numeric_limits<Type>::max();
    Type x = irwi->getNpoints();
    bool flag = false;
    for (int i = 0;; i++) {
        Type maxt = numeric_limits<Type>::min(), mint = numeric_limits<Type>::max();
        if (curves[i] == NULL) {
            x = irwi->getNpoints();
            QVector<QPointF> d;
            for (uint64_t i = 0; i < irwi->getNpoints(); i++) {
                d.push_back(QPointF(i, irwi->getElement(i)));
            }
            QwtPointSeriesData * temp = new QwtPointSeriesData(d);
            QwtPlotCurve * c = new QwtPlotCurve();
            c->setPaintAttribute(QwtPlotCurve::PaintAttribute::ClipPolygons, true);
            c->setRenderHint(QwtPlotCurve::RenderHint::RenderAntialiased, true);
            c->setData(temp);
            c->setStyle(QwtPlotCurve::Lines);
            QPen p;
            p.setColor(color);
            p.setWidth(2);
            c->setPen(p);
            c->attach(this->thisPlot);
            curves.insert(i, c);
            maxt = c->maxYValue();
            mint = c->minYValue();
            flag = true;
        } else if (curves.value(i)->plot()) {
            maxt = curves.value(i)->maxYValue();
            mint = curves.value(i)->minYValue();
        }
        if (maxt > max) {
            max = maxt;
        }
        if (mint < min) {
            min = mint;
        }
        if (flag) break;
    }
    this->thisPlot->setAxisScale(QwtPlot::yLeft, min, max);
    this->thisPlot->setAxisScale(QwtPlot::xBottom, 0, x);
}

template <class Type> void BDDataPointsDrawingEngine<Type>::paintAll() {
    paintFromTo(0, this->Nplots);
}

#endif	/* BDDATAPOINTSDRAWINGENGINE_H */

