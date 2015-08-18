/* 
 * File:   ExpressionParserWidget.cpp
 * Author: fordem
 * 
 * Created on February 21, 2015, 6:54 AM
 */

#include <qt5/QtWidgets/qabstractbutton.h>

#include "ExprParserWidget.h"

ExprParserWidget::ExprParserWidget(QWidget * parent) : IInputWidget(parent) {
    qGrdLay = new QGridLayout(this);
    Toker = new Tokenizer();
    fNWalks = fWSize = false;
    textBox = new QWidget(this);
    qGrdLayTexBox = new QGridLayout(textBox);
    qGrdLay->addWidget(textBox, 0, 0, 2, 2);

    lNWalks = new QLabel(this);
    lNWalks->setText("N. Walks:");
    lNWalks->setContentsMargins(0, 0, 0, 0);
    qGrdLayTexBox->addWidget(lNWalks, 0, 0, 1, 1, Qt::AlignCenter | Qt::AlignBottom);

    lWSize = new QLabel(this);
    lWSize->setText("W. Size:");
    lWSize->setContentsMargins(0, 0, 0, 0);
    qGrdLayTexBox->addWidget(lWSize, 1, 0, 1, 1, Qt::AlignCenter | Qt::AlignTop);

    NWalks = new QLineEdit(this);
    NWalks->setValidator(new QIntValidator(1, pow(2, 30)));
    NWalks->setContentsMargins(0, 0, 0, 0);
    qGrdLayTexBox->addWidget(NWalks, 0, 1, 1, 1, Qt::AlignCenter | Qt::AlignBottom);
    NWalks->setDisabled(true);

    WSize = new QLineEdit(this);
    WSize->setValidator(new QIntValidator(1, pow(2, 30)));
    WSize->setContentsMargins(0, 0, 0, 0);
    qGrdLayTexBox->addWidget(WSize, 1, 1, 1, 1, Qt::AlignCenter | Qt::AlignTop);
    WSize->setDisabled(true);

    linCongTitle = new QLabel("Randon Number Generator");
    linCongTitle->setContentsMargins(0, 0, 0, 0);
    qGrdLay->addWidget(linCongTitle, 0, 2, 1, 2, Qt::AlignCenter | Qt::AlignHCenter);


    linCongInput = new QTextEdit(this);
    linCongInput->setContentsMargins(0, 0, 0, 0);
    qGrdLay->addWidget(linCongInput, 1, 2, 1, 2);
    linCongInput->setEnabled(false);
    chkExpr = new QCheckBox(this);
    chkExpr->setContentsMargins(0, 0, 0, 0);
    qGrdLay->addWidget(chkExpr, 1, 4, 1, 1, Qt::AlignLeft | Qt::AlignTop);

    lChkExpr = new QLabel(this);
    lChkExpr->setText("Enable\nExpression:");
    qGrdLay->addWidget(lChkExpr, 0, 4, 1, 1, Qt::AlignLeft | Qt::AlignBottom);

    okNoLabel = new QLabel(this);
    okNoLabel->setContentsMargins(0, 0, 0, 0);
    okNoLabel->setVisible(false);
    qGrdLay->addWidget(okNoLabel, 1, 4, 1, 1, Qt::AlignCenter | Qt::AlignHCenter);
    _exprBRWK = NULL;
    this->_exprRNG = new ExprRNG();
    connect(linCongInput, SIGNAL(textChanged()), this, SLOT(runTimeParse()));
    connect(chkExpr, SIGNAL(stateChanged(int)), this, SLOT(enableExprEditing(int)));
    connect(WSize, SIGNAL(textChanged(QString)), this, SLOT(numstepsEdit(QString)));
    connect(NWalks, SIGNAL(textChanged(QString)), this, SLOT(numwalksEdit(QString)));
    connect(WSize, SIGNAL(editingFinished()), this, SLOT(attemptToCreateRWK()));
    connect(NWalks, SIGNAL(editingFinished()), this, SLOT(attemptToCreateRWK()));
    connect(_groupAnim, SIGNAL(finished()), this, SLOT(setMeInvisible()));

}

void ExprParserWidget::clear() {
    _exprRNG->resetExpressionRNG();
    linCongInput->setText("");
    IInputWidget::clear();
}

QParallelAnimationGroup * ExprParserWidget::getAnimation() {
    return groupAnim;
}

