#-------------------------------------------------
#
# Project created by QtCreator 2015-02-04T17:41:37
#
#-------------------------------------------------

CONFIG +=	c++11

QT +=	core gui \
		network

greaterThan(QT_MAJOR_VERSION, 4): QT +=	widgets

TARGET = herodotus
TEMPLATE = app


SOURCES +=	main.cpp \
			dispwindow.cpp \
			herodotus.cpp \
    detailswindow.cpp

HEADERS +=	dispwindow.h \
			herodotus.h \
    detailswindow.h

FORMS +=	dispwindow.ui \
    detailswindow.ui

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.6
