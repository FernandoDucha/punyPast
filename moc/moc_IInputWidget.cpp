/****************************************************************************
** Meta object code from reading C++ file 'IInputWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/IInputWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'IInputWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_IInputWidget_t {
    QByteArrayData data[7];
    char stringdata0[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IInputWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IInputWidget_t qt_meta_stringdata_IInputWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "IInputWidget"
QT_MOC_LITERAL(1, 13, 10), // "createdRWK"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 12), // "IRandomWalk*"
QT_MOC_LITERAL(4, 38, 12), // "numwalksEdit"
QT_MOC_LITERAL(5, 51, 12), // "numstepsEdit"
QT_MOC_LITERAL(6, 64, 14) // "setMeInvisible"

    },
    "IInputWidget\0createdRWK\0\0IRandomWalk*\0"
    "numwalksEdit\0numstepsEdit\0setMeInvisible"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IInputWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   37,    2, 0x09 /* Protected */,
       5,    1,   40,    2, 0x09 /* Protected */,
       6,    0,   43,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,

       0        // eod
};

void IInputWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        IInputWidget *_t = static_cast<IInputWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->createdRWK((*reinterpret_cast< IRandomWalk*(*)>(_a[1]))); break;
        case 1: _t->numwalksEdit((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->numstepsEdit((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->setMeInvisible(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (IInputWidget::*_t)(IRandomWalk * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&IInputWidget::createdRWK)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject IInputWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_IInputWidget.data,
      qt_meta_data_IInputWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *IInputWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IInputWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_IInputWidget.stringdata0))
        return static_cast<void*>(const_cast< IInputWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int IInputWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void IInputWidget::createdRWK(IRandomWalk * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
