/****************************************************************************
** Meta object code from reading C++ file 'LCGRngWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/LCGRngWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LCGRngWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LCGRngWidget_t {
    QByteArrayData data[5];
    char stringdata0[53];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LCGRngWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LCGRngWidget_t qt_meta_stringdata_LCGRngWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "LCGRngWidget"
QT_MOC_LITERAL(1, 13, 18), // "attemptToCreateRWK"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 17), // "enableNwWsEditing"
QT_MOC_LITERAL(4, 51, 1) // "s"

    },
    "LCGRngWidget\0attemptToCreateRWK\0\0"
    "enableNwWsEditing\0s"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LCGRngWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x09 /* Protected */,
       3,    1,   25,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,

       0        // eod
};

void LCGRngWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LCGRngWidget *_t = static_cast<LCGRngWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->attemptToCreateRWK(); break;
        case 1: _t->enableNwWsEditing((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject LCGRngWidget::staticMetaObject = {
    { &IInputWidget::staticMetaObject, qt_meta_stringdata_LCGRngWidget.data,
      qt_meta_data_LCGRngWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LCGRngWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LCGRngWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LCGRngWidget.stringdata0))
        return static_cast<void*>(const_cast< LCGRngWidget*>(this));
    return IInputWidget::qt_metacast(_clname);
}

int LCGRngWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IInputWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
