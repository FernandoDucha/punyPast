/* 
 * File:   FormatString.h
 * Author: fordem
 *
 * Created on June 20, 2015, 8:23 AM
 */

#ifndef FORMATSTRING_H
#define	FORMATSTRING_H
#include <QString>
#include <string>
#include <vector>
#include <iostream>
#include "GeneralUsage.h"
#include "driver.h"

enum FRMT {
    SEP = -1, INT = 0, DBL = 1, FLT = 2, LNG = 3
};

class FormatString {
public:
    FormatString(QString input);
    FormatString(char * input);
    FormatString(std::string input);
    virtual ~FormatString();
    bool parse();
    void setFormatString(QString input);
    void setFormatString(char * input);
    void setFormatString(std::string input);
    int grabNargs();
    int grabTksAt(int a);
    int grabTksSize();
    std::string grabSepStrAt(int a);
private:
    QString format;
    FormatStrNms::Driver FrmtDrv;
    std::vector<FRMT> types;
    bool pars;
};

inline std::string FormatString::grabSepStrAt(int a) {
    return FrmtDrv.regsS[a];
}

inline FormatString::FormatString(QString input) {
    format = input;
    //    pars = FrmtDrv.parse_string(format.toStdString(),std::string("FormatString"));
}

inline FormatString::FormatString(char * input) {
    format = QString(input);
    //    pars = FrmtDrv.parse_string(format.toStdString(),std::string("FormatString"));
}

inline FormatString::FormatString(std::string input) {
    format = QString(input.c_str());
    //    pars = FrmtDrv.parse_string(format.toStdString(),std::string("FormatString"));
}

inline void FormatString::setFormatString(QString input) {
    format = input;
}

inline void FormatString::setFormatString(char * input) {
    format = QString(input);
}

inline void FormatString::setFormatString(std::string input) {
    format = QString(input.c_str());
}

inline bool FormatString::parse() {
    pars = FrmtDrv.parse_string(std::string(format.toStdString().c_str()), std::string("FormatString"));
    return pars;
}

inline int FormatString::grabNargs() {
    int sum = -1;
    if (pars) {
        for (int i = 0; i < FrmtDrv.regs.size(); i++) {
            switch (FrmtDrv.regs[i]) {
                case 0:
                case 1:
                case 2:
                case 3:
                    sum++;
                    break;
            }
        }
        return sum + 1;
    }
    return sum;
}

inline int FormatString::grabTksSize() {
    return FrmtDrv.regs.size();
}

inline int FormatString::grabTksAt(int a) {
    return FrmtDrv.regs[a];
}

inline FormatString::~FormatString() {
}

#endif	/* FORMATSTRING_H */

