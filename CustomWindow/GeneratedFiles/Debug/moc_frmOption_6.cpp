/****************************************************************************
** Meta object code from reading C++ file 'frmOption_6.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Dialog/frmOption_6.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmOption_6.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_frmOption_6_t {
    QByteArrayData data[10];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_frmOption_6_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_frmOption_6_t qt_meta_stringdata_frmOption_6 = {
    {
QT_MOC_LITERAL(0, 0, 11), // "frmOption_6"
QT_MOC_LITERAL(1, 12, 13), // "ProcessSelect"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 3), // "row"
QT_MOC_LITERAL(4, 31, 3), // "col"
QT_MOC_LITERAL(5, 35, 6), // "slotUp"
QT_MOC_LITERAL(6, 42, 8), // "slotDown"
QT_MOC_LITERAL(7, 51, 7), // "slotAll"
QT_MOC_LITERAL(8, 59, 9), // "slotUnAll"
QT_MOC_LITERAL(9, 69, 11) // "slotDefault"

    },
    "frmOption_6\0ProcessSelect\0\0row\0col\0"
    "slotUp\0slotDown\0slotAll\0slotUnAll\0"
    "slotDefault"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_frmOption_6[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x0a /* Public */,
       5,    0,   49,    2, 0x0a /* Public */,
       6,    0,   50,    2, 0x0a /* Public */,
       7,    0,   51,    2, 0x0a /* Public */,
       8,    0,   52,    2, 0x0a /* Public */,
       9,    0,   53,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void frmOption_6::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        frmOption_6 *_t = static_cast<frmOption_6 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ProcessSelect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->slotUp(); break;
        case 2: _t->slotDown(); break;
        case 3: _t->slotAll(); break;
        case 4: _t->slotUnAll(); break;
        case 5: _t->slotDefault(); break;
        default: ;
        }
    }
}

const QMetaObject frmOption_6::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_frmOption_6.data,
      qt_meta_data_frmOption_6,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *frmOption_6::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *frmOption_6::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_frmOption_6.stringdata0))
        return static_cast<void*>(const_cast< frmOption_6*>(this));
    if (!strcmp(_clname, "frmOption_base"))
        return static_cast< frmOption_base*>(const_cast< frmOption_6*>(this));
    return QWidget::qt_metacast(_clname);
}

int frmOption_6::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
