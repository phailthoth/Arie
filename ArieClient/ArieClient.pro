#-------------------------------------------------
#
# Project created by QtCreator 2016-03-09T21:04:14
#
#-------------------------------------------------

QT       += core gui
QT	 += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ArieClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    studentclient.cpp \
    teacherclient.cpp \
    studentobject.cpp

HEADERS  += mainwindow.h \
    studentclient.h \
    teacherclient.h \
    studentobject.h

FORMS    += mainwindow.ui \
    studentclient.ui \
    teacherclient.ui \
    studentobject.ui

DISTFILES += \
    config.cfg
