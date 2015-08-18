/* 
 * File:   QPointFSLC.h
 * Author: fordem
 *
 * Created on August 15, 2015, 5:49 PM
 */

#ifndef QPOINTFSLC_H
#define	QPOINTFSLC_H
#include "SweepLine.h"
#include "QPollarF.h"

class QPointFSLC {
public:
    QPointFSLC(QPollarF*, int n);
    virtual ~QPointFSLC();

    bool getStatus() {
        EventQueue Eq(pn);
        SweepLine SL(pn);
        Event *e;
        SLseg * s;

        // This loop processes all events in the sorted queue
        // Events are only left or right vertices since
        // No new events will be added (an intersect => Done)
        while ((e = Eq.next())) { // while there are events
            if (e->type == LEFT) { // process a left vertex
                s = SL.add(e); // add it to the sweep line
                if (SL.intersect(s, s->above)) {
                    return false; // Pn is NOT simple
                }
                if (SL.intersect(s, s->below)) {
                    return false; // Pn is NOT simple
                }
            } 
            else { // process a right vertex
                s = e->otherEnd->seg;
                if (SL.intersect(s->above, s->below)) {
                    return false; // Pn is NOT simple
                }
                SL.remove(s); // remove it from the sweep line
            }
        }

        return true;
    }
private:
    bool status;
    Polygon pn;
};

inline QPointFSLC::QPointFSLC(QPollarF* input, int n) : pn(n) {
    int a = 0;
    for (int i = 0; i < n; i++) {
        pn.V[a].x = input[i].rx();
        pn.V[a].y = input[i].ry();
        a++;
    }

}

inline QPointFSLC::~QPointFSLC() {
}
#endif	/* QPOINTFSLC_H */

