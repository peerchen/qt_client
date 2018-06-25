/****************************************************************************
** Meta object code from reading C++ file 'frmHistoryWTSearchDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Dialog/frmHistoryWTSearchDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmHistoryWTSearchDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_frmHistoryWTSearchDialog_t {
    QByteArrayData data[13];
    char stringdata0[259];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_frmHistoryWTSearchDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_frmHistoryWTSearchDialog_t qt_meta_stringdata_frmHistoryWTSearchDialog = {
    {
QT_MOC_LITERAL(0, 0, 24), // "frmHistoryWTSearchDialog"
QT_MOC_LITERAL(1, 25, 22), // "OnBnClickedButtonQuery"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 24), // "OnBnClickedButtonFirpage"
QT_MOC_LITERAL(4, 74, 24), // "OnBnClickedButtonPrepage"
QT_MOC_LITERAL(5, 99, 24), // "OnBnClickedButtonNexpage"
QT_MOC_LITERAL(6, 124, 24), // "OnBnClickedButtonLaspage"
QT_MOC_LITERAL(7, 149, 18), // "comboBoxNumChanged"
QT_MOC_LITERAL(8, 168, 3), // "str"
QT_MOC_LITERAL(9, 172, 19), // "comboBoxPageChanged"
QT_MOC_LITERAL(10, 192, 27), // "OnCbnSelchangeComboProdCode"
QT_MOC_LITERAL(11, 220, 20), // "OnBnClickedOutTExcel"
QT_MOC_LITERAL(12, 241, 17) // "OnBnClickedOption"

    },
    "frmHistoryWTSearchDialog\0"
    "OnBnClickedButtonQuery\0\0"
    "OnBnClickedButtonFirpage\0"
    "OnBnClickedButtonPrepage\0"
    "OnBnClickedButtonNexpage\0"
    "OnBnClickedButtonLaspage\0comboBoxNumChanged\0"
    "str\0comboBoxPageChanged\0"
    "OnCbnSelchangeComboProdCode\0"
    "OnBnClickedOutTExcel\0OnBnClickedOption"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_frmHistoryWTSearchDialog[] = {

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
       7,    1,   69,    2, 0x0a /* Public */,
       9,    1,   72,    2, 0x0a /* Public */,
      10,    1,   75,    2, 0x0a /* Public */,
      11,    0,   78,    2, 0x0a /* Public */,
      12,    0,   79,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void frmHistoryWTSearchDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        frmHistoryWTSearchDialog *_t = static_cast<frmHistoryWTSearchDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnBnClickedButtonQuery(); break;
        case 1: _t->OnBnClickedButtonFirpage(); break;
        case 2: _t->OnBnClickedButtonPrepage(); break;
        case 3: _t->OnBnClickedButtonNexpage(); break;
        case 4: _t->OnBnClickedButtonLaspage(); break;
        case 5: _t->comboBoxNumChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->comboBoxPageChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->OnCbnSelchangeComboProdCode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->OnBnClickedOutTExcel(); break;
        case 9: _t->OnBnClickedOption(); break;
        default: ;
        }
    }
}

const QMetaObject frmHistoryWTSearchDialog::staticMetaObject = {
    { &frmFramelessDialogBase::staticMetaObject, qt_meta_stringdata_frmHistoryWTSearchDialog.data,
      qt_meta_data_frmHistoryWTSearchDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *frmHistoryWTSearchDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *frmHistoryWTSearchDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_frmHistoryWTSearchDialog.stringdata0))
        return static_cast<void*>(const_cast< frmHistoryWTSearchDialog*>(this));
    if (!strcmp(_clname, "CHJQueryBase"))
        return static_cast< CHJQueryBase*>(const_cast< frmHistoryWTSearchDialog*>(this));
    return frmFramelessDialogBase::qt_metacast(_clname);
}

int frmHistoryWTSearchDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
