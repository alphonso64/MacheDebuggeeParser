#-------------------------------------------------
#
# Project created by QtCreator 2017-12-20T19:32:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MacheDebuggeeParser
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    machinedebugparam.cpp

HEADERS  += mainwindow.h \
    machinedebugparam.h

FORMS    += mainwindow.ui


LIBS += -lGL -lpthread -lpthread -lpython2.7 -L./ -ljson

INCLUDEPATH += /usr/include/python2.7 /usr/include/c++/4.8.4/ /usr/local/include/
