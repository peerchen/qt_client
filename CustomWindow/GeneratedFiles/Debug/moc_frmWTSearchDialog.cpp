/****************************************************************************
** Meta object code from reading C++ file 'frmWTSearchDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Dialog/frmWTSearchDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmWTSearchDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_frmWTSearchDialog_t {
    QByteArrayData data[13];
    char stringdata0[252];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_frmWTSearchDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_frmWTSearchDialog_t qt_meta_stringdata_frmWTSearchDialog = {
    {
QT_MOC_LITERAL(0, 0, 17), // "frmWTSearchDialog"
QT_MOC_LITERAL(1, 18, 22), // "OnBnClickedButtonQuery"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 24), // "OnBnClickedButtonFirpage"
QT_MOC_LITERAL(4, 67, 24), // "OnBnClickedButtonPrepage"
QT_MOC_LITERAL(5, 92, 24), // "OnBnClickedButtonNexpage"
QT_MOC_LITERAL(6, 117, 24), // "OnBnClickedButtonLaspage"
QT_MOC_LITERAL(7, 142, 20), // "OnBnClickedOutTExcel"
QT_MOC_LITERAL(8, 163, 17), // "OnBnClickedOption"
QT_MOC_LITERAL(9, 181, 18), // "comboBoxNumChanged"
QT_MOC_LITERAL(10, 200, 3), // "str"
QT_MOC_LITERAL(11, 204, 19), // "comboBoxPageChanged"
QT_MOC_LITERAL(12, 224, 27) // "OnCbnSelchangeComboProdCode"

    },
    "frmWTSearchDialog\0OnBnClickedButtonQuery\0"
    "\0OnBnClickedButtonFirpage\0"
    "OnBnClickedButtonPrepage\0"
    "OnBnClickedButtonNexpage\0"
    "OnBnClickedButtonLaspage\0OnBnClickedOutTExcel\0"
    "OnBnClickedOption\0comboBoxNumChanged\0"
    "str\0comboBoxPageChanged\0"
    "OnCbnSelchangeComboProdCode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_frmWTSearchDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a /* Public */,
       3,    0,   65,    2, 0x0a /* Public */,
       4,    0,   66,    2, 0x0a /* Public */,
       5,    0,   67,    2, 0x0a /* Public */,
       6,    0,   68,    2, 0x0a /* Public */,
       7,    0,   69,    2, 0x0a /* Public */,
       8,    0,   70,    2, 0x0a /* Public */,
       9,    1,   71,    2, 0x0a /* Public */,
      11,    1,   74,    2, 0x0a /* Public */,
      12,    1,   77,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   10,

       0        // eod
};

void frmWTSearchDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        frmWTSearchDialog *_t = static_cast<frmWTSearchDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnBnClickedButtonQuery(); break;
        case 1: _t->OnBnClickedButtonFirpage(); break;
        case 2: _t->OnBnClickedButtonPrepage(); break;
        case 3: _t->OnBnClickedButtonNexpage(); break;
        case 4: _t->OnBnClickedButtonLaspage(); break;
        case 5: _t->OnBnClickedOutTExcel(); break;
        case 6: _t->OnBnClickedOption(); break;
        case 7: _t->comboBoxNumChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->comboBoxPageChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->OnCbnSelchangeComboProdCode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject frmWTSearchDialog::staticMetaObject = {
    { &frmFramelessDialogBase::staticMetaObject, qt_meta_stringdata_frmWTSearchDialog.data,
      qt_meta_data_frmWTSearchDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *frmWTSearchDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *frmWTSearchDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_frmWTSearchDialog.stringdata0))
        return static_cast<void*>(const_cast< frmWTSearchDialog*>(this));
    if (!strcmp(_clname, "CHJQueryBase"))
        return static_cast< CHJQueryBase*>(const_cast< frmWTSearchDialog*>(this));
    return frmFramelessDialogBase::qt_metacast(_clname);
}

int frmWTSearchDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = frmFramelessDialogBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
