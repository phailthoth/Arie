QT += core
QT += network
QT -= gui

CONFIG += c++11

TARGET = ArieServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    server.cpp \
    user.cpp

HEADERS += \
    server.h \
    user.h

DISTFILES += \
    config.cfg
