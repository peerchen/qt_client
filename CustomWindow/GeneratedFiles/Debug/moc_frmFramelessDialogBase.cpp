/****************************************************************************
** Meta object code from reading C++ file 'frmFramelessDialogBase.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Dialog/frmFramelessDialogBase.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmFramelessDialogBase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_frmFramelessDialogBase_t {
    QByteArrayData data[8];
    char stringdata0[121];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_frmFramelessDialogBase_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_frmFramelessDialogBase_t qt_meta_stringdata_frmFramelessDialogBase = {
    {
QT_MOC_LITERAL(0, 0, 22), // "frmFramelessDialogBase"
QT_MOC_LITERAL(1, 23, 14), // "setWindowTitle"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 4), // "text"
QT_MOC_LITERAL(4, 44, 26), // "on_applicationStateChanged"
QT_MOC_LITERAL(5, 71, 20), // "Qt::ApplicationState"
QT_MOC_LITERAL(6, 92, 5), // "state"
QT_MOC_LITERAL(7, 98, 22) // "on_closeButton_clicked"

    },
    "frmFramelessDialogBase\0setWindowTitle\0"
    "\0text\0on_applicationStateChanged\0"
    "Qt::ApplicationState\0state\0"
    "on_closeButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_frmFramelessDialogBase[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       4,    1,   32,    2, 0x08 /* Private */,
       7,    0,   35,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,

       0        // eod
};

void frmFramelessDialogBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        frmFramelessDialogBase *_t = static_cast<frmFramelessDialogBase *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setWindowTitle((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->on_applicationStateChanged((*reinterpret_cast< Qt::ApplicationState(*)>(_a[1]))); break;
        case 2: _t->on_closeButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject frmFramelessDialogBase::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_frmFramelessDialogBase.data,
      qt_meta_data_frmFramelessDialogBase,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *frmFramelessDialogBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *frmFramelessDialogBase::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_frmFramelessDialogBase.stringdata0))
        return static_cast<void*>(const_cast< frmFramelessDialogBase*>(this));
    return QDialog::qt_metacast(_clname);
}

int frmFramelessDialogBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
