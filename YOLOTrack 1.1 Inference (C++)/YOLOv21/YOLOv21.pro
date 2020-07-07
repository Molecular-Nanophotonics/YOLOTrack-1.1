#-------------------------------------------------
#
# Project created by QtCreator 2020-02-08T20:36:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = YOLOv2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h \
        mygraphicsview.h

FORMS += \
        mainwindow.ui

#LIBS += $$PWD/MyDLL/x64/Release/MyDLL.dll

win32:CONFIG(release, debug|release): LIBS += "-L../../TF DLL/x64/release/" -lTF \
                                              "-L../../YOLOv21 DLL/x64/release/" -lYOLOv21

INCLUDEPATH += ../../TF DLL/TF.h \
               ../../YOLOv21 DLL/YOLOv21.h

DEPENDPATH += ../../TF DLL/TF.h \
              ../../YOLOv21 DLL/YOLOv21.h
