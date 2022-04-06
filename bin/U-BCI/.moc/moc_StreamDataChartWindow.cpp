/****************************************************************************
** Meta object code from reading C++ file 'StreamDataChartWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../U-BCI-src-211022/StreamData/StreamDataChartWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'StreamDataChartWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StreamDataChartWindow_t {
    QByteArrayData data[10];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StreamDataChartWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StreamDataChartWindow_t qt_meta_stringdata_StreamDataChartWindow = {
    {
QT_MOC_LITERAL(0, 0, 21), // "StreamDataChartWindow"
QT_MOC_LITERAL(1, 22, 15), // "ShowDataInChart"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 14), // "streamDataName"
QT_MOC_LITERAL(4, 54, 6), // "dataId"
QT_MOC_LITERAL(5, 61, 37), // "std::shared_ptr<std::vector<d..."
QT_MOC_LITERAL(6, 99, 14), // "timeSeriesData"
QT_MOC_LITERAL(7, 114, 13), // "timestampData"
QT_MOC_LITERAL(8, 128, 19), // "StreamDataSettings*"
QT_MOC_LITERAL(9, 148, 18) // "streamDataSettings"

    },
    "StreamDataChartWindow\0ShowDataInChart\0"
    "\0streamDataName\0dataId\0"
    "std::shared_ptr<std::vector<double> >\0"
    "timeSeriesData\0timestampData\0"
    "StreamDataSettings*\0streamDataSettings"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StreamDataChartWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    5,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Long, 0x80000000 | 5, 0x80000000 | 5, 0x80000000 | 8,    3,    4,    6,    7,    9,

       0        // eod
};

void StreamDataChartWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<StreamDataChartWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ShowDataInChart((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2])),(*reinterpret_cast< const std::shared_ptr<std::vector<double> >(*)>(_a[3])),(*reinterpret_cast< const std::shared_ptr<std::vector<double> >(*)>(_a[4])),(*reinterpret_cast< StreamDataSettings*(*)>(_a[5]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject StreamDataChartWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_StreamDataChartWindow.data,
    qt_meta_data_StreamDataChartWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *StreamDataChartWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StreamDataChartWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StreamDataChartWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int StreamDataChartWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
