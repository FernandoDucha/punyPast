/* 
 * File:   Overlay.cpp
 * Author: fordem
 * 
 * Created on February 9, 2015, 11:56 PM
 */

#include <qt5/QtWidgets/qlabel.h>
#include <qt5/QtWidgets/qtextedit.h>
#include <qt5/QtCore/qlogging.h>
#include <qt5/QtCore/qlist.h>

#include "Overlay.h"
#include "Token.h"

Overlay::Overlay(QWidget * Parent) : QWidget(Parent) {
    //    setPalette(Qt::blue);
    //    setAttribute(Qt::WA_TransparentForMouseEvents);
    this->resize(800, 560);
    //    temp->setGeometry(QRect(0,0,600,600));
    //    temp->setWindowOpacity(0);
    //    temp->setGeometry(this->geometry());
    thisLayout = new QVBoxLayout(this);
    //    thisLayout->setSizeConstraint(QLayout::SetMaximumSize);
    //    thisLayout->setContentsMargins(0, 0, 0, 0);
    //
    //
    ExpressionMessage = new ExprTextEdit(this);
    QPalette pal = palette();
    pal.setBrush(QPalette::Window, QColor(255, 255, 255, 128));
    ExpressionMessage->setPalette(pal);
    ExpressionMessage->setAutoFillBackground(true);
    ExpressionMessage->setStyleSheet(" font-size:15pt ");
    ExpressionMessage->setReadOnly(true);
    //    QPalette pal1 = palette();
    pal.setBrush(QPalette::Window, QColor(255, 0, 0, 128));
    ErrorMessage = new QLabel("Sintaxe Error.");
    ErrorMessage->setPalette(pal);
    ErrorMessage->setAutoFillBackground(true);
    ErrorMessage->setStyleSheet(" font-size:15pt ");
    ErrorMessage->setVisible(false);

    pal.setBrush(QPalette::Window, QColor(0, 0, 128, 128));
    InsructionsMessage = new QLabel("When your expression is ready, press ctrl and click any number in your expression to select the SEED. After that, press \"Create RNG\".");
    InsructionsMessage->setPalette(pal);
    InsructionsMessage->setAutoFillBackground(true);
    InsructionsMessage->setStyleSheet(" font-size:15pt ");
    InsructionsMessage->setWordWrap(true);
    //    QPalette pal1 = palette();
    //    pal1.setBrush(QPalette::Window, Qt::red);
    //    setPalette(pal1);

    thisLayout->addWidget(ExpressionMessage, 0);
    thisLayout->addWidget(InsructionsMessage, 0);
    thisLayout->addWidget(ErrorMessage, 0);
    connect(ExpressionMessage, SIGNAL(expressionPos(int)), this, SLOT(ExpressionClicked(int)));
}

void Overlay::ExpressionClicked(int Pos) {
    hSeed = false;
    for (int i = 0; i < tk.size(); i++) {
        Token t = tk.at(i);
        if ((t.getStrInputStart() <= Pos)&&
                (t.getStrInputEnd() > Pos)&&
                (t.getTOKEN_TYPE() == NUMBER)) {
            t.setSeed(true);
            hSeed = true;
        } else {
            t.setSeed(false);
        }
        tk[i] = t;
    }
    setTokenList(tk);
    emit foundSeed(hSeed);
}

QList<Token>  Overlay::getTokenList() {
    return this->tk;
}

bool Overlay::hasSeed() {
    return hSeed;
}

void Overlay::setTokenList(QList<Token>  a) {
    QString actualText = "<html>";
    tk = a;
    QString temp = "";
    ErrorMessage->setVisible(false);
    for (int i = 0; i < tk.size(); i++) {
        Token tok = tk.at(i);
        temp += tok.getFormattedString();
        if (tok.getTOKEN_TYPE() == ERRO) {
            ErrorMessage->setVisible(true);
        }
    }
    actualText += temp + "</html>";
    ExpressionMessage->setText(actualText);
    emit foundSeed(false);
}

Overlay::~Overlay() {
}

