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
        rights.cpp

HEADERS  += admin.h \
            rights.h

FORMS    += admin.ui \
            rights.ui
