/* 
 * File:   MemAllocWidget.cpp
 * Author: fordem
 * 
 * Created on March 12, 2015, 10:10 PM
 */



#include <qt5/QtWidgets/qgridlayout.h>
#include <qt5/QtWidgets/qlabel.h>

#include "MemAllocWidget.h"
#include "GeneralUsage.h"

MemAllocWidget::MemAllocWidget(QWidget * parent) : QWidget(parent) {
    grdlay = new QGridLayout(this);
    grdlay->setSizeConstraint(QGridLayout::SetMaximumSize);
    grdlay->setContentsMargins(0, 0, 0, 0);

    memAlocLbl = new QLabel("Memory Allocation\nMethod");
    memAlocLbl->setContentsMargins(0, 0, 0, 0);

    memAlocComBox = new QComboBox(this);
    memAlocComBox->setContentsMargins(0, 0, 0, 0);
    QPixmap mem("images/ram.png");
    mem.scaled(42, 42, Qt::KeepAspectRatio);
    QIcon micon;
    micon.addPixmap(mem);
    memAlocComBox->addItem(micon, "All in Memory", QVariant(0));
    QPixmap drive("images/drive.png");
    drive.scaled(42, 42, Qt::KeepAspectRatio);
    QIcon dicon;
    dicon.addPixmap(drive);
    memAlocComBox->addItem(dicon, "All in Disk", QVariant(1));
    QPixmap bd("images/db.png");
    bd.scaled(42, 42, Qt::KeepAspectRatio);
    QIcon bdicon;
    bdicon.addPixmap(bd);
    memAlocComBox->addItem(bdicon,"Sql Database", QVariant(2));
    
    connect(memAlocComBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setToolTipMemAloc(int)));
//    connect(memAlocComBox,SIGNAL(highlighted(int)),this,SLOT(setToolTipMemAloc(int)));
    
    memAlocComBox->setCurrentIndex(2);
    memAlocComBox->setCurrentIndex(0);
    
    grdlay->addWidget(memAlocLbl,0,0,2,1);
    grdlay->addWidget(memAlocComBox,0,1,2,1);
    
}
void MemAllocWidget::setToolTipMemAloc(int index){
    switch(index){
        case ALL_MEM:{
            memAlocComBox->setToolTip("This is a fast and limited allocation.\n"
                    "Used in most desktop environments but not useful for very big simulations.");
            emit memOption(ALL_MEM);
        }break;
        case ALL_DISK:{
            memAlocComBox->setToolTip("This is a slow and non optimized allocation.\n"
                    "Used for very big simulations where time doesn't matter and there is over 100GB disk space.");
            emit memOption(ALL_DISK);
        }break;
        case SQL_DB:{
            memAlocComBox->setToolTip("An optimized embedded SQL database.\n"
                    "Used for very big simulations where time matters and both RAM and DISK are available.");
            emit memOption(SQL_DB);
        }break;
    }
}
MemAllocWidget::~MemAllocWidget() {
}

