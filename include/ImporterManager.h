/* 
 * File:   ImporterManager.h
 * Author: fordem
 *
 * Created on November 9, 2015, 7:20 PM
 */

#ifndef IMPORTERMANAGER_H
#define	IMPORTERMANAGER_H
#include "FormatString.h"
#include "FileInStreamInterface.h"
#include "FileInStreamInterfaceDecimal.h"
#include "IImporter.h"
#include "IRWItemImporter.h"
#include "IRWSet.h"

class ImporterManager {
public:
    ImporterManager(QString fileFormat, QString filename);
    ImporterManager(char * fileFormat, char * filename);
    ImporterManager(std::string fileFormat, std::string filename);
    void readFile();
    virtual ~ImporterManager();

    IRWSet<int> * getIset() {
        return iSet;
    }

    IRWSet<double> * getDset() {
        return dSet;
    }

    IRWSet<long long> * getLset() {
        return lSet;
    }

    IRWSet<float> * getFset() {
        return fSet;
    }

private:
    void closeReaders();
    void fillSets();
    bool searchColumSeparator();
    void initializeImporters();
    void clearImporters();
    int tokensize; // = format.grabTksSize();
    int tokenpos; // = 0;
    int importer; //= 0;
    int maxImporters; // = format.grabNargs();
    vector<IImporter*> importers;
    FormatString format;
    QString file;
    FileInStreamInterfaceDecimal<char> sepReader;
    FileInStreamInterfaceDecimal<double> doubleReader;
    FileInStreamInterfaceDecimal<int> intReader;
    FileInStreamInterfaceDecimal<long long> longReader;
    FileInStreamInterfaceDecimal<float> floatReader;
    IRWSet<int> * iSet;
    IRWSet<double> * dSet;
    IRWSet<long long> * lSet;
    IRWSet<float> * fSet;
    vector<int> iImp,dImp,lImp,fImp;
};

#endif	/* IMPORTERMANAGER_H */

