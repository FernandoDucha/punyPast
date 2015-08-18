/* 
 * File:   GraphMagnifier.h
 * Author: fordem
 *
 * Created on July 14, 2013, 7:37 PM
 */

#ifndef GRAPHMAGNIFIER_H
#define	GRAPHMAGNIFIER_H
#include <qwt_plot_magnifier.h>
#include <qwt_plot_canvas.h>

class GraphMagnifier : public QwtPlotMagnifier {
public:
    GraphMagnifier(QwtPlotCanvas * canvas);
    virtual ~GraphMagnifier();
    int deltaold;
    double scale;
    int scalecount;
protected:
//   void widgetMouseMoveEvent(QMouseEvent*);
//   void widgetKeyPressEvent(QKeyEvent *);
private:
};

#endif	/* GRAPHMAGNIFIER_H */

