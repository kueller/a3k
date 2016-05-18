/****************************************************************************
** Meta object code from reading C++ file 'a3kconsole.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "a3kconsole.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'a3kconsole.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_a3kconsole_t {
    QByteArrayData data[3];
    char stringdata0[23];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_a3kconsole_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_a3kconsole_t qt_meta_stringdata_a3kconsole = {
    {
QT_MOC_LITERAL(0, 0, 10), // "a3kconsole"
QT_MOC_LITERAL(1, 11, 10), // "write_char"
QT_MOC_LITERAL(2, 22, 0) // ""

    },
    "a3kconsole\0write_char\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_a3kconsole[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    2,    2,

       0        // eod
};

void a3kconsole::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        a3kconsole *_t = static_cast<a3kconsole *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->write_char((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject a3kconsole::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_a3kconsole.data,
      qt_meta_data_a3kconsole,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *a3kconsole::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *a3kconsole::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_a3kconsole.stringdata0))
        return static_cast<void*>(const_cast< a3kconsole*>(this));
    return QDialog::qt_metacast(_clname);
}

int a3kconsole::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
