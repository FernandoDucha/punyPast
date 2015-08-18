#ifndef VEdge_h
#define VEdge_h

#include "QPollarF.h"
#include <iostream>
#define SMALL_NUM   0.00000001 // anything that avoids division overflow
// dot product (3D) which allows vector operations in arguments
#define SMALL 0.00000001
#include <math.h>
#include <iostream>
#define dot(u,v)   ((u).rx() * (v).rx() + (u).ry() * (v).ry())
#define perp(u,v)  ((u).rx() * (v).ry() - (u).ry() * (v).rx())  // perp product  (2D)
#define norm(v)     sqrt(dot(v,v))
//#define dist(u,v)   norm(u-v)
/*
        A class that stores an edge in Voronoi diagram

        start		: pointer to start point
        end			: pointer to end point
        left		: pointer to Voronoi place on the left side of edge
        right		: pointer to Voronoi place on the right side of edge

        neighbour	: some edges consist of two parts, so we add the pointer to another part to connect them at the end of an algorithm

        direction	: directional vector, from "start", points to "end", normal of |left, right|
        f, g		: directional coeffitients satisfying equation y = f*x + g (edge lies on this line)
 */
//using namespace std;

class VEdge {
public:
    QPollarF start;
    QPollarF end;

    /*
            Constructor of the class

            s		: pointer to start
            a		: pointer to left place
            b		: pointer to right place
     */
    VEdge(){
        
    }
    VEdge(QPollarF s, QPollarF e) {
        start = s;
        end = e;
        start.setIndice(s.getIndice());
        end.setIndice(e.getIndice());

    }

    /*
            Destructor of the class
            direction belongs only to the current edge, other pointers can be shared by other edges
     */

    ~VEdge() {
        //        delete direction;
    }
    // Copyright 2001 softSurfer, 2012 Dan Sunday
    // This code may be freely used and modified for any purpose
    // providing that this copyright notice is included with it.
    // SoftSurfer makes no warranty for this code, and cannot be held
    // liable for any real or imagined damage resulting from its use.
    // Users of this code must verify correctness for their application.
    // intersect2D_2Segments(): find the 2D intersection of 2 finite segments
    //    Input:  two finite segments S1 and S2
    //    Output: *I0 = intersect point (when it exists)
    //            *I1 =  endpoint of intersect segment [I0,I1] (when it exists)
    //    Return: 0=disjoint (no intersect)
    //            1=intersect  in unique point I0
    //            2=overlap  in segment from I0 to I1

    static int intersect2D_2Segments(VEdge S1, VEdge S2, QPollarF& I0, QPollarF& I1) {
        QPollarF u;
        subQPollarF(S1.end, S1.start, u);
        QPollarF v;
        subQPollarF(S2.end, S2.start, v);
        QPollarF w;
        subQPollarF(S1.start, S2.start, w);

        float D = perp(u, v);

        // test if  they are parallel (includes either being a point)
        if (fabs(D) < SMALL_NUM) { // S1 and S2 are parallel
            if (perp(u, w) != 0 || perp(v, w) != 0) {
                return 0; // they are NOT collinear
            }
            // they are collinear or degenerate
            // check if they are degenerate  points
            float du = dot(u, u);
            float dv = dot(v, v);
            if (du == 0 && dv == 0) { // both segments are points
                if (S1.start != S2.start) // they are distinct  points
                    return 0;
                I0 = S1.start; // they are the same point
                return 3;
            }
            if (du == 0) { // S1 is a single point
                if (inSegment(S1.start, S2) == 0) // but is not in S2
                    return 0;
                I0 = S1.start;
                return 3;
            }
            if (dv == 0) { // S2 a single point
                if (inSegment(S2.start, S1) == 0) // but is not in S1
                    return 0;
                I0 = S2.start;
                return 3;
            }
            // they are collinear segments - get  overlap (or not)
            float t0, t1; // endpoints of S1 in eqn for S2
            QPollarF w2;
            subQPollarF(S1.end, S2.start, w2);
            if (v.rx() != 0) {
                t0 = w.rx() / v.rx();
                t1 = w2.rx() / v.rx();
            } else {
                t0 = w.ry() / v.ry();
                t1 = w2.ry() / v.ry();
            }
            if (t0 > t1) { // must have t0 smaller than t1
                float t = t0;
                t0 = t1;
                t1 = t; // swap if not
            }
            if (t0 > 1 || t1 < 0) {
                return 0; // NO overlap
            }
            t0 = t0 < 0 ? 0 : t0; // clip to min 0
            t1 = t1 > 1 ? 1 : t1; // clip to max 1
            if (t0 == t1) { // intersect is a point
                QPollarF a;
                a.setX(v.rx() * t0);
                a.setY(v.ry() * t0);
                sumQPollarF(S2.start, a, I0);
                return 1;
            }

            // they overlap in a valid subsegment
            QPollarF a;
            a.setX(v.rx() * t0);
            a.setY(v.ry() * t0);
            sumQPollarF(S2.start, a, I0);

            QPollarF b;
            b.setX(v.rx() * t1);
            b.setY(v.ry() * t1);
            sumQPollarF(S2.start, b, I1);

            return 2;
        }

        // the segments are skew and may intersect in a point
        // get the intersect parameter for S1
        float sI = perp(v, w) / D;
        if (sI < 0 || sI > 1) // no intersect with S1
            return 0;

        // get the intersect parameter for S2
        float tI = perp(u, w) / D;
        if (tI < 0 || tI > 1) // no intersect with S2
            return 0;
        QPollarF c;
        c.setX(u.rx() * sI);
        c.setY(u.ry() * sI);
        sumQPollarF(S1.start, c, u);
//        I0 = S1.start + sI * u; // compute S1 intersect point
        return 1;
    }

