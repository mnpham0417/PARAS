/****************************************************************************
** Meta object code from reading C++ file 'GlyphView.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../PARAS/src/graphical/ruleview/singlerule/glyph/GlyphView.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GlyphView.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PARASProgram__Graphical__GlyphView_t {
    QByteArrayData data[10];
    char stringdata0[134];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PARASProgram__Graphical__GlyphView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PARASProgram__Graphical__GlyphView_t qt_meta_stringdata_PARASProgram__Graphical__GlyphView = {
    {
QT_MOC_LITERAL(0, 0, 34), // "PARASProgram::Graphical::Glyp..."
QT_MOC_LITERAL(1, 35, 17), // "toggleConnections"
QT_MOC_LITERAL(2, 53, 0), // ""
QT_MOC_LITERAL(3, 54, 16), // "QAbstractButton*"
QT_MOC_LITERAL(4, 71, 1), // "e"
QT_MOC_LITERAL(5, 73, 10), // "toggleFill"
QT_MOC_LITERAL(6, 84, 13), // "toggleMissing"
QT_MOC_LITERAL(7, 98, 16), // "toggleDetailView"
QT_MOC_LITERAL(8, 115, 10), // "setGrouped"
QT_MOC_LITERAL(9, 126, 7) // "clicked"

    },
    "PARASProgram::Graphical::GlyphView\0"
    "toggleConnections\0\0QAbstractButton*\0"
    "e\0toggleFill\0toggleMissing\0toggleDetailView\0"
    "setGrouped\0clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PARASProgram__Graphical__GlyphView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x08 /* Private */,
       5,    1,   42,    2, 0x08 /* Private */,
       6,    1,   45,    2, 0x08 /* Private */,
       7,    1,   48,    2, 0x08 /* Private */,
       8,    1,   51,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int,    9,

       0        // eod
};

void PARASProgram::Graphical::GlyphView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GlyphView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->toggleConnections((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 1: _t->toggleFill((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 2: _t->toggleMissing((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 3: _t->toggleDetailView((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 4: _t->setGrouped((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractButton* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractButton* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractButton* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractButton* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PARASProgram::Graphical::GlyphView::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_PARASProgram__Graphical__GlyphView.data,
    qt_meta_data_PARASProgram__Graphical__GlyphView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PARASProgram::Graphical::GlyphView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PARASProgram::Graphical::GlyphView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PARASProgram__Graphical__GlyphView.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PARASProgram::Graphical::GlyphView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
