/* 
 * File:   FileQBRWWidget.cpp
 * Author: fordem
 * 
 * Created on February 22, 2015, 10:59 PM
 */

#include "FileQBRWWidget.h"

FileQBRWWidget::FileQBRWWidget(QWidget * parent) : IInputWidget(parent) {
    qGrdLay = new QGridLayout(this);
    fNWalks = fWSize = false;
    lNWalks = new QLabel(this);
    lNWalks->setText("N. Walks:");
    lNWalks->setContentsMargins(0, 0, 0, 0);
    qGrdLay->addWidget(lNWalks, 0, 0, 1, 1, Qt::AlignCenter | Qt::AlignBottom);

    lWSize = new QLabel(this);
    lWSize->setText("W. Size:");
    lWSize->setContentsMargins(0, 0, 0, 0);
    qGrdLay->addWidget(lWSize, 1, 0, 1, 1, Qt::AlignCenter | Qt::AlignTop);

    NWalks = new QLineEdit(this);
    NWalks->setValidator(new QIntValidator(1, pow(2, 30)));
    NWalks->setContentsMargins(0, 0, 0, 0);
    qGrdLay->addWidget(NWalks, 0, 1, 1, 1, Qt::AlignCenter | Qt::AlignBottom);
    NWalks->setDisabled(true);

    WSize = new QLineEdit(this);
    WSize->setValidator(new QIntValidator(1, pow(2, 30)));
    WSize->setContentsMargins(0, 0, 0, 0);
    qGrdLay->addWidget(WSize, 1, 1, 1, 1, Qt::AlignCenter | Qt::AlignTop);
    WSize->setDisabled(true);
    brwk = NULL;
    fileWid = new FileQTreeWidget("/", this);
    fileWid->setContentsMargins(0, 0, 0, 0);
    qGrdLay->addWidget(fileWid, 0, 2, 2, 3);



    connect(WSize, SIGNAL(textChanged(QString)), this, SLOT(numstepsEdit(QString)));
    connect(NWalks, SIGNAL(textChanged(QString)), this, SLOT(numwalksEdit(QString)));
    connect(WSize, SIGNAL(editingFinished()), this, SLOT(attemptToCreateRWK()));
    connect(NWalks, SIGNAL(editingFinished()), this, SLOT(attemptToCreateRWK()));
    connect(fileWid, SIGNAL(fileChosen()), this, SLOT(enableNwWsBox()));
    connect(_groupAnim, SIGNAL(finished()), this, SLOT(setMeInvisible()));
}

QParallelAnimationGroup *FileQBRWWidget::getAnimation() {
    return groupAnim;
}

void FileQBRWWidget::enableNwWsBox() {
    NWalks->setEnabled(true);
    WSize->setEnabled(true);
}

void FileQBRWWidget::attemptToCreateRWK() {
    if (fNWalks && fWSize) {//caso os dois sejam verdadeiros ou seja os dois foram editados.
        int nw = NWalks->text().toInt();
        int sw = WSize->text().toInt();
        //        if (brwk == NULL) {
        fileWid->getFileRawBuffer()->generateBuffer(sw * nw);
        brwk = new BinaryRandomWalk(fileWid->getFileRawBuffer(), sw, nw);
        //        } else {
        //            brwk->setup(fileWid->getFileRawBuffer(), sw, nw);
        //        }
        emit createdRWK(dynamic_cast<IRandomWalk*> (brwk));
        fNWalks = fWSize = false;
    } else if ((fNWalks && !fWSize) || (!fNWalks && fWSize)) {// aqui caso só tenha sido editado ver se há informação em outra caixa de texto.
        int v1 = NWalks->text().toInt();
        fNWalks = (v1 > 0) ? true : false;
        int v2 = WSize->text().toInt();
        fWSize = (v2 > 0) ? true : false;
        if (fNWalks && fWSize) {//caso os dois sejam verdadeiros há informação nas duas caixas de texto.
            int nw = NWalks->text().toInt();
            int sw = WSize->text().toInt();
            //            if (brwk == NULL) {
            fileWid->getFileRawBuffer()->generateBuffer(sw * nw);
            brwk = new BinaryRandomWalk(fileWid->getFileRawBuffer(), sw, nw);
            //            } else {
            //                brwk->setup(fileWid->getFileRawBuffer(), sw, nw);
            //            }
            emit createdRWK(dynamic_cast<IRandomWalk*> (brwk));
            fNWalks = fWSize = false;
        } else {
            emit createdRWK(NULL);
        }
    } else {
        emit createdRWK(NULL);
    }
}

void FileQBRWWidget::clear() {
    fileWid->removeAllItems();
    fileWid->buildTree();
    IInputWidget::clear();
}

FileQBRWWidget::~FileQBRWWidget() {
}

