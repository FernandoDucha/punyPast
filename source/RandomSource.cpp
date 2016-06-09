/* 
 * File:   RandomSource.cpp
 * Author: fordem
 * 
 * Created on February 20, 2015, 7:14 PM
 */


#include <qt5/QtCore/qdebug.h>
#include <qt5/QtCore/qlogging.h>
#include <qt5/QtGui/qpixmap.h>

#include "RandomSource.h"

RandomSource::RandomSource(QWidget * parent) : QDialog(parent) {
    setWindowTitle("Choose Randomness Source");
    qGrdLay = new QGridLayout(this);
    setLayout(qGrdLay);

    allocChoice = new MemAllocWidget(this);
    allocChoice->setContentsMargins(0, 0, 0, 0);
    qGrdLay->addWidget(allocChoice, 0, 0, 1, 2);

    qTW = new QTreeWidget(this);
    qTW->setContentsMargins(0, 0, 0, 0);
    qTW->setColumnCount(2);
    qGrdLay->addWidget(qTW, 1, 0, 1, 2);
    qTW->setHeaderLabels(QStringList() << "Methods" << "Description");
    QString style = "QTreeWidget::item:!selected"
            "{ "
            "border: 1px solid gainsboro; "
            "}"
            "QTreeWidget::item:selected"
            "{"
            "selection-background-color: #cccccc;"
            "selection-color: #000000;"

            "}"
            "QTreeWidget"
            "{"
            "background-color: #fcfcfc;"
            "background-image: url('images/seed.png');"
            "background-repeat: no-repeat;"
            "background-attachment: scroll;"
            "background-position: center center;"
            "}"
            "QTreeWidget"
            "{"
            "font: 16px;"
            "}"
            ;
    qTW->setStyleSheet(style);

    FileAnalysis = new QTreeWidgetItem(qTW);
    FileAnalysis->setText(0, "File Analysis");
    FileAnalysis->setText(1, "Techniques that propose analysis of files and the\npossibility of its randomness.\nStill under development.");
    FileAnalysis->setFlags(Qt::ItemIsEnabled);

    QRNGItem = new QTreeWidgetItem(FileAnalysis);
    QRNGItem->setText(0, "QRNG");
    QRNGItem->setText(1, "An analysis of randomness on Quantum Random\nGenerated Files(QRNG).");
    QRNGItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    RandomGenerators = new QTreeWidgetItem(qTW);
    RandomGenerators->setText(0, "Parsed RNG's");
    RandomGenerators->setText(1, "Techniques applied to files are now modified so\nthat RNG functions can be analyzed.\nStill under development.");
    RandomGenerators->setFlags(Qt::ItemIsEnabled);


    ExprParser = new QTreeWidgetItem(RandomGenerators);
    ExprParser->setText(0, "Expressions");
    ExprParser->setText(1, "A parser that is able to evaluate expressions,\nmaking possible to analyze its RNG capabilities\nwhen a seed is provided.");
    ExprParser->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    RNGcd = new QTreeWidgetItem(qTW);
    RNGcd->setText(0, "Coded RNG's");
    RNGcd->setText(1, "Hard Coded RNG's with fewer configuration options.\nYou will be able to able to choose at least the seed.");
    RNGcd->setFlags(Qt::ItemIsEnabled);

    CommonLinCong = new QTreeWidgetItem(RNGcd);
    CommonLinCong->setText(0, "LCG");
    CommonLinCong->setText(1, "A linear congruential RNG. Where is possible\nto set up the Seed and change magic numbers");
    CommonLinCong->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    CommonLinCong->setToolTip(0, "Linear Congruential Generator");

    NonDiff = new QTreeWidgetItem(qTW);
    NonDiff->setText(0, "NDCF");
    NonDiff->setText(1, "Some classical Non Differentiable Continuous Functions\n(NDCF)that have known and unknown fractal dimension.");
    NonDiff->setFlags(Qt::ItemIsEnabled);

    Weiestrass = new QTreeWidgetItem(NonDiff);
    Weiestrass->setText(0, "Weiestrass");
    Weiestrass->setText(1, "A special kind of function, that is NDCF.\nAnd has a well known fractal dimension D=2-H.");
    Weiestrass->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    Weiestrass->setToolTip(0, "Special function, NDCF. BEAWARE THIS IS NOT RANDOM.");

    qTW->addTopLevelItem(this->FileAnalysis);
    qTW->addTopLevelItem(this->RandomGenerators);
    qTW->addTopLevelItem(this->RNGcd);
    qTW->addTopLevelItem(this->NonDiff);


    qTW->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    qTW->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
    setModal(true);

    this->setMaximumSize(600, 450);
    this->setMinimumSize(600, 450);
    QPixmap icon("images/seed.png");
    icon.scaled(30, 30, Qt::KeepAspectRatio);
    setWindowIcon(icon);
    okBt = new QPushButton(this);
    QPixmap ok("images/ok.png");
    ok.scaled(30, 30, Qt::KeepAspectRatio);
    okBt->setIcon(ok);
    qGrdLay->addWidget(okBt, 2, 0, 1, 1);
    noBt = new QPushButton(this);
    QPixmap no("images/nook.png");
    no.scaled(30, 30, Qt::KeepAspectRatio);
    noBt->setIcon(no);
    qGrdLay->addWidget(noBt, 2, 1, 1, 1);
    connect(noBt, SIGNAL(pressed()), this, SLOT(noPressed()));
    connect(okBt, SIGNAL(pressed()), this, SLOT(okPressed()));
    connect(allocChoice, SIGNAL(memOption(MEM_ALLOC)), this, SLOT(memChoiceSel(MEM_ALLOC)));
    memChoice = ALL_MEM;
    //    qTW->resizeColumnToContents(0);
    //    qTW->resizeColumnToContents(1);
}

void RandomSource::memChoiceSel(MEM_ALLOC choice) {
    memChoice = choice;
}

void RandomSource::okPressed() {
    if (qTW->selectedItems().size() > 0) {
        accept();
        if (qTW->selectedItems().at(0) == QRNGItem) {
            emit choiceType(FA_QRNG);
            emit memAlloc(memChoice);
        } else if (qTW->selectedItems().at(0) == ExprParser) {
            emit choiceType(RNG_EP);
            emit memAlloc(memChoice);
        } else if (qTW->selectedItems().at(0) == CommonLinCong) {
            emit choiceType(RNG_CD);
            emit memAlloc(memChoice);
        } else if (qTW->selectedItems().at(0) == Weiestrass) {
            emit choiceType(WEIES);
            emit memAlloc(memChoice);
        } else {
            emit choiceType(NONE);
        }
    } else {
        reject();
    }
}

void RandomSource::noPressed() {
    reject();
}

void RandomSource::keyPressEvent(QKeyEvent *e) {
    if (e->key() != Qt::Key_Escape)
        QDialog::keyPressEvent(e);
    else {
    }
}

RandomSource::~RandomSource() {
}

