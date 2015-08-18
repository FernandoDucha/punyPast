/* 
 * File:   GULineEdit.h
 * Author: fernando
 *
 * Created on 1 de Maio de 2013, 10:10
 */

#ifndef GULINEEDIT_H
#define	GULINEEDIT_H
#include <qt5/QtWidgets/QLineEdit>
#include <qt5/QtWidgets/QWidget>
#include <qt5/QtCore/QDebug>

class GULineEdit : public QLineEdit {
    Q_OBJECT
public:
    GULineEdit(QWidget* parent);
    //    void keyPressEvent(QKeyEvent * event);
    virtual ~GULineEdit();
    void setPonto(int ponto);
    int getPonto() const;
    void setValue(int a);
    void setDefault_value(int default_value);
    int getDefault_value() const;
    void reset();
public slots:
    void setText(const QString &);
    int getActual_value() const;
private:
    int ponto;
    int ponto_pos;
    int actual_value;
    int default_value;
signals:
    void valueChanged(int a);
};

#endif	/* GULINEEDIT_H */

