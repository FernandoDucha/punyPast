/****************************************************************************
** Meta object code from reading C++ file 'Walks2DOverlay.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/Walks2DOverlay.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Walks2DOverlay.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Walks2DOverlay_t {
    QByteArrayData data[11];
    char stringdata[90];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Walks2DOverlay_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Walks2DOverlay_t qt_meta_stringdata_Walks2DOverlay = {
    {
QT_MOC_LITERAL(0, 0, 14), // "Walks2DOverlay"
QT_MOC_LITERAL(1, 15, 8), // "plotItem"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 18), // "IRWItem<QPollarF>*"
QT_MOC_LITERAL(4, 44, 5), // "point"
QT_MOC_LITERAL(5, 50, 9), // "QPollarF*"
QT_MOC_LITERAL(6, 60, 1), // "p"
QT_MOC_LITERAL(7, 62, 1), // "n"
QT_MOC_LITERAL(8, 64, 4), // "plot"
QT_MOC_LITERAL(9, 69, 9), // "runPushed"
QT_MOC_LITERAL(10, 79, 10) // "stopPushed"

    },
    "Walks2DOverlay\0plotItem\0\0IRWItem<QPollarF>*\0"
    "point\0QPollarF*\0p\0n\0plot\0runPushed\0"
    "stopPushed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Walks2DOverlay[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    3,   42,    2, 0x0a /* Public */,
       8,    0,   49,    2, 0x0a /* Public */,
       9,    0,   50,    2, 0x0a /* Public */,
      10,    0,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int, QMetaType::Double,    6,    7,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Walks2DOverlay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Walks2DOverlay *_t = static_cast<Walks2DOverlay *>(_o);
        switch (_id) {
        case 0: _t->plotItem((*reinterpret_cast< IRWItem<QPollarF>*(*)>(_a[1]))); break;
        case 1: _t->point((*reinterpret_cast< QPollarF*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 2: _t->plot(); break;
        case 3: _t->runPushed(); break;
        case 4: _t->stopPushed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Walks2DOverlay::*_t)(IRWItem<QPollarF> * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Walks2DOverlay::plotItem)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Walks2DOverlay::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Walks2DOverlay.data,
      qt_meta_data_Walks2DOverlay,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Walks2DOverlay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Walks2DOverlay::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Walks2DOverlay.stringdata))
        return static_cast<void*>(const_cast< Walks2DOverlay*>(this));
    return QWidget::qt_metacast(_clname);
}

int Walks2DOverlay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Walks2DOverlay::plotItem(IRWItem<QPollarF> * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
