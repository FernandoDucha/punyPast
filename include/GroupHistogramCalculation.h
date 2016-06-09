/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GroupHistogramCalculation.h
 * Author: fordem
 *
 * Created on 16 de Abril de 2016, 18:14
 */

#ifndef GROUPHISTOGRAMCALCULATION_H
#define GROUPHISTOGRAMCALCULATION_H
#include <QStringList>

#include "DirFilteringUtility.h"
#include "IRWItem.h"
#include "RWDpBase.h"
#include "ImporterManager.h"
#include "RWDpHistogram.h"
#include "IRWSet.h"
#include "IRWIHistogram.h"
#include <fstream>
#include "DFA.h"

class GroupHistogramCalculation {
public:
    GroupHistogramCalculation(QString path, int minbox, int maxbox, double ratio);
    virtual ~GroupHistogramCalculation();
    bool calculateHistogramsBarabasiFiles(double binsize);
    bool calculateHistogramsBarabasiFiles_avg(double binsize);

    bool calculateHistogramsERFiles(double binsize);
    bool calculateDFABarabasiFiles();
    bool calculateDFAERFiles();

    void exportOriginReturn(QString File);
private:
    u_int32_t * boxes;
    u_int32_t minbox;
    u_int32_t maxbox;
    double ratio;

    inline int boxSizes(u_int32_t minBox, u_int32_t maxBox, double boxRatio) {
        int tBoxes = log10((double) maxBox / minBox) / log10(boxRatio) + 1.5;
        boxes = new u_int32_t[tBoxes + 1];
        long i = 1, j = 2, k = 0;
        for (boxes[1] = minBox; j <= tBoxes && boxes[j - 1] < maxBox; i++)
            if ((k = minBox * pow(boxRatio, i) + 0.5) > boxes[j - 1])
                boxes[j++] = k;
        if (boxes[--j] > maxBox) --j;
        boxes[0] = 1;
        return (j);
    }
    IRWSet<double> * promoteDifferences(IRWItem<double> * item);
    IRWItem<double> * retrieveItem(QString file, QString Pattern, int collumn);
    IRWIHistogram<double> * createHistogram(IRWSet<double> * set, double ratio);
    int findZeroFromHistogram(IRWIHistogram<double> * hist);
    DirFilteringUtility * filtutil;
    QStringList Filter;
    int nBoxes;
    map<int, vector<double>> origin_return;
    QString path;
};

inline bool GroupHistogramCalculation::calculateHistogramsBarabasiFiles_avg(double binsize) {
    QStringList files = filtutil->getValidBarabasiFiles();
    origin_return.clear();
    IRWItem<double> * sum = new DataPointsDouble();
    for (int i = 0; i < files.size(); i++) {
        QString s = files.at(i);
        qDebug() << s;
        IRWItem<double> * er = retrieveItem(s, "%g %g %g %g %g %g %g %g %g\n", 4);
        *sum += *er;
        delete er;

    }
    *sum=*dynamic_cast<DataPointsDouble*>(sum)/ files.size();
    IRWSet<double> * diffs = promoteDifferences(sum);
    IRWIHistogram<double> * h = createHistogram(diffs, binsize);
    int zero = findZeroFromHistogram(h);
    for (int j = 0; j < diffs->getSize(); j++) {
        IRWItem<long long> * it = h->frequencies(diffs->getElement(j));
        double res = (double) it->getElement(zero - 1) / diffs->getElement(j)->getNpoints();
        origin_return[boxes[j]].push_back(res);
        delete it;
    }
    delete sum;
    delete diffs;
    delete h;
}

inline bool GroupHistogramCalculation::calculateDFABarabasiFiles() {
    QStringList files = filtutil->getValidBarabasiFiles();
    for (int i = 0; i < files.size(); i++) {
        QString s = files.at(i);
        qDebug() << s;
        IRWItem<double> * er = retrieveItem(s, "%g %g %g %g %g %g %g %g %g\n", 4);
        DFA dfa(minbox, maxbox, ratio);
        dfa.receiveData(er, 0, er->getNpoints());
        double * x = new double[nBoxes+1];
        double * y = new double[nBoxes+1];
        dfa.performAnalysis_1(x, y);
        delete [] x;
        delete [] y;
        delete er;
    }
}

inline bool GroupHistogramCalculation::calculateDFAERFiles() {
    QStringList files = filtutil->getValidERFiles();
    for (int i = 0; i < files.size(); i++) {
        QString s = files.at(i);
        IRWItem<double> * er = retrieveItem(s, "%g %g %g %g %g %g %g %g %g\n", 4);
        DFA dfa(minbox, maxbox, ratio);
        dfa.receiveData(er, 0, er->getNpoints());
        double * x = new double[nBoxes+1];
        double * y = new double[nBoxes+1];
        dfa.performAnalysis_1(x, y);
        delete [] x;
        delete [] y;
        delete er;
    }
}

