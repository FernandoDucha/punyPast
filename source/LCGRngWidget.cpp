/* 
 * File:   LCGRngWidget.cpp
 * Author: fordem
 * 
 * Created on February 26, 2015, 11:20 PM
 */

#include "LCGRngWidget.h"

LCGRngWidget::LCGRngWidget(QWidget * parent) : IInputWidget(parent) {
    LCGbrw=NULL;
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
    
    LCGconfig = new QWidget(this);
    LCGconfig->setContentsMargins(0, 0, 0, 0);
    
    qGridConfig = new QGridLayout(LCGconfig);
    qGridConfig->setContentsMargins(0, 0, 0, 0);
    qGrdLay->addWidget(LCGconfig, 0, 2, 5, 2);
    
    lConfig = new QLabel("LCG Config:");
    lConfig->setContentsMargins(0, 0, 0, 0);
    qGridConfig->addWidget(lConfig, 0, 0, 1, 2, Qt::AlignCenter | Qt::AlignHCenter);
    
    lSeed = new QLabel("Seed:");
    lSeed->setContentsMargins(0, 0, 0, 0);
    qGridConfig->addWidget(lSeed, 1, 0, 1, 1, Qt::AlignRight | Qt::AlignHCenter);
    
    lMulti = new QLabel("Multiplier:");
    lMulti->setContentsMargins(0, 0, 0, 0);
    qGridConfig->addWidget(lMulti, 2, 0, 1, 1, Qt::AlignRight | Qt::AlignHCenter);
    
    lInc = new QLabel("Increment:");
    lInc->setContentsMargins(0, 0, 0, 0);
    qGridConfig->addWidget(lInc, 3, 0, 1, 1, Qt::AlignRight | Qt::AlignHCenter);
    
    lModulus = new QLabel("Modulus:");
    lModulus->setContentsMargins(0, 0, 0, 0);
    qGridConfig->addWidget(lModulus, 4, 0, 1, 1, Qt::AlignRight | Qt::AlignHCenter);
    
    seed = new QLineEdit(LCGconfig);
    seed->setValidator(new QIntValidator(1, INT_MAX-1));
    seed->setContentsMargins(0, 0, 0, 0);
    qGridConfig->addWidget(seed, 1, 1, 1, 1, Qt::AlignRight | Qt::AlignHCenter);
    
    multi = new QLineEdit(LCGconfig);
    multi->setValidator(new QIntValidator(1,INT_MAX-1));
    multi->setContentsMargins(0, 0, 0, 0);
    qGridConfig->addWidget(multi, 2, 1, 1, 1, Qt::AlignRight | Qt::AlignHCenter);
    
    inc = new QLineEdit(LCGconfig);
    inc->setValidator(new QIntValidator(1,INT_MAX-1));
    inc->setContentsMargins(0, 0, 0, 0);
    qGridConfig->addWidget(inc, 3, 1, 1, 1, Qt::AlignRight | Qt::AlignHCenter);
    
    modulus = new QLineEdit(LCGconfig);
    modulus->setValidator(new QIntValidator(1,INT_MAX));
    modulus->setContentsMargins(0, 0, 0, 0);
    qGridConfig->addWidget(modulus, 4, 1, 1, 1, Qt::AlignRight | Qt::AlignHCenter);
    
    multi->setDisabled(true);
    inc->setDisabled(true);
    modulus->setDisabled(true);
    
    connect(WSize, SIGNAL(textChanged(QString)), this, SLOT(numstepsEdit(QString)));
    connect(NWalks, SIGNAL(textChanged(QString)), this, SLOT(numwalksEdit(QString)));
    connect(WSize, SIGNAL(editingFinished()), this, SLOT(attemptToCreateRWK()));
    connect(NWalks, SIGNAL(editingFinished()), this, SLOT(attemptToCreateRWK()));
    connect(_groupAnim, SIGNAL(finished()), this, SLOT(setMeInvisible()));
    connect(seed,SIGNAL(textChanged(QString)),this, SLOT(enableNwWsEditing(QString)));
}

void LCGRngWidget::attemptToCreateRWK() {
    if (fNWalks && fWSize) {//caso os dois sejam verdadeiros ou seja os dois foram editados.
        int nw = NWalks->text().toInt();
        int sw = WSize->text().toInt();
//        if (LCGbrw == NULL) {
            LCGbrw = new LCGBinaryRandomWalk(&LCGrng, sw, nw);
//        } else {
//            LCGbrw->setup(&LCGrng, sw, nw);
//        }
        emit createdRWK(dynamic_cast<IRandomWalk*> (LCGbrw));
        fNWalks = fWSize = false;
    } else if ((fNWalks && !fWSize) || (!fNWalks && fWSize)) {// aqui caso só tenha sido editado ver se há informação em outra caixa de texto.
        int v1 = NWalks->text().toInt();
        fNWalks = (v1 > 0) ? true : false;
        int v2 = WSize->text().toInt();
        fWSize = (v2 > 0) ? true : false;
        if (fNWalks && fWSize) {//caso os dois sejam verdadeiros há informação nas duas caixas de texto.
            int nw = NWalks->text().toInt();
            int sw = WSize->text().toInt();
//            if (LCGbrw == NULL) {
                LCGbrw = new LCGBinaryRandomWalk(&LCGrng, sw, nw);
//            } else {
//                LCGbrw->setup(&LCGrng, sw, nw);
//            }
            emit createdRWK(dynamic_cast<IRandomWalk*> (LCGbrw));
            fNWalks = fWSize = false;
        } else {
            emit createdRWK(NULL);
        }
    } else {
        emit createdRWK(NULL);
    }
}

void LCGRngWidget::enableNwWsEditing(QString s){
    uint64_t v = s.toULongLong();
    if(seed->text().length()>0){
        LCGrng.setSeed(v);
        NWalks->setEnabled(true);
        WSize->setEnabled(true);
        NWalks->setText("");
        WSize->setText("");        
    }else{
        NWalks->setEnabled(false);
        WSize->setEnabled(false);
    }
}

LCGRngWidget::~LCGRngWidget() {
}

