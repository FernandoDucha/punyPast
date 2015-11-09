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
#include "GeneralUsage.h"
#include "driver.h"
#include "SweepLine.h"

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

private:
    int grabNargs();
    QString format;
    FormatStrNms::Driver FrmtDrv;
    std::vector<FRMT> types;
    bool parse;
};

inline int FormatString::grabNargs() {
    types.size();
}

inline FormatString::FormatString(QString input) {
    format = input;
    parse = FrmtDrv.parse_string(format.toStdString());
}

inline FormatString::FormatString(char * input) {
    format = QString(input);
    parse = FrmtDrv.parse_string(format.toStdString());
}

inline FormatString::FormatString(std::string input) {
    format = QString(input.c_str());
    parse = FrmtDrv.parse_string(format.toStdString());
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
    parse = FrmtDrv.parse_string(format.toStdString());
}

inline int FormatString::grabNargs() {
    int sum = 0;
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
    return sum;
}

FormatString::~FormatString() {
}

#endif	/* FORMATSTRING_H */