    static int inSegment(QPollarF P, VEdge S) {
        if (S.start.rx() != S.end.rx()) { // S is not  vertical
            if (S.start.rx() <= P.rx() && P.rx() <= S.end.rx())
                return 1;
            if (S.start.rx() >= P.rx() && P.rx() >= S.end.rx())
                return 1;
        } else { // S is vertical, so test y  coordinate
            if (S.start.ry() <= P.ry() && P.ry() <= S.end.ry())
                return 1;
            if (S.start.ry() >= P.ry() && P.ry() >= S.end.ry())
                return 1;
        }
        return 0;
    }

    static float dist_Point_to_Segment(QPollarF P, VEdge S) {
        QPollarF v;
        subQPollarF(S.end, S.start, v);
        QPollarF w;
        subQPollarF(P, S.start, w);
        double c1 = dot(w, v);
        if (c1 <= 0)
            return P.distQPollarF( S.start);

        double c2 = dot(v, v);
        if (c2 <= c1)
            return P.distQPollarF( S.start);

        double b = c1 / c2;
        QPollarF Pb;
        v.setX(v.rx() * b);
        v.setY(v.ry() * b);
        sumQPollarF(v, S.start, Pb);
        return P.distQPollarF(Pb);
    }

    //    static QPollarF isInsideBox(VEdge & v, double w, double h, int & EndStart, int & EdgeCode) {
    //        QPollarF a(0, 0);
    //        QPollarF b(w, 0);
    //        QPollarF c(w, h);
    //        QPollarF d(0, h);
    //        VEdge bottom(&a, v.left, v.right);
    //        bottom.end = &b;
    //        VEdge left(&d, v.left, v.right);
    //        left.end = &a;
    //        VEdge right(&b, v.left, v.right);
    //        right.end = &c;
    //        VEdge top(&c, v.left, v.right);
    //        top.end = &d;
    //        QPollarF i1(-1, -1), i2(0, 0);
    //        int r1 = intersect2D_2Segments(v, bottom, &i1, &i2);
    //        int r2 = intersect2D_2Segments(v, left, &i1, &i2);
    //        int r3 = intersect2D_2Segments(v, right, &i1, &i2);
    //        int r4 = intersect2D_2Segments(v, top, &i1, &i2);
    //        if (r1 | r2 | r3 | r4) {
    //
    //            if (r1) {
    //                EdgeCode = 0;
    //            } else if (r2) {
    //                EdgeCode = 1;
    //            } else if (r3) {
    //                EdgeCode = 2;
    //            } else {
    //                EdgeCode = 3;
    //            }
    //            QPollarF res1 = *v.start;
    //            QPollarF res2 = *v.end;
    //            //            QPollarF T1 = res1 - i1;
    //            //            QPollarF T2 = res2 - i1;
    //            //            T1.x = T1.x / w;
    //            //            T1.y = T1.y / h;
    //            //            T2.x = T2.x / w;
    //            //            T2.y = T2.y / h;
    //
    //            res1.x = res1.x / w;
    //            res1.y = res1.y / h;
    //            res2.x = res2.x / w;
    //            res2.y = res2.y / h;
    //            //            if (((fabs(T1.x) < SMALL) && (res2.y < 0 || res2.y > 1)) ||
    //            //                    ((fabs(T1.y) < SMALL) && (res2.x < 0 || res2.x > 1))) {
    //            //                cout << v.start->x << " " << v.start->y << " " << v.end->x << " " << v.end->y << endl;
    //            //                cout << i1.x << " " << i1.y << endl;
    //            //                EndStart = -1;
    //            //                return QPollarF(-1, -1);
    //            //            }
    //            //            if (((fabs(T2.x) < SMALL) && (res1.y < 0 || res1.y > 1)) ||
    //            //                    ((fabs(T2.y) < SMALL) && (res1.x < 0 || res1.x > 1))) {
    //            //                cout << v.start->x << " " << v.start->y << " " << v.end->x << " " << v.end->y << endl;
    //            //                cout << i1.x << " " << i1.y << endl;
    //            //                EndStart = -1;
    //            //                return QPollarF(-1, -1);
    //            //            }
    //            if ((res1.x <= 0 || res1.x >= 1) || (res1.y <= 0 || res1.y >= 1)) {
    //                EndStart = 0;
    //                return i1;
    //            }
    //            if ((res2.x <= 0 || res2.x >= 1) || (res2.y <= 0 || res2.y >= 1)) {
    //                EndStart = 1;
    //                return i1;
    //            }
    //            if ((fabs(res1.x) < SMALL || fabs(1 - res1.x) < SMALL) || (fabs(res1.y) < SMALL || fabs(1 - res1.y) < SMALL)) {
    //                EndStart = 0;
    //                return i1;
    //            }
    //            if ((fabs(res2.x) < SMALL || fabs(1 - res2.x) < SMALL) || (fabs(res2.y) < SMALL || fabs(1 - res2.y) < SMALL)) {
    //                EndStart = 1;
    //                return i1;
    //            }
    //        }
    //    }
    bool operator==(VEdge & a){
        if(this->end==a.end&&this->start==a.start){
            return true; 
        }else if(this->end==a.start&&this->start==a.end){
            return true;
        }else if(this->start==a.end&&this->end==a.start){
            return true;
        }
        else{
            return false;
        }
    }
};

#endif
