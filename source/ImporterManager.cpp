/* 
 * File:   ImporterManager.cpp
 * Author: fordem
 * 
 * Created on November 9, 2015, 7:20 PM
 */

#include "ImporterManager.h"
#include "RWDpSet.h"

ImporterManager::ImporterManager(QString fileFormat, QString filename) : format(fileFormat), sepReader(const_cast<char*> (filename.toStdString().c_str())),
intReader(const_cast<char*> (filename.toStdString().c_str())), doubleReader(const_cast<char*> (filename.toStdString().c_str())),
longReader(const_cast<char*> (filename.toStdString().c_str())), floatReader(const_cast<char*> (filename.toStdString().c_str())) {
    file = filename;
}

ImporterManager::ImporterManager(char * fileFormat, char * filename) : format(fileFormat), sepReader(filename), intReader(filename), doubleReader(filename),
longReader(filename), floatReader(filename) {
    file = QString(filename);
}

ImporterManager::ImporterManager(std::string fileFormat, std::string filename) : format(fileFormat), sepReader(const_cast<char*> (filename.c_str())),
intReader(const_cast<char*> (filename.c_str())), doubleReader(const_cast<char*> (filename.c_str())),
longReader(const_cast<char*> (filename.c_str())), floatReader(const_cast<char*> (filename.c_str())) {
    file = QString(filename.c_str());
}

ImporterManager::~ImporterManager() {
}

bool ImporterManager::searchColumSeparator() {
    bool isDigitOrDot = false;

    while (!isDigitOrDot) {
        int t = sepReader.tell();
        char sep = sepReader.read();
        switch (sep) {
            case ' ':
            case '_':
            case ',':
            case ':':
            case ';':
            case '\t':
                break;
            case '-':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                doubleReader.seek(t);
                doubleReader.read();
                if (!doubleReader.good()) {
                    cerr << "erro na Estrutura do arquivo." << endl;
                    exit(1);
                } else {
                    isDigitOrDot = true;
                    sepReader.seek(t);
                    doubleReader.seek(t);
                }
                break;
            default:
                cerr << "Caractere inválido encontrado   --- " << t << endl;

        };
    }

}

void ImporterManager::clearImporters() {
    for (int i = 0; i < importers.size(); i++) {
        delete importers[i];
    }
    importers.clear();
}

void ImporterManager::initializeImporters() {
    clearImporters();
    tokensize = format.grabTksSize();
    tokenpos = 0;
    importer = 0;
    maxImporters = format.grabNargs();
    importers = vector<IImporter*>(maxImporters);
    int i = 0, d = 0, l = 0, f = 0;
    for (int j = 0; j < maxImporters; j++) {
        switch (format.grabTksAt(tokenpos)) {
            case 0:
                importers[j] = new IRWItemImporter<int>(intReader);
                iImp.push_back(j);
                i++;
                break;
            case 1:
                importers[j] = new IRWItemImporter<double>(doubleReader);
                dImp.push_back(j);

                d++;
                break;
            case 2:
                importers[j] = new IRWItemImporter<long long>(longReader);
                lImp.push_back(j);

                l++;
                break;
            case 3:
                f++;
                importers[j] = new IRWItemImporter<float>(floatReader);
                fImp.push_back(j);
                break;
        }
    }
    if (i) {
        iSet = new RWDpSet<int>(i);
    } else {
        iSet = nullptr;
    }
    if (d) {
        dSet = new RWDpSet<double>(d);
    } else {
        dSet = nullptr;
    }
    if (l) {
        lSet = new RWDpSet<long long>(l);
    } else {
        lSet = nullptr;
    }
    if (f) {
        fSet = new RWDpSet<float>(f);
    } else {
        fSet = nullptr;
    }
}

void ImporterManager::fillSets() {
    if (iSet) {
        for (int i = 0; i < iSet->getSize(); i++) {
            IRWItemImporter<int> * item = dynamic_cast<IRWItemImporter<int>*> (importers[iImp[i]]);
            if (item) {
                iSet->put(item->finish());
            }
        }
    }
    if (dSet) {
        for (int i = 0; i < dSet->getSize(); i++) {
            IRWItemImporter<double> * item = dynamic_cast<IRWItemImporter<double>*> (importers[dImp[i]]);
            if (item) {
                dSet->put(item->finish());
            }
        }
    }
    if (lSet) {
        for (int i = 0; i < lSet->getSize(); i++) {
            IRWItemImporter<long long> * item = dynamic_cast<IRWItemImporter<long long>*> (importers[lImp[i]]);
            if (item) {
                lSet->put(item->finish());
            }
        }
    }
    if (fSet) {
        for (int i = 0; i < fSet->getSize(); i++) {
            IRWItemImporter<float> * item = dynamic_cast<IRWItemImporter<float>*> (importers[fImp[i]]);
            if (item) {
                fSet->put(item->finish());
            }
        }
    }
}

void ImporterManager::readFile() {
    if (format.parse()) {
        initializeImporters();
        while (!sepReader.eof()&&!intReader.eof()&&!doubleReader.eof()&&!longReader.eof()&&!floatReader.eof()) {
            switch (format.grabTksAt(tokenpos)) {
                case -2:
                    sepReader.read();
                    tokenpos = (tokenpos + 1) % tokensize;
                    break;
                case -1:
                {

                    searchColumSeparator();
                    uint64_t tp = sepReader.tell();
                    intReader.seek(tp);
                    doubleReader.seek(tp);
                    longReader.seek(tp);
                    floatReader.seek(tp);
                    tokenpos = (tokenpos + 1) % tokensize;
                    break;
                }
                case 0:
                {
                    importers[importer]->addTerm();
                    uint64_t tp = intReader.tell();
                    sepReader.seek(tp);
                    doubleReader.seek(tp);
                    longReader.seek(tp);
                    floatReader.seek(tp);
                    tokenpos = (tokenpos + 1) % tokensize;
                    importer = (importer + 1) % maxImporters;
                    break;
                }
                case 1:
                {
                    importers[importer]->addTerm();
                    uint64_t tp = doubleReader.tell();
                    intReader.seek(tp);
                    sepReader.seek(tp);
                    longReader.seek(tp);
                    floatReader.seek(tp);
                    tokenpos = (tokenpos + 1) % tokensize;
                    importer = (importer + 1) % maxImporters;
                    break;
                }
                case 2:
                {
                    importers[importer]->addTerm();
                    uint64_t tp = longReader.tell();
                    intReader.seek(tp);
                    doubleReader.seek(tp);
                    sepReader.seek(tp);
                    floatReader.seek(tp);
                    tokenpos = (tokenpos + 1) % tokensize;
                    importer = (importer + 1) % maxImporters;
                    break;
                }
                case 3:
                {
                    importers[importer]->addTerm();
                    uint64_t tp = floatReader.tell();
                    intReader.seek(tp);
                    doubleReader.seek(tp);
                    longReader.seek(tp);
                    sepReader.seek(tp);
                    tokenpos = (tokenpos + 1) % tokensize;
                    importer = (importer + 1) % maxImporters;
                    break;
                }

            }
        }
    }
    fillSets();
}

