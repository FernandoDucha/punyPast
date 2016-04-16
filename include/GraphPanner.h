/* 
 * File:   GraphPanner.h
 * Author: fordem
 *
 * Created on July 16, 2013, 5:58 AM
 */

#ifndef GRAPHPANNER_H
#define	GRAPHPANNER_H
#include <qwt/qwt_plot_panner.h>
class GraphPanner: public QwtPlotPanner  {
public:
    GraphPanner(QwtPlotCanvas *);
    virtual ~GraphPanner();
private:

};

#endif	/* GRAPHPANNER_H */

