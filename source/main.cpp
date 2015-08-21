/*
 * File:   main.cpp
 * Author: fordem
 *
 * Created on July 1, 2013, 11:52 AM
 */

#include <QApplication>
#include <FileRawBuffer.h>
#include <ProbabilityBase.h>
#include <GraphUi.h>
#include <QDebug>
#include <qt5/QtCore/qlogging.h>
#include "FileRawBuffer.h"
#include "FileRNG.h"
#include "Dtest.h"
#include "std_test.h"
#include "BufferedProbabilityBase.h"
#include "RWDpIntervalBuilder.h"
#include "LinearFit.h"
#include "DFA.h"
#include "DFAInputGui.h"
#include "stringfrmt/driver.h"
#include "QPollarF.h"
extern "C" {
    Dtest * dtst_call;
    Test ** tst_call;
    void _dieharder_call(int test_num, int gen_num, int ts, int ps);
    void destroy_die_teste(Dtest* dtst, Test** tst);
}

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    //    RWBufferManager<int> rwbfm("file");
    //    int temp[10];
    //    RWBufferedVecSet<int> dps(10);
    //    for (int j = 0; j < 10; j++) {
    //        for (int i = 0; i < 10; i++) {
    //            temp[i] = lcg.randd()*10;
    //        }
    //        BufferedVecInt t = rwbfm.createBufferedVec(temp, 10);
    //        dps.put(&t);
    //    }
    //    auto teste = rwbfm.getVecIterator();
    //    teste[4].print();
    //    RWVInt * t1 = new RWVInt();
    //    *dynamic_cast<IRWItem<int>*>(t1)=*dynamic_cast<IRWItem<int>*>(dps.getElement(4));
    //    t1->print();
    //    //    teste.goBeg();
    //    //    while(!teste.last()){
    //    //        teste->print();
    //    //        teste++;
    //    //    }
    //    rwbfm.resetManager();
    QApplication app(argc, argv);
    setlocale(LC_ALL, "C");

    //    for (int i = 0; i < 18; i++) {
    //        _dieharder_call(i, 14, 10000, 100);
    //        for (int i = 0; i < dtst_call->nkps; i++) {
    //            for (int j = 0; j < tst_call[i]->psamples; j++) {
    //                qDebug() << tst_call[i]->pvalues[j];
    //            }
    //        }
    //        destroy_die_teste(dtst_call, tst_call);
    //    }

    //    RNGLinearCong lcg(5645678);
    //    LCGBinaryRandomWalk lcgbrwk(&lcg, 4000, 1);
    //    IRWItem<QPollarF> * d = lcgbrwk.perform2DWalkNoCollision(36);
    //    d->print();
    //    
    //        double a = 0.6, b = 0.61;
    //        IRWItem<double> * d1 = p->buildWeiestrass(0.2, 2.1, a, b, 40000);
    //    DFA dfa(5, 20000, 1.3);
    //    dfa.receiveData(d1, a, b);
    //    double teste;
    //    dfa.performAnalysis(NULL, NULL);
    //    delete d1;
    //    d1 = p->buildWeiestrass(0.4, 2.1, a, b, 40000);
    //    dfa.receiveData(d1, a, b);
    //    dfa.performAnalysis(NULL, NULL, teste, teste, teste);
    //    delete d1;
    //    d1 = p->buildWeiestrass(0.6, 2.1, a, b, 40000);
    //    dfa.receiveData(d1, a, b);
    //    dfa.performAnalysis(NULL, NULL, teste, teste, teste);

    //        IRWIntervalBuilder<double> *ib = new RWDpIntervalBuilder<double>();
    //        IRWItem<double> * interval = ib->produceLinearInterval(a, b, (b - a) / 40000);
    //    DataPointsDouble * dp = new DataPointsDouble();
    //    double * dd = new double[50];
    //    for(int i=0;i<50;i++){
    //        dd[i]=i;
    //    }
    //    d->print();
    //    dp->receiveData(dd,50);
    //    Polynom<2> P;
    //    P.setCoef(0,0);
    //    P.setCoef(1,0);
    //    IRWItem<double> * interval1=P.evalFromTo(0,49,1);
    //    LinearFit lin(interval, d);
    //    lin.performFit();
    //    lin.getFit()->distanceFromPoints(interval,d)->print();
    //    d->print();

    //
    //    //    IRWSet<double> * irs = ib->getOverlapingIntervals(d,3,1);
    //    //    for(int i=0;i<irs->getSize();i++){
    //    //        irs->getElement(i)->print();
    //    //    }
    //    IPolynom * p = new Polynom<2>();
    //    p->setCoef(0, 0);
    //    p->setCoef(1, 1);
    //    IRWItem<double> * b = p->evalFromToBuffered(10.37,11.42,0.05);
    //    b->print();

    //    (f * f1);
    //    f.print();
    //    cout << (f == f1) << endl;
    //    DFAInputGui DFA(interval, d, NULL);
    //    DFA.exec();
    //    FormatStrNms::Driver driver;
    //    std::cout<<(driver.parse_string(std::string("%d;%d;%d;%g;\n"),std::string("hello"))==true)<<std::endl;
    GraphUi * g = new GraphUi();
    //    create and show your widgets here
    g->showMaximized();

    //    Tokenizer T;
    //    QList<QString>* res=T.Tokenize("x=123.123*abc123abc");
    //    qDebug()<<*res;
    return app.exec();
}