inline void GroupHistogramCalculation::exportOriginReturn(QString File) {
    auto beg = origin_return.begin();
    auto end = origin_return.end();
    std::fstream arch(path.toStdString() + File.toStdString(), std::ios::out);
    for (; beg != end; beg++) {
        arch << (*beg).first;
        for (int i = 0; i < (*beg).second.size(); i++) {
            arch << " " << (*beg).second[i];
        }
        arch << endl;
    }
}

inline bool GroupHistogramCalculation::calculateHistogramsBarabasiFiles(double binsize) {
    QStringList files = filtutil->getValidBarabasiFiles();
    origin_return.clear();
    for (int i = 0; i < files.size(); i++) {
        QString s = files.at(i);
        qDebug() << s;
        IRWItem<double> * er = retrieveItem(s, "%g %g %g %g %g %g %g %g %g\n", 4);
        IRWSet<double> * diffs = promoteDifferences(er);
        IRWIHistogram<double> * h = createHistogram(diffs, binsize);
        int zero = findZeroFromHistogram(h);
        for (int j = 0; j < diffs->getSize(); j++) {
            IRWItem<long long> * it = h->frequencies(diffs->getElement(j));
            double res = (double) it->getElement(zero - 1) / diffs->getElement(j)->getNpoints();
            origin_return[boxes[j]].push_back(res);
            delete it;
        }
        delete er;
        delete diffs;
        delete h;
    }
}

inline bool GroupHistogramCalculation::calculateHistogramsERFiles(double binsize) {
    QStringList files = filtutil->getValidERFiles();
    origin_return.clear();
    for (int i = 0; i < files.size(); i++) {
        QString s = files.at(i);
        IRWItem<double> * er = retrieveItem(s, "%g %g %g %g %g %g %g %g %g\n", 4);
        IRWSet<double> * diffs = promoteDifferences(er);
        IRWIHistogram<double> * h = createHistogram(diffs, binsize);
        int zero = findZeroFromHistogram(h);
        for (int j = 0; j < diffs->getSize(); j++) {
            IRWItem<long long> * it = h->frequencies(diffs->getElement(j));
            double res = (double) it->getElement(zero - 1) / diffs->getElement(j)->getNpoints();
            origin_return[boxes[j]].push_back(res);
            delete it;
        }
        delete er;
        delete diffs;
        delete h;
    }
}

inline int GroupHistogramCalculation::findZeroFromHistogram(IRWIHistogram<double>* hist) {
    IRWItem<double> * intervals = hist->intervals();
    intervals->resetIterator();
    double abc;
    int zero = 0;
    while (intervals->getNext(abc)) {
        if (abc > 0) {
            break;
        }
        zero++;
    }
    delete intervals;
    return zero;
}

inline IRWIHistogram<double> * GroupHistogramCalculation::createHistogram(IRWSet<double> * set, double ratio) {
    return new RWDpHistogram<double>(set->getMax(), set->getMin(), ratio);
}

inline IRWSet<double> * GroupHistogramCalculation::promoteDifferences(IRWItem<double> * item) {
    IRWSet<double> * set = new RWDpSet<double>(nBoxes + 1);
    for (int i = 0; i < nBoxes + 1; i++) {
        double * buffer = nullptr;
        int size = 0;
        if (i) {
            u_int32_t box_size = boxes[i];
            size = item->getNpoints() - box_size;
            buffer = new double[size];
            double * data = item->data();
            for (int i = 0; i < size; i++) {
                buffer[i] = data[i + box_size] - data[i];
            }
        } else {
            size = item->getNpoints() - 1;
            buffer = new double[size];
            double * data = item->data();
            for (int i = 0; i < size; i++) {
                buffer[i] = data[i + 1] - data[i];
            }
        }
        IRWItem<double> * it = new RWDp<double>();
        it->receiveData(buffer, size);
        set->put(it);
        delete buffer;
    }
    return set;
}

inline IRWItem<double> * GroupHistogramCalculation::retrieveItem(QString file, QString Pattern, int collumn) {
    ImporterManager * a = new ImporterManager(Pattern, file);
    a->readFile();
    IRWSet<double> * t = a->getDset();
    IRWItem<double> * er = new DataPointsDouble();
    er->receiveData(t->getElement(collumn)->data(), t->getElement(collumn)->getNpoints());
    delete a;
    return er;
}

inline GroupHistogramCalculation::GroupHistogramCalculation(QString path, int minbox, int maxbox, double ratio) {
    Filter << "*.txt";
    filtutil = new DirFilteringUtility(path, Filter);
    this->minbox = minbox;
    this->maxbox = maxbox;
    this->ratio = ratio;
    this->path = path;
    nBoxes = boxSizes(this->minbox, this->maxbox, this->ratio);
}

inline GroupHistogramCalculation::~GroupHistogramCalculation() {
}
#endif /* GROUPHISTOGRAMCALCULATION_H */

