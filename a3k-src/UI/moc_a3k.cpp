/****************************************************************************
** Meta object code from reading C++ file 'a3k.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "a3k.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'a3k.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_a3k_t {
    QByteArrayData data[16];
    char stringdata0[324];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_a3k_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_a3k_t qt_meta_stringdata_a3k = {
    {
QT_MOC_LITERAL(0, 0, 3), // "a3k"
QT_MOC_LITERAL(1, 4, 15), // "vidMemoryUpdate"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 28), // "on_actionLoad_File_triggered"
QT_MOC_LITERAL(4, 50, 34), // "on_actionJump_To_Address_trig..."
QT_MOC_LITERAL(5, 85, 31), // "on_actionShow_Console_triggered"
QT_MOC_LITERAL(6, 117, 8), // "run_next"
QT_MOC_LITERAL(7, 126, 20), // "on_runButton_clicked"
QT_MOC_LITERAL(8, 147, 24), // "on_runFastButton_clicked"
QT_MOC_LITERAL(9, 172, 21), // "on_stepButton_clicked"
QT_MOC_LITERAL(10, 194, 22), // "on_pauseButton_clicked"
QT_MOC_LITERAL(11, 217, 21), // "on_stopButton_clicked"
QT_MOC_LITERAL(12, 239, 23), // "on_actionExit_triggered"
QT_MOC_LITERAL(13, 263, 28), // "on_actionSet_Speed_triggered"
QT_MOC_LITERAL(14, 292, 15), // "jump_to_address"
QT_MOC_LITERAL(15, 308, 15) // "set_timer_speed"

    },
    "a3k\0vidMemoryUpdate\0\0on_actionLoad_File_triggered\0"
    "on_actionJump_To_Address_triggered\0"
    "on_actionShow_Console_triggered\0"
    "run_next\0on_runButton_clicked\0"
    "on_runFastButton_clicked\0on_stepButton_clicked\0"
    "on_pauseButton_clicked\0on_stopButton_clicked\0"
    "on_actionExit_triggered\0"
    "on_actionSet_Speed_triggered\0"
    "jump_to_address\0set_timer_speed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_a3k[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   89,    2, 0x08 /* Private */,
       4,    0,   90,    2, 0x08 /* Private */,
       5,    0,   91,    2, 0x08 /* Private */,
       6,    0,   92,    2, 0x08 /* Private */,
       7,    0,   93,    2, 0x08 /* Private */,
       8,    0,   94,    2, 0x08 /* Private */,
       9,    0,   95,    2, 0x08 /* Private */,
      10,    0,   96,    2, 0x08 /* Private */,
      11,    0,   97,    2, 0x08 /* Private */,
      12,    0,   98,    2, 0x08 /* Private */,
      13,    0,   99,    2, 0x08 /* Private */,
      14,    1,  100,    2, 0x0a /* Public */,
      15,    1,  103,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void a3k::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        a3k *_t = static_cast<a3k *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->vidMemoryUpdate((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->on_actionLoad_File_triggered(); break;
        case 2: _t->on_actionJump_To_Address_triggered(); break;
        case 3: _t->on_actionShow_Console_triggered(); break;
        case 4: { bool _r = _t->run_next();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: _t->on_runButton_clicked(); break;
        case 6: _t->on_runFastButton_clicked(); break;
        case 7: _t->on_stepButton_clicked(); break;
        case 8: _t->on_pauseButton_clicked(); break;
        case 9: _t->on_stopButton_clicked(); break;
        case 10: _t->on_actionExit_triggered(); break;
        case 11: _t->on_actionSet_Speed_triggered(); break;
        case 12: _t->jump_to_address((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->set_timer_speed((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (a3k::*_t)(QString , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&a3k::vidMemoryUpdate)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject a3k::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_a3k.data,
      qt_meta_data_a3k,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *a3k::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *a3k::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_a3k.stringdata0))
        return static_cast<void*>(const_cast< a3k*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int a3k::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void a3k::vidMemoryUpdate(QString _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
