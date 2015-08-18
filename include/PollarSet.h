/* 
 * File:   PollarSet.h
 * Author: fordem
 *
 * Created on August 17, 2015, 7:24 AM
 */

#ifndef POLLARSET_H
#define	POLLARSET_H
#include <map>
#include <string>

#include "QPollarF.h"
using namespace std;

class PollarSet {
public:
    PollarSet();
    PollarSet(const PollarSet& orig);
    virtual ~PollarSet();
    void addPollar(QPollarF f);
    void removePollar(QPollarF F);
    int qtyPollar(QPollarF f);
private:
    map<string, int> thismap;
};

inline PollarSet::PollarSet() {
    
}
inline void PollarSet::addPollar(QPollarF f){
    thismap[f.toString()]++;
}
inline int PollarSet::qtyPollar(QPollarF f){
    return thismap[f.toString()];
}
inline void PollarSet::removePollar(QPollarF f){
    thismap[f.toString()]--;
}
inline PollarSet::PollarSet(const PollarSet& orig) {
}

inline PollarSet::~PollarSet() {
}

#endif	/* POLLARSET_H */

