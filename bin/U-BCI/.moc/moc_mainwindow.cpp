/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../U-BCI-src-211022/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[31];
    char stringdata0[414];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 28), // "DisableStreamDataChartWindow"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 11), // "qWindowName"
QT_MOC_LITERAL(4, 53, 13), // "StopRecording"
QT_MOC_LITERAL(5, 67, 5), // "title"
QT_MOC_LITERAL(6, 73, 7), // "message"
QT_MOC_LITERAL(7, 81, 12), // "statusUpdate"
QT_MOC_LITERAL(8, 94, 10), // "closeEvent"
QT_MOC_LITERAL(9, 105, 12), // "QCloseEvent*"
QT_MOC_LITERAL(10, 118, 2), // "ev"
QT_MOC_LITERAL(11, 121, 13), // "blockSelected"
QT_MOC_LITERAL(12, 135, 5), // "block"
QT_MOC_LITERAL(13, 141, 14), // "refreshStreams"
QT_MOC_LITERAL(14, 156, 29), // "std::vector<lsl::stream_info>"
QT_MOC_LITERAL(15, 186, 14), // "startRecording"
QT_MOC_LITERAL(16, 201, 13), // "stopRecording"
QT_MOC_LITERAL(17, 215, 16), // "selectAllStreams"
QT_MOC_LITERAL(18, 232, 15), // "selectNoStreams"
QT_MOC_LITERAL(19, 248, 13), // "buildFilename"
QT_MOC_LITERAL(20, 262, 17), // "buildBidsTemplate"
QT_MOC_LITERAL(21, 280, 21), // "printReplacedFilename"
QT_MOC_LITERAL(22, 302, 9), // "enableRcs"
QT_MOC_LITERAL(23, 312, 7), // "bEnable"
QT_MOC_LITERAL(24, 320, 18), // "rcsCheckBoxChanged"
QT_MOC_LITERAL(25, 339, 7), // "checked"
QT_MOC_LITERAL(26, 347, 17), // "rcsUpdateFilename"
QT_MOC_LITERAL(27, 365, 1), // "s"
QT_MOC_LITERAL(28, 367, 17), // "rcsStartRecording"
QT_MOC_LITERAL(29, 385, 22), // "rcsportValueChangedInt"
QT_MOC_LITERAL(30, 408, 5) // "value"

    },
    "MainWindow\0DisableStreamDataChartWindow\0"
    "\0qWindowName\0StopRecording\0title\0"
    "message\0statusUpdate\0closeEvent\0"
    "QCloseEvent*\0ev\0blockSelected\0block\0"
    "refreshStreams\0std::vector<lsl::stream_info>\0"
    "startRecording\0stopRecording\0"
    "selectAllStreams\0selectNoStreams\0"
    "buildFilename\0buildBidsTemplate\0"
    "printReplacedFilename\0enableRcs\0bEnable\0"
    "rcsCheckBoxChanged\0checked\0rcsUpdateFilename\0"
    "s\0rcsStartRecording\0rcsportValueChangedInt\0"
    "value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  104,    2, 0x0a /* Public */,
       4,    2,  107,    2, 0x0a /* Public */,
       7,    0,  112,    2, 0x08 /* Private */,
       8,    1,  113,    2, 0x08 /* Private */,
      11,    1,  116,    2, 0x08 /* Private */,
      13,    0,  119,    2, 0x08 /* Private */,
      15,    0,  120,    2, 0x08 /* Private */,
      16,    0,  121,    2, 0x08 /* Private */,
      17,    0,  122,    2, 0x08 /* Private */,
      18,    0,  123,    2, 0x08 /* Private */,
      19,    0,  124,    2, 0x08 /* Private */,
      20,    0,  125,    2, 0x08 /* Private */,
      21,    0,  126,    2, 0x08 /* Private */,
      22,    1,  127,    2, 0x08 /* Private */,
      24,    1,  130,    2, 0x08 /* Private */,
      26,    1,  133,    2, 0x08 /* Private */,
      28,    0,  136,    2, 0x08 /* Private */,
      29,    1,  137,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::QString,   12,
    0x80000000 | 14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   23,
    QMetaType::Void, QMetaType::Bool,   25,
    QMetaType::Void, QMetaType::QString,   27,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   30,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->DisableStreamDataChartWindow((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->StopRecording((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->statusUpdate(); break;
        case 3: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 4: _t->blockSelected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: { std::vector<lsl::stream_info> _r = _t->refreshStreams();
            if (_a[0]) *reinterpret_cast< std::vector<lsl::stream_info>*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->startRecording(); break;
        case 7: _t->stopRecording(); break;
        case 8: _t->selectAllStreams(); break;
        case 9: _t->selectNoStreams(); break;
        case 10: _t->buildFilename(); break;
        case 11: _t->buildBidsTemplate(); break;
        case 12: _t->printReplacedFilename(); break;
        case 13: _t->enableRcs((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->rcsCheckBoxChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->rcsUpdateFilename((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: _t->rcsStartRecording(); break;
        case 17: _t->rcsportValueChangedInt((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
