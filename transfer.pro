#-------------------------------------------------
#
# Project created by QtCreator 2015-01-27T23:22:22
#
#-------------------------------------------------

QT += core gui network widgets sql quick

CONFIG += c++11

TARGET = transfer
TEMPLATE = app

OBJECTS_DIR = .obj
MOC_DIR = .moc

HEADERS  += \
    src/core.h \
    src/dbhandler.h \
    src/discoverer.h \
    src/dialogs/settingsdialog.h \
    src/parser.h \
    src/settings.h \
    src/systray.h \
    src/user.h \
    src/userlist.h

SOURCES += \
    src/core.cpp \
    src/dbhandler.cpp \
    src/discoverer.cpp \
    src/dialogs/settingsdialog.cpp \
    src/main.cpp \
    src/parser.cpp \
    src/settings.cpp \
    src/systray.cpp \
    src/user.cpp \
    src/userlist.cpp

FORMS += \
    src/dialogs/settingsdialog.ui

RESOURCES += \
    images.qrc \
    qml.qrc

OTHER_FILES += \
    qml/sendfile/main.qml \
    qml/sendfile/Avatar.qml \
    qml/sendfile/SelectionStatus.qml \
    qml/sendfile/UserDelegate.qml
