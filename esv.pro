#-------------------------------------------------
#
# Project created by QtCreator 2015-05-21T19:41:36
#
#-------------------------------------------------

QT       += core
QT       += gui opengl
#QT       += qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = esv
TEMPLATE = app

CONFIG += c++14

SOURCES += main.cpp\
    boardmodel.cpp \
    mainscene.cpp \
    mvcontroller.cpp \
    tile.cpp \
    filemanager.cpp \
    boardmodelcollectioncontroller.cpp \
    clientcontroller.cpp \
    esvgraphicsview.cpp \
    newboardoptionsdialog.cpp \
    dialogmanager.cpp \
    zoomer.cpp \
    mainwindow.cpp

HEADERS  += \
    boardmodel.h \
    mainscene.h \
    mvcontroller.h \
    tile.h \
    filemanager.h \
    boardmodelcollectioncontroller.h \
    clientcontroller.h \
    boarddata.h \
    esvgraphicsview.h \
    newboardoptionsdialog.h \
    newboardoptions.h \
    dialogmanager.h \
    zoomer.h \
    mainwindow.h

DISTFILES +=
