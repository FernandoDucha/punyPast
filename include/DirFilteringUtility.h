/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DirFilteringUtility.h
 * Author: fordem
 *
 * Created on 16 de Abril de 2016, 09:54
 */

#ifndef DIRFILTERINGUTILITY_H
#define DIRFILTERINGUTILITY_H
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QDir>
#include <iostream>
#include <string>

class DirFilteringUtility {
public:
    DirFilteringUtility(QString Path, QStringList filters);
    virtual ~DirFilteringUtility();
    QStringList getValidBarabasiFiles();
    QStringList getValidERFiles();

private:
    QString thispath;
    QStringList thisfilters;
    QDir thisdir;
    QStringList validBarabasiFiles;
};

inline DirFilteringUtility::DirFilteringUtility(QString Path, QStringList filters) : thispath(Path), thisfilters(filters) {
    thisdir.setNameFilters(thisfilters);

}

inline QStringList DirFilteringUtility::getValidERFiles() {
    if (thisdir.cd(thispath)) {
        validBarabasiFiles.clear();
       double par[14];
        int dir, per,mt;
        unsigned int seed, ssd ;
        QFileInfoList filei = thisdir.entryInfoList();
        for (int i = 0; i < filei.size(); i++) {
            int size = filei.at(i).fileName().size();
            char * r = new char[filei.at(i).fileName().size() + 1];
            r[size] = '\0';
            strncpy(r, const_cast<char*> (filei.at(i).fileName().toStdString().c_str()), size);
            std::string str1(r);
            std::string str ="ER_%lf_"
                    "%d_"
                    "pn_%lf"
                    "_pr_%lf"
                    "_pm_%lf"
                    "_tw_%lf"
                    "_ts_%lf"
                    "_c_%lf"
                    "_ws_%lf"
                    "_ic_%lf"
                    "_per_%d"
                    "_avgt_%lf"
                    "_msgt_%lf"
                    "_seed_%lf_"
                    "ssd_%lf_"        
                    "mt_%lf.txt"; 
            int a = sscanf(str1.c_str(),
                    str.c_str(), &par[0], &dir, &par[1], &par[2], &par[3], &par[4], &par[5], &par[6], &par[7], &par[8], &per, &par[9], &par[10], &par[11],&par[12], &par[13]);
            if (a == 16) {
                validBarabasiFiles << filei.at(i).absoluteFilePath();
            }
            delete r;
        }
        return validBarabasiFiles;
    }
    return QStringList();
}

inline QStringList DirFilteringUtility::getValidBarabasiFiles() {
    if (thisdir.cd(thispath)) {
        validBarabasiFiles.clear();
        double par[14];
        int dir, per,mt;
        unsigned int seed, ssd ;
        QFileInfoList filei = thisdir.entryInfoList();
        for (int i = 0; i < filei.size(); i++) {
            int size = filei.at(i).fileName().size();
            char * r = new char[filei.at(i).fileName().size() + 1];
            r[size] = '\0';
            strncpy(r, const_cast<char*> (filei.at(i).fileName().toStdString().c_str()), size);
            std::string str1(r);
            std::string str ="AB_%lf_"
                    "%d_"
                    "pn_%lf"
                    "_pr_%lf"
                    "_pm_%lf"
                    "_tw_%lf"
                    "_ts_%lf"
                    "_c_%lf"
                    "_ws_%lf"
                    "_ic_%lf"
                    "_per_%d"
                    "_avgt_%lf"
                    "_msgt_%lf"
                    "_seed_%lf_"
                    "ssd_%lf_"        
                    "mt_%lf.txt"; 
            int a = sscanf(str1.c_str(),
                    str.c_str(), &par[0], &dir, &par[1], &par[2], &par[3], &par[4], &par[5], &par[6], &par[7], &par[8], &per, &par[9], &par[10], &par[11],&par[12], &par[13]);
            if (a == 16) {
                validBarabasiFiles << filei.at(i).absoluteFilePath();
            }
            delete r;
        }
        return validBarabasiFiles;
    }
    return QStringList();
}

inline DirFilteringUtility::~DirFilteringUtility() {
}

#endif /* DIRFILTERINGUTILITY_H */

