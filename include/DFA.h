/* 
 * File:   DFAAnalysis.h
 * Author: fordem
 *
 * Created on June 6, 2015, 5:52 PM
 * programa baseado em http://physionet.org/physiotools/dfa/dfa.c
 * This method was first proposed in:
  Peng C-K, Buldyrev SV, Havlin S, Simons M, Stanley HE, Goldberger AL. Mosaic
  organization of DNA nucleotides. Phys Rev E 1994;49:1685-1689.  [Available
  on-line at http://prola.aps.org/abstract/PRE/v49/i2/p1685_1]

A detailed description of the algorithm and its application to physiologic
signals can be found in:
  Peng C-K, Havlin S, Stanley HE, Goldberger AL. Quantification of scaling
  exponents and crossover phenomena in nonstationary heartbeat time series.
  Chaos 1995;5:82-87. [Abstract online at http://www.ncbi.nlm.nih.gov/entrez/-
   query.fcgi?cmd=Retrieve&db=PubMed&list_uids=11538314&dopt=Abstract]

If you use this program in support of published research, please include a
citation of at least one of the two references above, as well as the standard
citation for PhysioNet:
  Goldberger AL, Amaral LAN, Glass L, Hausdorff JM, Ivanov PCh, Mark RG,
  Mietus JE, Moody GB, Peng CK, Stanley HE.  PhysioBank, PhysioToolkit, and
  Physionet: Components of a New Research Resource for Complex Physiologic
  Signals. Circulation 101(23):e215-e220 [Circulation Electronic Pages;
  http://circ.ahajournals.org/cgi/content/full/101/23/e215]; 2000 (June 13). 
 */

#ifndef DFA_H
#define DFA_H
#include "IRWItem.h"
#include "IRWSet.h"
#include "LinearFit.h"
#include "RWDpBase.h"
#include <iostream>
#include <RWDpIntervalBuilder.h>

class DFA {
public:
    DFA(double minBox, double maxBox, double boxRatio);
    void receiveData(IRWItem<double>*, double MinX, double MaxX);
    void receiveData(IRWItem<double>*, IRWItem<double>*);
    void receiveData(double * y, int ny, double xmin, double xmax);
    void performAnalysis(double * logX, double * logY);
    void performAnalysis_1(double * logX, double * logY);
    void performAnalysisScale(double&, double&, u_int32_t);

    virtual ~DFA();
    u_int32_t getNBoxes() const;
    u_int32_t * getBoxes() const;
private:
    int boxSizes(u_int32_t minBox, u_int32_t maxBox, double boxRatio);
    void preprocess(IRWSet<double>*& X, IRWSet<double>*& Y, int boxIndex);
    u_int32_t * boxes;
    u_int32_t nBoxes;
    IRWIntervalBuilder<double> * interval;
    IRWItem<double> * data;
    IRWItem<double> * interX;
    bool deldata;
};

inline u_int32_t * DFA::getBoxes() const {
    return boxes;
}

inline void DFA::performAnalysisScale(double & x, double & y, u_int32_t scale) {
    //    IRWItem<double> * interX = interval->produceLinearInterval(0, data->getNpoints() - 1, 1);
    if (scale < nBoxes) {
        double sums = 0;
        uint_32t intervalsneeded = interval->overlapingIntervals(data, boxes[scale]);
        IRWItem<double> * X = interval->getOverlapingIntervalsI(interX, boxes[scale], 0);

        for (unsigned long int j = 0; j < intervalsneeded; j++) {
            IRWItem<double> * Y = interval->getOverlapingIntervalsI(data, boxes[scale], j);
            LinearFit lfit(X, Y);
            lfit.performFit();
            double sumsquared = 0;
            IRWItem<double> *dist = lfit.getFit()->quadraticHeightDifference(X, Y, sumsquared);
            delete dist;
            sumsquared /= boxes[scale];
            sums += sqrt(sumsquared);
            delete Y;
        }
        delete X;
        x = boxes[scale];
        y = sums / data->getNpoints();
    }
}

inline void DFA::preprocess(IRWSet<double>*& X, IRWSet<double>*& Y, int boxIndex) {
    int N = boxIndex;
    IRWItem<double> * interX = interval->produceLinearInterval(0, data->getNpoints() - 1, 1);
    X = interval->getOverlapingIntervals(interX, N);
    Y = interval->getOverlapingIntervals(data, N);
    delete interX;
}

