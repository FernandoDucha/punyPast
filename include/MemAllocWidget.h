/* 
 * File:   MemAllocWidget.h
 * Author: fordem
 *
 * Created on March 12, 2015, 10:10 PM
 */

#ifndef MEMALLOCWIDGET_H
#define	MEMALLOCWIDGET_H
#include <QWidget>
#include <QGridLayout>
#include <QComboBox>
#include <QLabel>
#include <QIcon>
#include <QPixmap>

enum MEM_ALLOC {
    ALL_MEM = 0, ALL_DISK = 1, SQL_DB = 2
};

class MemAllocWidget : public QWidget {
    Q_OBJECT
public:
    MemAllocWidget(QWidget * parent);
    virtual ~MemAllocWidget();
protected slots:
    void setToolTipMemAloc(int);
private:
    QGridLayout * grdlay;
    QLabel * memAlocLbl;
    QComboBox * memAlocComBox;
signals:
    void memOption(MEM_ALLOC); 
};

#endif	/* MEMALLOCWIDGET_H */

