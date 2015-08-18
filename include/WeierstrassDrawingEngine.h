/* 
 * File:   WeierstrassDrawingEngine.h
 * Author: fordem
 *
 * Created on June 16, 2015, 9:55 PM
 */

#ifndef WEIERSTRASSDRAWINGENGINE_H
#define	WEIERSTRASSDRAWINGENGINE_H
#include "IDrawingEngine.h"
#include <qwt_plot_curve.h>

template <class Type> class WeierstrassDrawingEngine : public IDrawingEngine<Type> {
public:
    void setNPlots(u_int32_t N);
    void setDataSet(IRWSet<Type>*);
    void setDataSet(IRWBd*);
    void addToPlot(IRWItem<Type>*);
    void setYandX(IRWItem<Type>* X, IRWItem<Type>* Y);
    void detach();
    void paintItem(u_int32_t);
    void paintAll();
    void paintFromTo(u_int32_t, u_int32_t);
    void setDataSet(IPolyfit*);
    WeierstrassDrawingEngine(QwtPlot* qwtPlot);
    virtual ~WeierstrassDrawingEngine();
    void paintQAverageDistance();
    virtual void setMaxForType(){
        this->max=std::numeric_limits<Type>::min();
    }
    virtual void setMinForType(){
        this->min=std::numeric_limits<Type>::max();
    }
private:
    QwtPlotCurve * curve;
    IRWItem<Type> * actualItemX;
    IRWItem<Type> * actualItemY;
};

template<class Type>void WeierstrassDrawingEngine<Type>::paintQAverageDistance() {
    return;
}

template<class Type> WeierstrassDrawingEngine<Type>::WeierstrassDrawingEngine(QwtPlot* qwtPlot) : IDrawingEngine<Type>(qwtPlot) {
    curve = NULL;
    actualItemX = NULL;
    actualItemY = NULL;
}

template<class Type> WeierstrassDrawingEngine<Type>::~WeierstrassDrawingEngine() {
    delete actualItemX;
    delete actualItemY;
}

template<class Type>void WeierstrassDrawingEngine<Type>::detach() {
    if (curve) {
        curve->detach();
    }
}

template<class Type>void WeierstrassDrawingEngine<Type>::paintAll() {
    if (actualItemX && actualItemY) {
        QVector<QPointF> d;
        for (uint64_t i = 0; i < actualItemY->getNpoints(); i++) {
            d.push_back(QPointF(actualItemX->getElement(i), actualItemY->getElement(i)));
        }
        QwtPointSeriesData * temp = new QwtPointSeriesData(d);
        if (!curve)
            curve = new QwtPlotCurve();
        curve->setPaintAttribute(QwtPlotCurve::PaintAttribute::ClipPolygons, true);
        curve->setRenderHint(QwtPlotCurve::RenderHint::RenderAntialiased, true);
        curve->setData(temp);
        curve->setStyle(QwtPlotCurve::Lines);
        QPen p;
        p.setColor(randomColor(qrand()));
        p.setWidth(2);
        curve->setPen(p);
        curve->attach(this->thisPlot);
        this->thisPlot->setAxisScale(QwtPlot::yLeft, curve->minYValue(), curve->maxYValue());
        this->thisPlot->setAxisScale(QwtPlot::xBottom, curve->minXValue(), curve->maxXValue());
        this->thisPlot->replot();
    }
}

template<class Type>void WeierstrassDrawingEngine<Type>::paintFromTo(u_int32_t, u_int32_t) {

}

template<class Type>void WeierstrassDrawingEngine<Type>::paintItem(u_int32_t) {

}

template<class Type>void WeierstrassDrawingEngine<Type>::setDataSet(IRWBd*) {
    return;
}

template<class Type>void WeierstrassDrawingEngine<Type>::setDataSet(IRWSet<Type>*) {
    return;
}

template<class Type>void WeierstrassDrawingEngine<Type>::setDataSet(IPolyfit*) {
    return;
}

template<class Type>void WeierstrassDrawingEngine<Type>::setNPlots(u_int32_t N) {
    return;
}

template<class Type>void WeierstrassDrawingEngine<Type>::setYandX(IRWItem<Type>* X, IRWItem<Type>* Y) {
    //    if (X->getNpoints() == Y->getNpoints()) {
    if (actualItemX) {
        delete actualItemX;
    }
    if (actualItemY) {
        delete actualItemY;
    }
    actualItemX = X;
    actualItemY = Y;
    //    }else{
    //        std::cout<<"Merda"<<std::endl;
    //    }
}

template<class Type>void WeierstrassDrawingEngine<Type>::addToPlot(IRWItem<Type>* irwi) {
    //    if (actualItem) {
    //        delete actualItem;
    //    }
    //    actualItem = irwi;
    //    QVector<QPointF> d;
    //    for (uint64_t i = 0; i < irwi->getNpoints(); i++) {
    //        d.push_back(QPointF(i, irwi->getElement(i)));
    //    }
    //    if (!curve)
    //        curve = new QwtPlotCurve();
    //
    //    QwtPointSeriesData * temp = new QwtPointSeriesData(d);
    //    curve->setPaintAttribute(QwtPlotCurve::PaintAttribute::ClipPolygons, true);
    //    curve->setRenderHint(QwtPlotCurve::RenderHint::RenderAntialiased, true);
    //    curve->setData(temp);
    //    curve->setStyle(QwtPlotCurve::Lines);
    //    QPen p;
    //    p.setColor(randomColor(qrand()));
    //    p.setWidth(2);
    //    curve->setPen(p);
    //    curve->attach(this->thisPlot);
    //    this->thisPlot->setAxisScale(QwtPlot::yLeft, curve->minYValue(), curve->maxYValue());
    //    this->thisPlot->setAxisScale(QwtPlot::xBottom, curve->minXValue(), curve->maxXValue());
}
#endif	/* WEIERSTRASSDRAWINGENGINE_H */

