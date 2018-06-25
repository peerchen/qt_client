/****************************************************************************
** Meta object code from reading C++ file 'frmlogindialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Dialog/frmlogindialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmlogindialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_frmLoginDialog_t {
    QByteArrayData data[10];
    char stringdata0[89];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_frmLoginDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_frmLoginDialog_t qt_meta_stringdata_frmLoginDialog = {
    {
QT_MOC_LITERAL(0, 0, 14), // "frmLoginDialog"
QT_MOC_LITERAL(1, 15, 6), // "notify"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 3), // "str"
QT_MOC_LITERAL(4, 27, 9), // "checkInfo"
QT_MOC_LITERAL(5, 37, 7), // "exitSys"
QT_MOC_LITERAL(6, 45, 10), // "CheckInput"
QT_MOC_LITERAL(7, 56, 11), // "refreshCode"
QT_MOC_LITERAL(8, 68, 11), // "timerUpdate"
QT_MOC_LITERAL(9, 80, 8) // "OnNotify"

    },
    "frmLoginDialog\0notify\0\0str\0checkInfo\0"
    "exitSys\0CheckInput\0refreshCode\0"
    "timerUpdate\0OnNotify"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_frmLoginDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   52,    2, 0x0a /* Public */,
       5,    0,   53,    2, 0x0a /* Public */,
       6,    0,   54,    2, 0x0a /* Public */,
       7,    0,   55,    2, 0x0a /* Public */,
       8,    0,   56,    2, 0x0a /* Public */,
       9,    1,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void frmLoginDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        frmLoginDialog *_t = static_cast<frmLoginDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->notify((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->checkInfo(); break;
        case 2: _t->exitSys(); break;
        case 3: { bool _r = _t->CheckInput();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: _t->refreshCode(); break;
        case 5: _t->timerUpdate(); break;
        case 6: _t->OnNotify((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (frmLoginDialog::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&frmLoginDialog::notify)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject frmLoginDialog::staticMetaObject = {
    { &StyleSheetDialog::staticMetaObject, qt_meta_stringdata_frmLoginDialog.data,
      qt_meta_data_frmLoginDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *frmLoginDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *frmLoginDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_frmLoginDialog.stringdata0))
        return static_cast<void*>(const_cast< frmLoginDialog*>(this));
    return StyleSheetDialog::qt_metacast(_clname);
}

int frmLoginDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = StyleSheetDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void frmLoginDialog::notify(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
