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

enum FRMT {
    INT = 0, DBL = 1, FLT = 2, LNG = 3
};

class FormatString {
public:
    FormatString(QString input);
    FormatString(char * input);
    FormatString(std::string input);
    virtual ~FormatString();
    bool parse();
private:
    int grabNargs();
    QString format;
    FormatStrNms::Driver FrmtDrv;
    std::vector<FRMT> types;
};

int FormatString::grabNargs() {
    types.size();
}

FormatString::FormatString(QString input) {
    format = input;
}

FormatString::FormatString(char * input) {
    format = QString(input);
}

FormatString::FormatString(std::string input) {
    format = QString(input.c_str());
}

bool FormatString::parse() {
    bool ret = FrmtDrv.parse_string(format.toStdString());
    if (ret) {
        for (int i = 0; i < FrmtDrv.regs.size(); i++) {
            if (FrmtDrv.regs[i]) {
                switch (FrmtDrv.regs[i]) {
                    case 0:
                        types.push_back(INT);
                        break;
                    case 1:
                        types.push_back(DBL);
                        break;
                    case 2:
                        types.push_back(FLT);
                        break;
                    case 3:
                        types.push_back(LNG);
                        break;
                }
            }
        }
    }
    return ret;
}

FormatString::~FormatString() {
}

#endif	/* FORMATSTRING_H */

