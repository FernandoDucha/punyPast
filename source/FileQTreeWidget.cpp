/* 
 * File:   FileQTreeWidget.cpp
 * Author: fordem
 * 
 * Created on February 22, 2015, 4:21 PM
 */




#include <qt5/QtWidgets/qheaderview.h>
#include <qt5/QtWidgets/qmessagebox.h>

#include "FileQTreeWidget.h"

FileQTreeWidget::FileQTreeWidget(QString root, QWidget * parent) : QTreeWidget(parent) {
    QTreeWidgetItem * header = new QTreeWidgetItem();
    header->setText(0, "File Names");
    header->setText(1, "Path");
    this->setHeaderItem(header);
    this->setColumnHidden(1, true);
    QPixmap temp("images/file.png");
    temp.scaled(20, 20, Qt::KeepAspectRatio);
    FileIcon = QIcon(temp);
    QPixmap temp1("images/folder.png");
    temp1.scaled(20, 20, Qt::KeepAspectRatio);
    this->header()->setSectionResizeMode(0, QHeaderView::Interactive);
    FolderIcon = QIcon(temp1);
    _root = QDir(root);
    rootString = root;
    buildTree();
    this->setAutoScroll(true);
    connect(this, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(showDirectory(QTreeWidgetItem*, int)));
    connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(selectFile(QTreeWidgetItem*, int)));
    frb = NULL;
}

void FileQTreeWidget::selectFile(QTreeWidgetItem* qtwi, int) {
    QString path = qtwi->text(1);
    QFileInfo qfi = QFileInfo(path);
    if (qfi.isFile()) {
        int buttom = QMessageBox::question(parentWidget(), "Is this your file?", "File with path,\n" + path);
        if (buttom == QMessageBox::Yes) {
            if (frb) {
                delete frb;
            }
            char * temp = strdup(path.toStdString().c_str());

            frb = new FileRawBuffer(temp, 0);
            emit fileChosen();
        }
    }
}

FileRawBuffer * FileQTreeWidget::getFileRawBuffer() {
    return frb;
}

void FileQTreeWidget::showDirectory(QTreeWidgetItem* qtwi, int) {
    QString path = qtwi->text(1);
    QDir tpath = QDir(path);
    QFileInfo qfi = QFileInfo(path);
    if (qfi.isDir()) {//checking if is directory.
        if (qtwi->childCount() == 0) {//there is no children so no checking is needed.
            QList<QFileInfo> qtemplist = tpath.entryInfoList();
            for (int i = 0; i < qtemplist.size(); i++) {
                if (qtemplist.at(i).isDir()) {
                    addFolder(qtwi, qtemplist.at(i));
                } else {
                    addFile(qtwi, qtemplist.at(i));
                }
                this->resizeColumnToContents(0);
            }
        } else {
            int child_c = qtwi->childCount();
            while (child_c > 0) {
                QTreeWidgetItem * qtwi_temp = qtwi->child(0);
                qtwi->removeChild(qtwi_temp);
                child_c--;
            }
            QList<QFileInfo> qtemplist = tpath.entryInfoList();
            for (int i = 0; i < qtemplist.size(); i++) {
                if (qtemplist.at(i).isDir()) {
                    addFolder(qtwi, qtemplist.at(i));
                } else {
                    addFile(qtwi, qtemplist.at(i));
                }
                this->resizeColumnToContents(0);
            }
        }
        if (qtwi->isExpanded()) {
            qtwi->setExpanded(false);
        } else {
            qtwi->setExpanded(true);
        }

    }
}

void FileQTreeWidget::addFolder(QTreeWidgetItem* parent, QFileInfo folder) {
    QTreeWidgetItem * qtwi = new QTreeWidgetItem(parent);
    qtwi->setText(0, folder.fileName());
    qtwi->setText(1, folder.filePath());
    qtwi->setIcon(0, FolderIcon);
    qtwi->setToolTip(0, folder.filePath());
    parent->addChild(qtwi);
}

void FileQTreeWidget::addFile(QTreeWidgetItem* parent, QFileInfo file) {
    QTreeWidgetItem * qtwi = new QTreeWidgetItem(parent);
    qtwi->setText(0, file.fileName());
    qtwi->setText(1, file.filePath());
    qtwi->setIcon(0, FileIcon);
    qtwi->setToolTip(0, file.filePath());
    parent->addChild(qtwi);
}

void FileQTreeWidget::addFolder(QTreeWidget* parent, QFileInfo folder) {
    QTreeWidgetItem * qtwi = new QTreeWidgetItem(parent);
    qtwi->setText(0, folder.fileName());
    qtwi->setText(1, folder.filePath());
    qtwi->setIcon(0, FolderIcon);
    qtwi->setToolTip(0, folder.filePath());
    parent->addTopLevelItem(qtwi);
}

void FileQTreeWidget::addFile(QTreeWidget* parent, QFileInfo file) {
    QTreeWidgetItem * qtwi = new QTreeWidgetItem(parent);
    qtwi->setText(0, file.fileName());
    qtwi->setText(1, file.filePath());
    qtwi->setIcon(0, FileIcon);
    qtwi->setToolTip(0, file.filePath());
    parent->addTopLevelItem(qtwi);
}

void FileQTreeWidget::removeAllItems() {
    int topLvl = this->topLevelItemCount();
    while (topLvl > 0) {
        QTreeWidget::takeTopLevelItem(0);
        topLvl--;
    }
}

void FileQTreeWidget::buildTree() {
    qfil = _root.entryInfoList();
    for (int i = 0; i < qfil.size(); i++) {
        if (qfil.at(i).isDir()) {
            addFolder(this, qfil.at(i));
        } else {
            addFile(this, qfil.at(i));
        }
    }
}

FileQTreeWidget::~FileQTreeWidget() {
}

