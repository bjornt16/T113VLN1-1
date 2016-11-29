QT += core
QT -= gui

CONFIG += c++11

TARGET = T113VLN1
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    programmer.cpp

HEADERS += \
    programmer.h
