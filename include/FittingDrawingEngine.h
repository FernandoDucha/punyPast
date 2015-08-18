/* 
 * File:   FittingDrawingEngine.h
 * Author: fordem
 *
 * Created on June 15, 2015, 4:58 PM
 */

#ifndef FITTINGDRAWINGENGINE_H
#define	FITTINGDRAWINGENGINE_H
#include "IDrawingEngine.h"
#include "IPolyfit.h"
#include <qwt_plot_curve.h>
#include <qwt_legend.h>

template <class Type>class FittingDrawingEngine : public IDrawingEngine<Type> {
public:
    FittingDrawingEngine(QwtPlot * plot);
    virtual ~FittingDrawingEngine();
    virtual void addToPlot(IRWItem<Type>*);
    virtual void detach();
    virtual void paintFromTo(u_int32_t, u_int32_t);
    virtual void paintAll();
    virtual void paintItem(u_int32_t);
    virtual void setDataSet(IRWBd*);
    virtual void setNPlots(u_int32_t);
    virtual void setDataSet(IRWSet<Type>*);
    virtual void paintQAverageDistance();
    virtual void setMaxForType(){
        this->max=std::numeric_limits<Type>::min();
    }
    virtual void setMinForType(){
        this->min=std::numeric_limits<Type>::max();
    }
    /**
     * For all classes other than Fitting*DrawingEngine BDFitting*DrawingEngine, this method has no use.
     * @param poly
     */
    virtual void setDataSet(IPolyfit* poly);
private:
    QwtPlotCurve * fittingCurve, *samples;
    IPolyfit * thisPoly;
};
template <class Type> inline void FittingDrawingEngine<Type>::paintQAverageDistance(){
    return;
}

template <class Type> inline void FittingDrawingEngine<Type>::setNPlots(u_int32_t) {
    return;
}

template <class Type> inline void FittingDrawingEngine<Type>::setDataSet(IPolyfit* poly) {
    this->thisPoly = poly;
}

template <class Type> inline FittingDrawingEngine<Type>::FittingDrawingEngine(QwtPlot * plot) : IDrawingEngine<Type>(plot) {
    thisPoly = NULL;
    fittingCurve = NULL;
    samples = NULL;
}

template <class Type> inline FittingDrawingEngine<Type>::~FittingDrawingEngine() {
    if (thisPoly)
        delete thisPoly;
}

template <class Type>void FittingDrawingEngine<Type>::addToPlot(IRWItem<Type>*) {
    return;
}

template <class Type>void FittingDrawingEngine<Type>::detach() {
    if (fittingCurve) {
        fittingCurve->detach();
    }
    if (samples) {
        samples->detach();
    }
}

template <class Type>void FittingDrawingEngine<Type>::paintFromTo(u_int32_t, u_int32_t) {
    return;
}

template <class Type>void FittingDrawingEngine<Type>::paintAll() {
    if (thisPoly) {
        double a, b, SSE;
        a = thisPoly->getFit()->getCoef(1);
        b = thisPoly->getFit()->getCoef(0);
        SSE = thisPoly->getSSE();
        double *x, *y;
        x = thisPoly->getSamplesX();
        y = thisPoly->getSamplesY();
        if (!samples&&!fittingCurve) {
            samples = new QwtPlotCurve();
            fittingCurve = new QwtPlotCurve();
        }
        QVector<QPointF> ptf, ptfc;
        for (uint64_t i = 0; i < thisPoly->getN(); i++) {
            ptf.push_back(QPointF(x[i], y[i]));
            ptfc.push_back(QPointF(x[i], b + x[i] * a));
        }
        QwtPointSeriesData * temp = new QwtPointSeriesData(ptf);
        samples->setData(temp);
        samples->setStyle(QwtPlotCurve::Dots);
        QPen p;
        p.setColor(QColor(Qt::black));
        p.setWidth(4);
        samples->setPen(p);
        samples->attach(this->thisPlot);
        QwtPointSeriesData * temp1 = new QwtPointSeriesData(ptfc);
        fittingCurve->setData(temp1);
        fittingCurve->setStyle(QwtPlotCurve::Lines);
        p.setColor(QColor(Qt::red));
        p.setWidth(2);
        fittingCurve->setPen(p);
        fittingCurve->attach(this->thisPlot);
        samples->setTitle("Samples");
        QString fitstr = "Fitting:\n";
        fitstr += "y=a*x+b\n";
        fitstr += "a= " + QString::number(a);
        fitstr += "\nb= " + QString::number(b);
        fitstr += "\nSSE= " + QString::number(SSE);
        fittingCurve->setTitle(fitstr);
        fittingCurve->setItemAttribute(QwtPlotCurve::Legend, true);
        fittingCurve->setLegendAttribute(QwtPlotCurve::LegendShowLine, true);
        QwtLegend * leg = new QwtLegend();
        this->thisPlot->insertLegend(leg, QwtPlot::RightLegend, -.5);
        this->thisPlot->setAxisScale(QwtPlot::yLeft, samples->minYValue(), samples->maxYValue());
        this->thisPlot->setAxisScale(QwtPlot::xBottom, samples->minXValue(), samples->maxXValue());
        this->thisPlot->replot();
    }
}

template <class Type>void FittingDrawingEngine<Type>::paintItem(u_int32_t) {
    return;
}

template <class Type>void FittingDrawingEngine<Type>::setDataSet(IRWBd*) {
    return;
}

template <class Type>void FittingDrawingEngine<Type>::setDataSet(IRWSet<Type>*) {
    return;
}

#endif	/* FITTINGDRAWINGENGINE_H */

