/****************************************************************************
** Meta object code from reading C++ file 'PSpaceGraph.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PARAS/src/graphical/PSpaceGraph.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PSpaceGraph.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PARASProgram__Graphical__PSpaceGraph_t {
    QByteArrayData data[11];
    char stringdata[162];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_PARASProgram__Graphical__PSpaceGraph_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_PARASProgram__Graphical__PSpaceGraph_t qt_meta_stringdata_PARASProgram__Graphical__PSpaceGraph = {
    {
QT_MOC_LITERAL(0, 0, 36),
QT_MOC_LITERAL(1, 37, 9),
QT_MOC_LITERAL(2, 47, 0),
QT_MOC_LITERAL(3, 48, 12),
QT_MOC_LITERAL(4, 61, 17),
QT_MOC_LITERAL(5, 79, 15),
QT_MOC_LITERAL(6, 95, 13),
QT_MOC_LITERAL(7, 109, 13),
QT_MOC_LITERAL(8, 123, 12),
QT_MOC_LITERAL(9, 136, 22),
QT_MOC_LITERAL(10, 159, 1)
    },
    "PARASProgram::Graphical::PSpaceGraph\0"
    "slotRMode\0\0colorChooser\0updateGranularity\0"
    "updateGridLines\0updateSkyline\0"
    "setRedundancy\0SupConfInput\0"
    "updateShownGranularity\0g\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PARASProgram__Graphical__PSpaceGraph[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a,
       3,    0,   55,    2, 0x0a,
       4,    0,   56,    2, 0x0a,
       5,    0,   57,    2, 0x0a,
       6,    0,   58,    2, 0x0a,
       7,    0,   59,    2, 0x0a,
       8,    0,   60,    2, 0x0a,
       9,    1,   61,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,

       0        // eod
};

void PARASProgram::Graphical::PSpaceGraph::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PSpaceGraph *_t = static_cast<PSpaceGraph *>(_o);
        switch (_id) {
        case 0: _t->slotRMode(); break;
        case 1: _t->colorChooser(); break;
        case 2: _t->updateGranularity(); break;
        case 3: _t->updateGridLines(); break;
        case 4: _t->updateSkyline(); break;
        case 5: _t->setRedundancy(); break;
        case 6: _t->SupConfInput(); break;
        case 7: _t->updateShownGranularity((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject PARASProgram::Graphical::PSpaceGraph::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PARASProgram__Graphical__PSpaceGraph.data,
      qt_meta_data_PARASProgram__Graphical__PSpaceGraph,  qt_static_metacall, 0, 0}
};


const QMetaObject *PARASProgram::Graphical::PSpaceGraph::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PARASProgram::Graphical::PSpaceGraph::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PARASProgram__Graphical__PSpaceGraph.stringdata))
        return static_cast<void*>(const_cast< PSpaceGraph*>(this));
    if (!strcmp(_clname, "EventListener"))
        return static_cast< EventListener*>(const_cast< PSpaceGraph*>(this));
    return QWidget::qt_metacast(_clname);
}

int PARASProgram::Graphical::PSpaceGraph::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
