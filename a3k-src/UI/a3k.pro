#-------------------------------------------------
#
# Project created by QtCreator 2016-04-15T12:10:26
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
    a3kconsole.cpp \
    a3kaddrdialog.cpp \
    a3kspeedselect.cpp

HEADERS  += a3k.h \
    a3kconsole.h \
    a3kaddrdialog.h \
    a3kspeedselect.h

FORMS    += a3k.ui \
    a3kconsole.ui \
    a3kaddrdialog.ui \
    a3kspeedselect.ui

CONFIG  += c++11
