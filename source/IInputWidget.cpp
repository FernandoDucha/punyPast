/* 
 * File:   IInputWidget.cpp
 * Author: fordem
 * 
 * Created on February 26, 2015, 7:06 PM
 */

#include "IInputWidget.h"

IInputWidget::IInputWidget(QWidget * parent) : QWidget(parent) {
    animationMin = new QPropertyAnimation(this, "minimumSize");
    animationMin->setEasingCurve(QEasingCurve::InOutQuad);
    animationMin->setDuration(3000);
    animationMin->setStartValue(QSize(0, 0));
    animationMin->setEndValue(QSize(400, 150));
    
    animationMax = new QPropertyAnimation(this, "maximumSize");
    animationMax->setEasingCurve(QEasingCurve::InOutQuad);
    animationMax->setDuration(3000);
    animationMax->setStartValue(QSize(0, 0));
    animationMax->setEndValue(QSize(400, 150));
    
    groupAnim = new QParallelAnimationGroup(this);
    groupAnim->addAnimation(animationMin);
    groupAnim->addAnimation(animationMax);
    
    _animationMin = new QPropertyAnimation(this, "minimumSize");
    _animationMin->setEasingCurve(QEasingCurve::InOutQuad);
    _animationMin->setDuration(500);
    _animationMin->setStartValue(QSize(400, 150));
    _animationMin->setEndValue(QSize(0, 0));
    
    _animationMax = new QPropertyAnimation(this, "maximumSize");
    _animationMax->setEasingCurve(QEasingCurve::InOutQuad);
    _animationMax->setDuration(500);
    _animationMax->setStartValue(QSize(400, 150));
    _animationMax->setEndValue(QSize(0, 0));
    
    _groupAnim = new QParallelAnimationGroup(this);
    _groupAnim->addAnimation(_animationMin);
    _groupAnim->addAnimation(_animationMax);
}

IInputWidget::~IInputWidget() {
}
void IInputWidget::setMeInvisible(){
    QWidget::setVisible(false);
    clear();
}
void IInputWidget::setMeVisible(bool visible) {
    if (visible) {
        clear();
        groupAnim->start();
        QWidget::setVisible(visible);
    } else {
        _groupAnim->start();
    }
}
void IInputWidget::numwalksEdit(QString s) {
    int v = s.toInt();
    fNWalks = (v > 0) ? true : false;
}

void IInputWidget::numstepsEdit(QString s) {
    int v = s.toInt();
    fWSize = (v > 0) ? true : false;
}

void IInputWidget::clear(){
    NWalks->setText("");
    WSize->setText("");
    fNWalks=false;
    fWSize=false;
}