/****************************************************************************
** Meta object code from reading C++ file 'StreamDataChart.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../U-BCI-src-211022/StreamData/StreamDataChart.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'StreamDataChart.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StreamDataChart_t {
    QByteArrayData data[14];
    char stringdata0[216];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StreamDataChart_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StreamDataChart_t qt_meta_stringdata_StreamDataChart = {
    {
QT_MOC_LITERAL(0, 0, 15), // "StreamDataChart"
QT_MOC_LITERAL(1, 16, 12), // "UpdateSeries"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 6), // "dataId"
QT_MOC_LITERAL(4, 37, 37), // "std::shared_ptr<std::vector<d..."
QT_MOC_LITERAL(5, 75, 14), // "timeSeriesData"
QT_MOC_LITERAL(6, 90, 13), // "timestampData"
QT_MOC_LITERAL(7, 104, 19), // "StreamDataSettings*"
QT_MOC_LITERAL(8, 124, 18), // "streamDataSettings"
QT_MOC_LITERAL(9, 143, 15), // "ChangeTimeWidth"
QT_MOC_LITERAL(10, 159, 13), // "ChangeChWidth"
QT_MOC_LITERAL(11, 173, 20), // "ChangeNumChDisplayed"
QT_MOC_LITERAL(12, 194, 11), // "ScrollYAxis"
QT_MOC_LITERAL(13, 206, 9) // "scrollVal"

    },
    "StreamDataChart\0UpdateSeries\0\0dataId\0"
    "std::shared_ptr<std::vector<double> >\0"
    "timeSeriesData\0timestampData\0"
    "StreamDataSettings*\0streamDataSettings\0"
    "ChangeTimeWidth\0ChangeChWidth\0"
    "ChangeNumChDisplayed\0ScrollYAxis\0"
    "scrollVal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StreamDataChart[] = {

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
       1,    4,   39,    2, 0x0a /* Public */,
       9,    0,   48,    2, 0x0a /* Public */,
      10,    0,   49,    2, 0x0a /* Public */,
      11,    0,   50,    2, 0x0a /* Public */,
      12,    1,   51,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Long, 0x80000000 | 4, 0x80000000 | 4, 0x80000000 | 7,    3,    5,    6,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   13,

       0        // eod
};

void StreamDataChart::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<StreamDataChart *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->UpdateSeries((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< const std::shared_ptr<std::vector<double> >(*)>(_a[2])),(*reinterpret_cast< const std::shared_ptr<std::vector<double> >(*)>(_a[3])),(*reinterpret_cast< StreamDataSettings*(*)>(_a[4]))); break;
        case 1: _t->ChangeTimeWidth(); break;
        case 2: _t->ChangeChWidth(); break;
        case 3: _t->ChangeNumChDisplayed(); break;
        case 4: _t->ScrollYAxis((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject StreamDataChart::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_StreamDataChart.data,
    qt_meta_data_StreamDataChart,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *StreamDataChart::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StreamDataChart::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StreamDataChart.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int StreamDataChart::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
