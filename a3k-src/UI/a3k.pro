#-------------------------------------------------
#
# Project created by QtCreator 2016-02-05T01:11:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = a3k
TEMPLATE = app


SOURCES += main.cpp\
        a3k.cpp \
        ../a3ksetup.c \
        ../execute.c \
    instructionops.cpp

HEADERS  += a3k.h \
    instructionops.h

FORMS    += a3k.ui

CONFIG  += c++11
