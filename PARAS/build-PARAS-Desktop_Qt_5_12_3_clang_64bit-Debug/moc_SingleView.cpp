/****************************************************************************
** Meta object code from reading C++ file 'SingleView.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../PARAS/src/graphical/ruleview/singlerule/SingleView.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SingleView.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PARASProgram__Graphical__SingleView_t {
    QByteArrayData data[7];
    char stringdata0[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PARASProgram__Graphical__SingleView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PARASProgram__Graphical__SingleView_t qt_meta_stringdata_PARASProgram__Graphical__SingleView = {
    {
QT_MOC_LITERAL(0, 0, 35), // "PARASProgram::Graphical::Sing..."
QT_MOC_LITERAL(1, 36, 11), // "resetFilter"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 13), // "filterResults"
QT_MOC_LITERAL(4, 63, 14), // "changeViewMode"
QT_MOC_LITERAL(5, 78, 16), // "QAbstractButton*"
QT_MOC_LITERAL(6, 95, 13) // "clickedButton"

    },
    "PARASProgram::Graphical::SingleView\0"
    "resetFilter\0\0filterResults\0changeViewMode\0"
    "QAbstractButton*\0clickedButton"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PARASProgram__Graphical__SingleView[] = {

 // content:
       8,       // revision
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
       4,    1,   31,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,

       0        // eod
};

void PARASProgram::Graphical::SingleView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SingleView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resetFilter(); break;
        case 1: _t->filterResults(); break;
        case 2: _t->changeViewMode((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractButton* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PARASProgram::Graphical::SingleView::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_PARASProgram__Graphical__SingleView.data,
    qt_meta_data_PARASProgram__Graphical__SingleView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PARASProgram::Graphical::SingleView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PARASProgram::Graphical::SingleView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PARASProgram__Graphical__SingleView.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "EventListener"))
        return static_cast< EventListener*>(this);
    return QWidget::qt_metacast(_clname);
}

int PARASProgram::Graphical::SingleView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
