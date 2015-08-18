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

#include "Tokenizer.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);
    QApplication app(argc, argv);
    setlocale(LC_ALL,"C");
    GraphUi * g = new GraphUi();
//    create and show your widgets here
    g->showMaximized();
//    Tokenizer T;
//    QList<QString>* res=T.Tokenize("x=123.123*abc123abc");
//    qDebug()<<*res;
    return app.exec();
}
