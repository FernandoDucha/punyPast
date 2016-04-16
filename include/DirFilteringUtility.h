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

class DirFilteringUtility {
public:
    DirFilteringUtility(QString Path);
    virtual ~DirFilteringUtility();
private:
    QString thispath;
};
inline DirFilteringUtility::DirFilteringUtility(QString Path):thispath(Path) {
}


inline DirFilteringUtility::~DirFilteringUtility() {
}

#endif /* DIRFILTERINGUTILITY_H */

