/* 
 * File:   FileQTreeWidget.h
 * Author: fordem
 *
 * Created on February 22, 2015, 4:21 PM
 */

#ifndef FILEQTREEWIDGET_H
#define	FILEQTREEWIDGET_H
#include <QtGui>
#include <QTreeWidget>
#include <QFileInfo>
#include <QDebug>
#include <FileRawBuffer.h>

class FileQTreeWidget : public QTreeWidget {
    Q_OBJECT
public:
    FileQTreeWidget(QString root, QWidget * parent);
    void addFolder(QTreeWidgetItem * parent, QFileInfo folder);
    void addFile(QTreeWidgetItem * parent, QFileInfo file);
    void addFolder(QTreeWidget * parent, QFileInfo folder);
    void addFile(QTreeWidget * parent, QFileInfo file);
    FileRawBuffer * getFileRawBuffer();
    virtual ~FileQTreeWidget();
    void removeAllItems();
    void buildTree();
protected slots:
    void showDirectory(QTreeWidgetItem* qwti, int column);
    void selectFile(QTreeWidgetItem* qwti, int column);
signals:
    void fileChosen();
private:
    QDir _root;
    QList<QFileInfo> qfil;
    QIcon FolderIcon;
    QIcon FileIcon;
    QString rootString;
    FileRawBuffer * frb;
};

#endif	/* FILEQTREEWIDGET_H */