inline void DFA::performAnalysis(double * logX, double * logY) {
    //    IRWItem<double> * interX = interval->produceLinearInterval(0, data->getNpoints() - 1, 1);
    for (int i = 1; i <= nBoxes; i++) {
        double sums = 0;
        uint_32t intervalsneeded = interval->overlapingIntervals(data, boxes[i]);
        IRWItem<double> * X = interval->getOverlapingIntervalsI(interX, boxes[i], 0);
        for (unsigned long int j = 0; j < intervalsneeded; j++) {
            IRWItem<double> * Y = interval->getOverlapingIntervalsI(data, boxes[i], j);
            LinearFit lfit(X, Y);
            lfit.performFit();
            double sumsquared = 0;
            IRWItem<double> *dist = lfit.getFit()->heightDifference(X, Y, sumsquared);
            delete dist;
            sumsquared /= boxes[i];
            sums += sqrt(sumsquared);
            delete Y;
        }
        delete X;
        logY [i] = sums / data->getNpoints();
        logX [i] = boxes[i];
        cout << logX [i] << " " << logY [i] << endl;
    }
}

inline void DFA::performAnalysis_1(double * logX, double * logY) {
    //    IRWItem<double> * interX = interval->produceLinearInterval(0, data->getNpoints() - 1, 1);
    double * xdata = interX->data();
    double * ydata = data->data();
    if (xdata && ydata) {
        for (int i = 1; i <= nBoxes; i++) {
            double sums = 0;
            uint_32t intervalsneeded = interval->overlapingIntervals(data, boxes[i]);
            //            IRWItem<double> * X = interval->getOverlapingIntervalsI(interX, boxes[i], 0);
            for (unsigned long int j = 0; j < intervalsneeded; j++) {
                //                IRWItem<double> * Y = interval->getOverlapingIntervalsI(data, boxes[i], j);
                LinearFit lfit(&xdata[0], boxes[i], &ydata[j], boxes[i]);
                lfit.performFit();
                double sumsquared = 0;
                lfit.getFit()->heightDifference(&xdata[0], boxes[i], &ydata[j], boxes[i], sumsquared);
                //                delete dist;
                sumsquared /= boxes[i];
                sums += sqrt(sumsquared);
                //                delete Y;
            }
            //            delete X;
            logY [i] = sums / data->getNpoints();
            logX [i] = boxes[i];
            cout << logX [i] << " " << logY [i] << endl;
        }
    }
}

inline void DFA::receiveData(double * y, int ny, double xmin, double xmax) {
    this->data = new DataPointsDouble();
    this->data->receiveData(y, ny);
    interX = interval->produceLinearInterval(xmin, xmax, (xmax - xmin) / data->getNpoints());
    cout<<this->data->getNpoints()<<" "<<interX->getNpoints()<<endl;
    deldata = true;
}

inline void DFA::receiveData(IRWItem<double>* data, double MinX, double MaxX) {
    this->data = data;
    interX = interval->produceLinearInterval(MinX, MaxX, (MaxX - MinX) / data->getNpoints());
    deldata = false;
}

inline void DFA::receiveData(IRWItem<double>* data, IRWItem<double> * X) {
    this->data = data;
    interX = X;
    deldata = false;
}

inline DFA::DFA(double minBox, double maxBox, double boxRatio) {
    nBoxes = boxSizes(minBox, maxBox, boxRatio);
    interval = new RWDpIntervalBuilder<double>();
}

inline int DFA::boxSizes(u_int32_t minBox, u_int32_t maxBox, double boxRatio) {
    int tBoxes = log10((double) maxBox / minBox) / log10(boxRatio) + 1.5;
    boxes = new u_int32_t[tBoxes + 1];
    long i = 1, j = 2, k = 0;
    for (boxes[1] = minBox; j <= tBoxes && boxes[j - 1] < maxBox; i++)
        if ((k = minBox * pow(boxRatio, i) + 0.5) > boxes[j - 1])
            boxes[j++] = k;
    if (boxes[--j] > maxBox) --j;
    return (j);
}

inline DFA::~DFA() {
    delete interval;
    delete interX;
    if(deldata){
        delete data;
    }
}

inline u_int32_t DFA::getNBoxes() const {
    return nBoxes;
}

#endif /* DFAANALYSIS_H */

