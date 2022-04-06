/****************************************************************************
** Meta object code from reading C++ file 'OnlineProcessingModule.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../U-BCI-src-211022/OnlineProcessingModule/OnlineProcessingModule.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'OnlineProcessingModule.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OnlineProcessingModule_t {
    QByteArrayData data[16];
    char stringdata0[258];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OnlineProcessingModule_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OnlineProcessingModule_t qt_meta_stringdata_OnlineProcessingModule = {
    {
QT_MOC_LITERAL(0, 0, 22), // "OnlineProcessingModule"
QT_MOC_LITERAL(1, 23, 13), // "DataAvailable"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 26), // "onlineProcessingModuleName"
QT_MOC_LITERAL(4, 65, 37), // "std::shared_ptr<std::vector<d..."
QT_MOC_LITERAL(5, 103, 11), // "resultsData"
QT_MOC_LITERAL(6, 115, 20), // "RequestRecordingStop"
QT_MOC_LITERAL(7, 136, 5), // "title"
QT_MOC_LITERAL(8, 142, 7), // "message"
QT_MOC_LITERAL(9, 150, 17), // "ReceiveStreamData"
QT_MOC_LITERAL(10, 168, 14), // "streamDataName"
QT_MOC_LITERAL(11, 183, 6), // "dataId"
QT_MOC_LITERAL(12, 190, 14), // "timeSeriesData"
QT_MOC_LITERAL(13, 205, 13), // "timestampData"
QT_MOC_LITERAL(14, 219, 19), // "StreamDataSettings*"
QT_MOC_LITERAL(15, 239, 18) // "streamDataSettings"

    },
    "OnlineProcessingModule\0DataAvailable\0"
    "\0onlineProcessingModuleName\0"
    "std::shared_ptr<std::vector<double> >\0"
    "resultsData\0RequestRecordingStop\0title\0"
    "message\0ReceiveStreamData\0streamDataName\0"
    "dataId\0timeSeriesData\0timestampData\0"
    "StreamDataSettings*\0streamDataSettings"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OnlineProcessingModule[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,
       6,    2,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    5,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Long, 0x80000000 | 4, 0x80000000 | 4, 0x80000000 | 14,   10,   11,   12,   13,   15,

       0        // eod
};

void OnlineProcessingModule::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<OnlineProcessingModule *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->DataAvailable((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const std::shared_ptr<std::vector<double> >(*)>(_a[2]))); break;
        case 1: _t->RequestRecordingStop((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->ReceiveStreamData((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2])),(*reinterpret_cast< const std::shared_ptr<std::vector<double> >(*)>(_a[3])),(*reinterpret_cast< const std::shared_ptr<std::vector<double> >(*)>(_a[4])),(*reinterpret_cast< StreamDataSettings*(*)>(_a[5]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (OnlineProcessingModule::*)(const QString & , const std::shared_ptr<std::vector<double>> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OnlineProcessingModule::DataAvailable)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (OnlineProcessingModule::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OnlineProcessingModule::RequestRecordingStop)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject OnlineProcessingModule::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_OnlineProcessingModule.data,
    qt_meta_data_OnlineProcessingModule,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *OnlineProcessingModule::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OnlineProcessingModule::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OnlineProcessingModule.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int OnlineProcessingModule::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void OnlineProcessingModule::DataAvailable(const QString & _t1, const std::shared_ptr<std::vector<double>> _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void OnlineProcessingModule::RequestRecordingStop(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
