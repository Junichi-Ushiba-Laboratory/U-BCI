/****************************************************************************
** Meta object code from reading C++ file 'StreamDataPreprocessor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../U-BCI-src-211022/StreamData/StreamDataPreprocessor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'StreamDataPreprocessor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StreamDataPreprocessor_t {
    QByteArrayData data[17];
    char stringdata0[301];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StreamDataPreprocessor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StreamDataPreprocessor_t qt_meta_stringdata_StreamDataPreprocessor = {
    {
QT_MOC_LITERAL(0, 0, 22), // "StreamDataPreprocessor"
QT_MOC_LITERAL(1, 23, 13), // "DataAvailable"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 14), // "streamDataName"
QT_MOC_LITERAL(4, 53, 6), // "dataId"
QT_MOC_LITERAL(5, 60, 37), // "std::shared_ptr<std::vector<d..."
QT_MOC_LITERAL(6, 98, 14), // "timeSeriesData"
QT_MOC_LITERAL(7, 113, 13), // "timestampData"
QT_MOC_LITERAL(8, 127, 19), // "StreamDataSettings*"
QT_MOC_LITERAL(9, 147, 18), // "streamDataSettings"
QT_MOC_LITERAL(10, 166, 20), // "RequestRecordingStop"
QT_MOC_LITERAL(11, 187, 5), // "title"
QT_MOC_LITERAL(12, 193, 7), // "message"
QT_MOC_LITERAL(13, 201, 31), // "ConnectToOnlineProcessingModule"
QT_MOC_LITERAL(14, 233, 23), // "OnlineProcessingModule*"
QT_MOC_LITERAL(15, 257, 22), // "onlineProcessingModule"
QT_MOC_LITERAL(16, 280, 20) // "PreprocessStreamData"

    },
    "StreamDataPreprocessor\0DataAvailable\0"
    "\0streamDataName\0dataId\0"
    "std::shared_ptr<std::vector<double> >\0"
    "timeSeriesData\0timestampData\0"
    "StreamDataSettings*\0streamDataSettings\0"
    "RequestRecordingStop\0title\0message\0"
    "ConnectToOnlineProcessingModule\0"
    "OnlineProcessingModule*\0onlineProcessingModule\0"
    "PreprocessStreamData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StreamDataPreprocessor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    5,   34,    2, 0x06 /* Public */,
      10,    2,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    1,   50,    2, 0x0a /* Public */,
      16,    0,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Long, 0x80000000 | 5, 0x80000000 | 5, 0x80000000 | 8,    3,    4,    6,    7,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   11,   12,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void,

       0        // eod
};

void StreamDataPreprocessor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<StreamDataPreprocessor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->DataAvailable((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2])),(*reinterpret_cast< const std::shared_ptr<std::vector<double> >(*)>(_a[3])),(*reinterpret_cast< const std::shared_ptr<std::vector<double> >(*)>(_a[4])),(*reinterpret_cast< StreamDataSettings*(*)>(_a[5]))); break;
        case 1: _t->RequestRecordingStop((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->ConnectToOnlineProcessingModule((*reinterpret_cast< OnlineProcessingModule*(*)>(_a[1]))); break;
        case 3: _t->PreprocessStreamData(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< OnlineProcessingModule* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (StreamDataPreprocessor::*)(const QString & , long , const std::shared_ptr<std::vector<double>> , const std::shared_ptr<std::vector<double>> , StreamDataSettings * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StreamDataPreprocessor::DataAvailable)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (StreamDataPreprocessor::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StreamDataPreprocessor::RequestRecordingStop)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject StreamDataPreprocessor::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_StreamDataPreprocessor.data,
    qt_meta_data_StreamDataPreprocessor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *StreamDataPreprocessor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StreamDataPreprocessor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StreamDataPreprocessor.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int StreamDataPreprocessor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void StreamDataPreprocessor::DataAvailable(const QString & _t1, long _t2, const std::shared_ptr<std::vector<double>> _t3, const std::shared_ptr<std::vector<double>> _t4, StreamDataSettings * _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void StreamDataPreprocessor::RequestRecordingStop(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
