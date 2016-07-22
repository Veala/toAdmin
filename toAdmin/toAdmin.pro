#-------------------------------------------------
#
# Project created by QtCreator 2016-07-05T14:16:31
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = toAdmin
TEMPLATE = app

SOURCES += main.cpp\
        admin.cpp \
        rights.cpp \
    userdialog.cpp \
    rightdialog.cpp \
    lp.cpp

HEADERS  += admin.h \
            rights.h \
    userdialog.h \
    rightdialog.h \
    lp.h

FORMS    += admin.ui \
            rights.ui \
    userdialog.ui \
    rightdialog.ui
