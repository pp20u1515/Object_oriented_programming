# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = lab_04

QT = core gui widgets

HEADERS = \
   $$PWD/mainwindow.h \
   $$PWD/button/Button.hpp \
   $$PWD/cabin/Cabin.hpp \
   $$PWD/controller/Controller.hpp \
   $$PWD/doors/Doors.hpp \
   $$PWD/lift/Lift.hpp \
   $$PWD/defines.hpp

SOURCES = \
   $$PWD/mainwindow.cpp \
   $$PWD/button/Button.cpp \
   $$PWD/cabin/Cabin.cpp \
   $$PWD/controller/Controller.cpp \
   $$PWD/doors/Doors.cpp \
   $$PWD/lift/Lift.cpp \
   $$PWD/main.cpp

INCLUDEPATH = \
    $$PWD/gui

FORMS = \
   mainwindow.ui

#DEFINES = 

