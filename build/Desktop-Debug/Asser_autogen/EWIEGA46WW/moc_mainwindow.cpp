/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN10MainWindowE = QtMocHelpers::stringData(
    "MainWindow",
    "showNotificationRequested",
    "",
    "message",
    "switchWithAnim",
    "index",
    "toggleFullscreen",
    "goMain_clicked",
    "goTests_clicked",
    "goAuthors_clicked",
    "goDonut_clicked",
    "goManuals_clicked",
    "handleNotification",
    "hideNotification",
    "showNotification",
    "handleTestRequest",
    "TestType",
    "type",
    "name",
    "variant"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN10MainWindowE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   86,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    1,   89,    2, 0x08,    3 /* Private */,
       6,    0,   92,    2, 0x08,    5 /* Private */,
       7,    0,   93,    2, 0x08,    6 /* Private */,
       8,    0,   94,    2, 0x08,    7 /* Private */,
       9,    0,   95,    2, 0x08,    8 /* Private */,
      10,    0,   96,    2, 0x08,    9 /* Private */,
      11,    0,   97,    2, 0x08,   10 /* Private */,
      12,    1,   98,    2, 0x08,   11 /* Private */,
      13,    0,  101,    2, 0x08,   13 /* Private */,
      14,    0,  102,    2, 0x08,   14 /* Private */,
      15,    3,  103,    2, 0x08,   15 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16, QMetaType::QString, QMetaType::QString,   17,   18,   19,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_ZN10MainWindowE.offsetsAndSizes,
    qt_meta_data_ZN10MainWindowE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN10MainWindowE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'showNotificationRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'switchWithAnim'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'toggleFullscreen'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'goMain_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'goTests_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'goAuthors_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'goDonut_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'goManuals_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleNotification'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'hideNotification'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showNotification'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleTestRequest'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<TestType, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->showNotificationRequested((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->switchWithAnim((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->toggleFullscreen(); break;
        case 3: _t->goMain_clicked(); break;
        case 4: _t->goTests_clicked(); break;
        case 5: _t->goAuthors_clicked(); break;
        case 6: _t->goDonut_clicked(); break;
        case 7: _t->goManuals_clicked(); break;
        case 8: _t->handleNotification((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->hideNotification(); break;
        case 10: _t->showNotification(); break;
        case 11: _t->handleTestRequest((*reinterpret_cast< std::add_pointer_t<TestType>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (MainWindow::*)(const QString & );
            if (_q_method_type _q_method = &MainWindow::showNotificationRequested; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN10MainWindowE.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::showNotificationRequested(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
