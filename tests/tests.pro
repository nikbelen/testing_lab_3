include(gtest_dependency.pri)

TEMPLATE = app

QT       += core gui
QT       += network
QT       += testlib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG += qt
CONFIG += c++11



QMAKE_CXXFLAGS += -Wall -Wextra -std=c++11 #-Werror
QMAKE_CFLAGS += -Wall -Wextra -std=c++11 #-Werror

# gcov
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
QMAKE_CFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov

DEFINES += INPUTDIR=\\\"$$PWD/input/\\\"

HEADERS += parse_test.h \
        ../currency/helper.h \


SOURCES +=     main.cpp \
    ../currency/helper.cpp


INCLUDEPATH += ../currency
