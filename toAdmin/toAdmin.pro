#-------------------------------------------------
#
# Project created by QtCreator 2016-07-05T14:16:31
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = toAdmin
TEMPLATE = app

SOURCES +=  $$PWD/admin.cpp \
            $$PWD/rights.cpp \
    $$PWD/userdialog.cpp \
    $$PWD/rightdialog.cpp \
    $$PWD/lp.cpp \
    $$PWD/lpdialog.cpp

HEADERS  += $$PWD/admin.h \
            $$PWD/rights.h \
    $$PWD/userdialog.h \
    $$PWD/rightdialog.h \
    $$PWD/lp.h \
    $$PWD/lpdialog.h

FORMS    += $$PWD/admin.ui \
            $$PWD/rights.ui \
    $$PWD/userdialog.ui \
    $$PWD/rightdialog.ui \
    $$PWD/lpdialog.ui

RESOURCES += \
    $$PWD/resource.qrc
