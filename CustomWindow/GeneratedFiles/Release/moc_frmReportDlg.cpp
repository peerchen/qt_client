/****************************************************************************
** Meta object code from reading C++ file 'frmReportDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Dialog/frmReportDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmReportDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_frmReportDlg_t {
    QByteArrayData data[7];
    char stringdata0[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_frmReportDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_frmReportDlg_t qt_meta_stringdata_frmReportDlg = {
    {
QT_MOC_LITERAL(0, 0, 12), // "frmReportDlg"
QT_MOC_LITERAL(1, 13, 9), // "slotPrint"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 12), // "slotOutExcel"
QT_MOC_LITERAL(4, 37, 16), // "printPreviewSlot"
QT_MOC_LITERAL(5, 54, 9), // "QPrinter*"
QT_MOC_LITERAL(6, 64, 12) // "printerImage"

    },
    "frmReportDlg\0slotPrint\0\0slotOutExcel\0"
    "printPreviewSlot\0QPrinter*\0printerImage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_frmReportDlg[] = {

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
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    1,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,

       0        // eod
};

void frmReportDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        frmReportDlg *_t = static_cast<frmReportDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotPrint(); break;
        case 1: _t->slotOutExcel(); break;
        case 2: _t->printPreviewSlot((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject frmReportDlg::staticMetaObject = {
    { &frmFramelessDialogBase::staticMetaObject, qt_meta_stringdata_frmReportDlg.data,
      qt_meta_data_frmReportDlg,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *frmReportDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *frmReportDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_frmReportDlg.stringdata0))
        return static_cast<void*>(const_cast< frmReportDlg*>(this));
    return frmFramelessDialogBase::qt_metacast(_clname);
}

int frmReportDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = frmFramelessDialogBase::qt_metacall(_c, _id, _a);
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
