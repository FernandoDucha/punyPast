/* 
 * File:   IDrawingEngine.h
 * Author: fordem
 *
 * Created on June 12, 2015, 7:13 PM
 */

#ifndef IDRAWINGENGINE_H
#define	IDRAWINGENGINE_H
#include <qwt_plot.h>
#include "IRWSet.h"
#include "IProbabilityBase.h"
#include <QObject>
#include "GeneralUsage.h"
#include "IRWBd.h"

template <class Type> class IDrawingEngine {
public:
    IDrawingEngine(QwtPlot * qwtPlot);
    virtual ~IDrawingEngine();

    virtual void attach(QwtPlot * qwtPlot) {
        thisPlot = qwtPlot;
    }

    //@Override
    virtual void setNPlots(u_int32_t N) = 0;
    //@Override
    virtual void setDataSet(IRWSet<Type>*) = 0;
    //@Override
    virtual void setDataSet(IRWBd*) = 0;
    //@Override
    virtual void addToPlot(IRWItem<Type>*) = 0;
    //@Override
    virtual void detach() = 0;
    //@Override
    virtual void paintItem(u_int32_t) = 0;
    //@Override
    virtual void paintAll() = 0;
    //@Override
    virtual void paintFromTo(u_int32_t, u_int32_t) = 0;
    //@Override
    virtual void setDataSet(IPolyfit*) = 0;
    //@Override
    virtual void paintQAverageDistance()=0;
    virtual void setMaxForType()=0;
    virtual void setMinForType()=0;
    
protected:
    Type min,max;
    u_int32_t Nplots;
    QwtPlot * thisPlot;
};

template <class Type> IDrawingEngine<Type>::IDrawingEngine(QwtPlot * qwtPlot) {
    thisPlot = qwtPlot;
    min = numeric_limits<Type>::max();
    max = numeric_limits<Type>::min();
}

template <class Type> IDrawingEngine<Type>::~IDrawingEngine() {
}
#endif	/* IDRAWINGENGINE_H */

