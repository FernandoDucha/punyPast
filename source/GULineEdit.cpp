/* 
 * File:   GULineEdit.cpp
 * Author: fernando
 * 
 * Created on 1 de Maio de 2013, 10:10
 */

#include <qt5/QtCore/QEvent>
#include <qt5/QtGui/QValidator>
#include <qt5/QtGui/qdesktopservices.h>

#include "GULineEdit.h"

GULineEdit::GULineEdit(QWidget * parent) : QLineEdit(parent) {
    ponto = 0;
    ponto_pos = 0;
    setValidator(new QIntValidator(this));
    default_value = 0;
    connect(this,SIGNAL(textEdited (const QString &)),this,SLOT(setText( const QString & )));
}

GULineEdit::~GULineEdit() {
}

void GULineEdit::setPonto(int ponto) {
    this->ponto = ponto;
}

void GULineEdit::reset() {
    setValue(getDefault_value());
}

int GULineEdit::getPonto() const {
    return ponto;
}
void GULineEdit::setText(const QString& str){
    QLineEdit::setText(str);
    actual_value=str.toInt(NULL,10);
    emit valueChanged(actual_value);
}

int GULineEdit::getActual_value() const {
    return actual_value;
}
//void GULineEdit::(QKeyEvent * event){
    
//    QString a = text().remove(selectedText());
//    setText(a);
//    qDebug()<<text()<<"---"<<event->text();
//    
//    setValue((text()+event->text()).toInt(NULL,10));
    
//    if((event->key()>=Qt::Key_0)&&(event->key()<=Qt::Key_9)){
//        QString a = text();
//        if(!hasSelectedText()){
//            if(!getPonto()&&text().size()<=3){
//                a.insert(cursorPosition(),QChar(event->key()));
//                int cp = cursorPosition();
//                setCursorPosition(cp+1);
//            }else if(getPonto()&&text().size()<=4){
//                a.insert(cursorPosition(),QChar(event->key()));
//                int cp = cursorPosition();
//                setText(a);
//                setCursorPosition(cp+1);
//            }
//        }else{
//            if(selectedText().contains('.')){
//                ponto=0;
//                ponto_pos=0;
//            }
//            int init=a.indexOf(selectedText(),0);
//            a.remove(selectedText());
//            if(!getPonto()&&text().size()<=3){
//                a.insert(init,QChar(event->key()));
//                setCursorPosition(init+1);
//            }else if(getPonto()&&text().size()<=4){
//                a.insert(init,QChar(event->key()));
//                setCursorPosition(init+1);
//            }
//        }
//        setText(a);
//        
//    }else if((event->key()==Qt::Key_Period)&&ponto==0){
//        ponto=1;
//        ponto_pos=cursorPosition();
//        QString a = text();
//        a.insert(cursorPosition(),QChar(event->key()));
//        setText(a);
//    }else if(hasSelectedText()&&(ponto==1)&&(event->key()==Qt::Key_Period)){
//        QString a = text();
//        QString b=selectedText();
//        int dp=a.indexOf(b,0);
//        a.remove(selectedText());
//        a.insert(dp,'.');
//        setText(a);
//        this->setCursorPosition(a.indexOf('.')+1);
//    }else if((event->key()==Qt::Key_Delete)){
//        
//        if(cursorPosition()==ponto_pos){
//            ponto=0;
//        }
//        QString a=text();
//        if(!hasSelectedText()){
//            a.remove(cursorPosition(),1);            
//        }else{
//            if(selectedText().contains(QChar(Qt::Key_Period))){
//                ponto =0; 
//                ponto_pos=0;
//            }
//            a.remove(selectedText());            
//        }
//        int cp = cursorPosition();
//        setText(a);
//        setCursorPosition(cp);
//    }else if((event->key()==Qt::Key_Backspace)){
//        if(cursorPosition()-1==ponto_pos){
//            ponto=0;
//        }
//        QString a=text();
//        if(!hasSelectedText()){
//            a.remove(cursorPosition()-1,1);
//        }else{
//            if(selectedText().contains(QChar(Qt::Key_Period))){
//                ponto =0; 
//                ponto_pos=0;
//            }
//            a.remove(selectedText());
//        }
//        int cp = cursorPosition();
//        setText(a);
//        setCursorPosition(cp-1);
//    }else if(event->key()==Qt::Key_Left){
//        if(cursorPosition()>0){
//                setCursorPosition(cursorPosition()-1);
//        }
//    }else if(event->key()==Qt::Key_Right){
//        if(cursorPosition()<text().size()){
//                setCursorPosition(cursorPosition()+1);
//        }
//    }
//    bool temp;
//    double v=text().toDouble(&temp);
//    if(temp&&(v!=0)){
//        actual_value=v;
//        emit valueChanged(v);
//    }
//}

void GULineEdit::setValue(int a) {
    if (a >= 0) {
        setText(QString::number(a));
        actual_value = a;
        emit valueChanged(a);
    }
}

void GULineEdit::setDefault_value(int default_value) {
    this->default_value = default_value;
}

int GULineEdit::getDefault_value() const {
    return default_value;
}