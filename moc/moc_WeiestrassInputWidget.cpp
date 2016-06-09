/****************************************************************************
** Meta object code from reading C++ file 'WeiestrassInputWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/WeiestrassInputWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WeiestrassInputWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_WeiestrassInputWidget_t {
    QByteArrayData data[14];
    char stringdata0[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WeiestrassInputWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WeiestrassInputWidget_t qt_meta_stringdata_WeiestrassInputWidget = {
    {
QT_MOC_LITERAL(0, 0, 21), // "WeiestrassInputWidget"
QT_MOC_LITERAL(1, 22, 11), // "weiestrassR"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 9), // "u_int32_t"
QT_MOC_LITERAL(4, 45, 1), // "L"
QT_MOC_LITERAL(5, 47, 1), // "H"
QT_MOC_LITERAL(6, 49, 1), // "B"
QT_MOC_LITERAL(7, 51, 5), // "start"
QT_MOC_LITERAL(8, 57, 3), // "end"
QT_MOC_LITERAL(9, 61, 5), // "Hedit"
QT_MOC_LITERAL(10, 67, 5), // "bedit"
QT_MOC_LITERAL(11, 73, 9), // "startedit"
QT_MOC_LITERAL(12, 83, 7), // "endedit"
QT_MOC_LITERAL(13, 91, 5) // "Ledit"

    },
    "WeiestrassInputWidget\0weiestrassR\0\0"
    "u_int32_t\0L\0H\0B\0start\0end\0Hedit\0bedit\0"
    "startedit\0endedit\0Ledit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WeiestrassInputWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    5,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   55,    2, 0x09 /* Protected */,
      10,    1,   58,    2, 0x09 /* Protected */,
      11,    1,   61,    2, 0x09 /* Protected */,
      12,    1,   64,    2, 0x09 /* Protected */,
      13,    1,   67,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,    4,    5,    6,    7,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void WeiestrassInputWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WeiestrassInputWidget *_t = static_cast<WeiestrassInputWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->weiestrassR((*reinterpret_cast< u_int32_t(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5]))); break;
        case 1: _t->Hedit((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->bedit((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->startedit((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->endedit((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->Ledit((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (WeiestrassInputWidget::*_t)(u_int32_t , double , double , double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WeiestrassInputWidget::weiestrassR)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject WeiestrassInputWidget::staticMetaObject = {
    { &IInputWidget::staticMetaObject, qt_meta_stringdata_WeiestrassInputWidget.data,
      qt_meta_data_WeiestrassInputWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *WeiestrassInputWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WeiestrassInputWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_WeiestrassInputWidget.stringdata0))
        return static_cast<void*>(const_cast< WeiestrassInputWidget*>(this));
    return IInputWidget::qt_metacast(_clname);
}

int WeiestrassInputWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IInputWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void WeiestrassInputWidget::weiestrassR(u_int32_t _t1, double _t2, double _t3, double _t4, double _t5)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