void ExprParserWidget::enableExprEditing(int state) {
    if (state == Qt::Checked) {
        linCongInput->setEnabled(true);
        ThisOverLay->setVisible(true);
    } else {
        linCongInput->setEnabled(false);
        ThisOverLay->setVisible(false);
    }
}

void ExprParserWidget::enableNwWsEditing(bool state) {
    int scale = 40;
    if (state) {
        QList<Token> sec_resp =ThisOverLay->getTokenList();
        _exprRNG->receiveNewExpression(&sec_resp);
        NWalks->setEnabled(true);
        WSize->setEnabled(true);
        QPixmap pix("images/okseed.png");
        okNoLabel->setPixmap(pix.scaled(scale, scale, Qt::KeepAspectRatio));
        okNoLabel->setToolTip("You have set a seed. Remember you have to set the Number of Walks AND the Size of the Walks.");
    } else {
        NWalks->setText("");
        WSize->setText("");
        NWalks->setEnabled(false);
        WSize->setEnabled(false);
        fNWalks = fWSize = false;
    }
}

void ExprParserWidget::attemptToCreateRWK() {
    if (fNWalks && fWSize) {//caso os dois sejam verdadeiros ou seja os dois foram editados.
        int nw = NWalks->text().toInt();
        int sw = WSize->text().toInt();
        _exprBRWK = new ExprBinaryRandomWalk(_exprRNG, sw, nw);
        emit createdRWK(dynamic_cast<IRandomWalk*> (_exprBRWK));
        fNWalks = fWSize = false;
    } else if ((fNWalks && !fWSize) || (!fNWalks && fWSize)) {// aqui caso só tenha sido editado ver se há informação em outra caixa de texto.
        int v1 = NWalks->text().toInt();
        fNWalks = (v1 > 0) ? true : false;
        int v2 = WSize->text().toInt();
        fWSize = (v2 > 0) ? true : false;
        if (fNWalks && fWSize) {//caso os dois sejam verdadeiros há informação nas duas caixas de texto.
            int nw = NWalks->text().toInt();
            int sw = WSize->text().toInt();
            _exprBRWK = new ExprBinaryRandomWalk(_exprRNG, sw, nw);
//            _exprBRWK->setup(_exprRNG,sw,nw);
            emit createdRWK(dynamic_cast<IRandomWalk*> (_exprBRWK));
            fNWalks = fWSize = false;
        } else {
            emit createdRWK(NULL);
        }
    } else {
        emit createdRWK(NULL);
    }
}

void ExprParserWidget::setOverlay(Overlay * Over) {
    ThisOverLay = Over;
    connect(ThisOverLay, SIGNAL(foundSeed(bool)), this, SLOT(enableNwWsEditing(bool)));
}

Overlay * ExprParserWidget::getOverlay() {
    return ThisOverLay;
}

void ExprParserWidget::runTimeParse() {
    okNoLabel->setVisible(true);
    QString str = linCongInput->toPlainText();
    QList<Token>  resp = (Toker->Tokenize(str));
    ThisOverLay->setTokenList(resp);
    QList<Token> sec_resp =ThisOverLay->getTokenList();
    _exprRNG->receiveNewExpression(&sec_resp);
    int scale = 40;
    if (Toker->hasErro()) {
        QPixmap pix("images/nook.png");
        okNoLabel->setPixmap(pix.scaled(scale, scale, Qt::KeepAspectRatio));
        okNoLabel->setToolTip("There is a lexical error. Number written in a bad form. Functions that don't exist. Look for the manual.");
    } else if (_exprRNG->hasErro()) {
        QPixmap pix("images/nook.png");
        okNoLabel->setPixmap(pix.scaled(scale, scale, Qt::KeepAspectRatio));
        okNoLabel->setToolTip("There is a syntax error. The expression is incorrect at some point. Operators incorrectly used, parenthesis that don't match. Look for the manual.");
    } else if (!ThisOverLay->hasSeed()) {
        QPixmap pix("images/nookseed.png");
        okNoLabel->setPixmap(pix.scaled(scale, scale, Qt::KeepAspectRatio));
        okNoLabel->setToolTip("There is no Seed chosen for this expression. Look for the manual.");
    }
}

ExprParserWidget::~ExprParserWidget() {
}

void ExprParserWidget::setMeInvisible() {
    this->chkExpr->setChecked(false);
    IInputWidget::setMeInvisible();
}
