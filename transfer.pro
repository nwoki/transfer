#-------------------------------------------------
#
# Project created by QtCreator 2015-01-27T23:22:22
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = transfer
TEMPLATE = app


OBJECTS_DIR = .obj
MOC_DIR = .moc

HEADERS  += \
    src/mainwindow.h \
    src/systray.h

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/systray.cpp

FORMS += \
    forms/mainwindow.ui

RESOURCES += \
    images.qrc
