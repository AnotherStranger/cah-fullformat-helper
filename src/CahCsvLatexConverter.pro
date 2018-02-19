QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CahCsvLatexConverter
TEMPLATE = app

CONFIG += console c++17

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    blackcard.cpp \
    whitecard.cpp \
    mainclass.cpp \
    cardsdeck.cpp \
    fileparser.cpp \
    card.cpp \
    mainwindow.cpp \
    commandlineparser.cpp \
    dbmanager.cpp \
    filewriter.cpp \
    newcardform.cpp

HEADERS += \
    whitecard.h \
    blackcard.h \
    mainclass.h \
    cardsdeck.h \
    fileparser.h \
    card.h \
    mainwindow.h \
    commandlineparser.h \
    dbmanager.h \
    filewriter.h \
    newcardform.h

FORMS += \
    mainwindow.ui \
    newcardform.ui

RESOURCES += \
    resources.qrc
