/****************************************************************************
** Meta object code from reading C++ file 'wakatime-plugin.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/wakatime-plugin.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wakatime-plugin.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN14WakatimePluginE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN14WakatimePluginE = QtMocHelpers::stringData(
    "WakatimePlugin",
    "documentJumpPerformed",
    "",
    "document",
    "documentActivated",
    "documentSaved",
    "documentOpened",
    "documentClosed"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN14WakatimePluginE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   44,    2, 0x0a,    1 /* Public */,
       4,    1,   47,    2, 0x0a,    3 /* Public */,
       5,    1,   50,    2, 0x0a,    5 /* Public */,
       6,    1,   53,    2, 0x0a,    7 /* Public */,
       7,    1,   56,    2, 0x0a,    9 /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::VoidStar,    3,
    QMetaType::Void, QMetaType::VoidStar,    3,
    QMetaType::Void, QMetaType::VoidStar,    3,
    QMetaType::Void, QMetaType::VoidStar,    3,
    QMetaType::Void, QMetaType::VoidStar,    3,

       0        // eod
};

Q_CONSTINIT const QMetaObject WakatimePlugin::staticMetaObject = { {
    QMetaObject::SuperData::link<KDevelop::IPlugin::staticMetaObject>(),
    qt_meta_stringdata_ZN14WakatimePluginE.offsetsAndSizes,
    qt_meta_data_ZN14WakatimePluginE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN14WakatimePluginE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<WakatimePlugin, std::true_type>,
        // method 'documentJumpPerformed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<void *, std::false_type>,
        // method 'documentActivated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<void *, std::false_type>,
        // method 'documentSaved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<void *, std::false_type>,
        // method 'documentOpened'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<void *, std::false_type>,
        // method 'documentClosed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<void *, std::false_type>
    >,
    nullptr
} };

void WakatimePlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<WakatimePlugin *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->documentJumpPerformed((*reinterpret_cast< std::add_pointer_t<void*>>(_a[1]))); break;
        case 1: _t->documentActivated((*reinterpret_cast< std::add_pointer_t<void*>>(_a[1]))); break;
        case 2: _t->documentSaved((*reinterpret_cast< std::add_pointer_t<void*>>(_a[1]))); break;
        case 3: _t->documentOpened((*reinterpret_cast< std::add_pointer_t<void*>>(_a[1]))); break;
        case 4: _t->documentClosed((*reinterpret_cast< std::add_pointer_t<void*>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *WakatimePlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WakatimePlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN14WakatimePluginE.stringdata0))
        return static_cast<void*>(this);
    return KDevelop::IPlugin::qt_metacast(_clname);
}

int WakatimePlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = KDevelop::IPlugin::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN18WakatimePluginViewE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN18WakatimePluginViewE = QtMocHelpers::stringData(
    "WakatimePluginView"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN18WakatimePluginViewE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject WakatimePluginView::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN18WakatimePluginViewE.offsetsAndSizes,
    qt_meta_data_ZN18WakatimePluginViewE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN18WakatimePluginViewE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<WakatimePluginView, std::true_type>
    >,
    nullptr
} };

void WakatimePluginView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<WakatimePluginView *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *WakatimePluginView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WakatimePluginView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN18WakatimePluginViewE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WakatimePluginView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
