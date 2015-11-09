/****************************************************************************
** Meta object code from reading C++ file 'RandomSource.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/RandomSource.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RandomSource.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RandomSource_t {
    QByteArrayData data[10];
    char stringdata[100];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RandomSource_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RandomSource_t qt_meta_stringdata_RandomSource = {
    {
QT_MOC_LITERAL(0, 0, 12), // "RandomSource"
QT_MOC_LITERAL(1, 13, 10), // "choiceType"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 8), // "RS_TYPES"
QT_MOC_LITERAL(4, 34, 13), // "random_source"
QT_MOC_LITERAL(5, 48, 8), // "memAlloc"
QT_MOC_LITERAL(6, 57, 9), // "MEM_ALLOC"
QT_MOC_LITERAL(7, 67, 9), // "okPressed"
QT_MOC_LITERAL(8, 77, 9), // "noPressed"
QT_MOC_LITERAL(9, 87, 12) // "memChoiceSel"

    },
    "RandomSource\0choiceType\0\0RS_TYPES\0"
    "random_source\0memAlloc\0MEM_ALLOC\0"
    "okPressed\0noPressed\0memChoiceSel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RandomSource[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       5,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   45,    2, 0x09 /* Protected */,
       8,    0,   46,    2, 0x09 /* Protected */,
       9,    1,   47,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    2,

       0        // eod
};

void RandomSource::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RandomSource *_t = static_cast<RandomSource *>(_o);
        switch (_id) {
        case 0: _t->choiceType((*reinterpret_cast< RS_TYPES(*)>(_a[1]))); break;
        case 1: _t->memAlloc((*reinterpret_cast< MEM_ALLOC(*)>(_a[1]))); break;
        case 2: _t->okPressed(); break;
        case 3: _t->noPressed(); break;
        case 4: _t->memChoiceSel((*reinterpret_cast< MEM_ALLOC(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (RandomSource::*_t)(RS_TYPES );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RandomSource::choiceType)) {
                *result = 0;
            }
        }
        {
            typedef void (RandomSource::*_t)(MEM_ALLOC );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RandomSource::memAlloc)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject RandomSource::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_RandomSource.data,
      qt_meta_data_RandomSource,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RandomSource::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RandomSource::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RandomSource.stringdata))
        return static_cast<void*>(const_cast< RandomSource*>(this));
    return QDialog::qt_metacast(_clname);
}

int RandomSource::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void RandomSource::choiceType(RS_TYPES _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RandomSource::memAlloc(MEM_ALLOC _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
