/* 
 * File:   BinDrawingEngine.h
 * Author: fordem
 *
 * Created on June 13, 2015, 11:37 PM
 */

#ifndef BINDRAWINGENGINE_H
#define	BINDRAWINGENGINE_H
#include "IDrawingEngine.h"
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>

template <class Type> class BinDrawingEngine : public IDrawingEngine<Type> {
public:
    BinDrawingEngine(QwtPlot * plot);
    virtual ~BinDrawingEngine();
    virtual void setNPlots(u_int32_t N);
    virtual void setDataSet(IRWSet<Type>*);
    virtual void setDataSet(IRWBd*);
    virtual void addToPlot(IRWItem<Type>*);
    virtual void addToPlot(IRWItem<Type>*, QColor);

    virtual void detach();
    virtual void paintItem(u_int32_t);
    virtual void paintAll();
    virtual void paintFromTo(u_int32_t, u_int32_t);

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
    IRWItem<Type> * noiseLine;
    QwtPlotCurve * NoiseCurve;
    IRWSet<Type> * dataSet;
};

template <class Type> void BinDrawingEngine<Type>::paintQAverageDistance() {
    return;
}

template <class Type> BinDrawingEngine<Type>::BinDrawingEngine(QwtPlot * plot) : IDrawingEngine<Type>(plot) {
    noiseLine = NULL;
    NoiseCurve = new QwtPlotCurve();
    dataSet = NULL;
}

template <class Type> BinDrawingEngine<Type>::~BinDrawingEngine() {
    delete noiseLine;
}

template <class Type> void BinDrawingEngine<Type>::paintItem(u_int32_t i) {
    *noiseLine = *dataSet->getElement(i);
    QVector<QPointF> d;
    for (unsigned int k = 0; k < noiseLine->getNpoints(); k++) {
        d.push_back(QPointF(k, noiseLine->getElement(k)));
    }
    QwtPointSeriesData * temp = new QwtPointSeriesData(d);
    QPen p;
    p.setWidth(2);
    p.setColor(QColor(Qt::cyan));
    NoiseCurve->setPen(p);
    NoiseCurve->setData(temp);
    NoiseCurve->setStyle(QwtPlotCurve::Lines);
    NoiseCurve->attach(this->thisPlot);
    this->thisPlot->setAxisScale(QwtPlot::yLeft, NoiseCurve->minYValue(), NoiseCurve->maxYValue());
    this->thisPlot->setAxisScale(QwtPlot::xBottom, 0, noiseLine->getNpoints());
    this->thisPlot->replot();
}

/**
 * If this class is anything else other than BDDataPointsDrawingEngine,BDBinDrawingEngine, this method has no functionality.
 * @param 
 */
template <class Type> void BinDrawingEngine<Type>::setDataSet(IRWBd*) {
    return;
}

template <class Type> void BinDrawingEngine<Type>::detach() {
    if (NoiseCurve) {
        NoiseCurve->detach();
    }
    delete noiseLine;
    noiseLine = NULL;
}

template <class Type> void BinDrawingEngine<Type>::setNPlots(u_int32_t N) {
    this->Nplots = N;
}

template <class Type> void BinDrawingEngine<Type>::paintFromTo(u_int32_t beg, u_int32_t end) {
    if (noiseLine) {
        delete noiseLine;
    }
    noiseLine = new RWVec<Type>();
    for (int i = beg; i < end; i++) {
        *noiseLine += *dataSet->getElement(i);
    }
    QVector<QPointF> d;
    for (unsigned int i = 0; i < noiseLine->getNpoints(); i++) {
        d.push_back(QPointF(i, noiseLine->getElement(i)));
    }
    QwtPointSeriesData * temp = new QwtPointSeriesData(d);
    QPen p;
    p.setWidth(2);
    p.setColor(QColor(Qt::cyan));
    NoiseCurve->setPen(p);
    NoiseCurve->setData(temp);
    NoiseCurve->setStyle(QwtPlotCurve::Lines);
    NoiseCurve->attach(this->thisPlot);
    this->thisPlot->setAxisScale(QwtPlot::yLeft, NoiseCurve->minYValue(), NoiseCurve->maxYValue());
    this->thisPlot->setAxisScale(QwtPlot::xBottom, 0, noiseLine->getNpoints());
    this->thisPlot->replot();

}

template <class Type> void BinDrawingEngine<Type>::setDataSet(IRWSet<Type>* irws) {
    if (dataSet != NULL) {
        delete dataSet;
    }
    setNPlots(irws->getSize());
    dataSet = irws;

}
template <class Type> void BinDrawingEngine<Type>::addToPlot(IRWItem<Type>* irwi, QColor){
    addToPlot(irwi);
}

template <class Type> void BinDrawingEngine<Type>::addToPlot(IRWItem<Type>* irwi) {
    *noiseLine += *irwi;
    QVector<QPointF> d;
    for (unsigned int i = 0; i < noiseLine->getNpoints(); i++) {
        d.push_back(QPointF(i, noiseLine->getElement(i)));
    }
    QwtPointSeriesData * temp = new QwtPointSeriesData(d);
    QPen p;
    p.setWidth(2);
    p.setColor(QColor(Qt::cyan));
    NoiseCurve->setPen(p);
    NoiseCurve->setData(temp);
    NoiseCurve->setStyle(QwtPlotCurve::Lines);
    NoiseCurve->attach(this->thisPlot);
    this->thisPlot->setAxisScale(QwtPlot::yLeft, NoiseCurve->minYValue(), NoiseCurve->maxYValue());
    this->thisPlot->setAxisScale(QwtPlot::xBottom, 0, noiseLine->getNpoints());
    this->thisPlot->replot();
}

template <class Type> void BinDrawingEngine<Type>::paintAll() {
    paintFromTo(0, this->Nplots);
}


#endif	/* BINDRAWINGENGINE_H */

