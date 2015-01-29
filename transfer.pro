#-------------------------------------------------
#
# Project created by QtCreator 2015-01-27T23:22:22
#
#-------------------------------------------------

QT += core gui network

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = transfer
TEMPLATE = app


OBJECTS_DIR = .obj
MOC_DIR = .moc

HEADERS  += \
    src/core.h \
    src/dialogs/settingsdialog.h \
    src/settings.h \
    src/systray.h

SOURCES += \
    src/core.cpp \
    src/dialogs/settingsdialog.cpp \
    src/main.cpp \
    src/settings.cpp \
    src/systray.cpp

FORMS += \
    src/dialogs/settingsdialog.ui

RESOURCES += \
    images.qrc
