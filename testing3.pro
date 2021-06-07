TEMPLATE = subdirs

CONFIG -= app_bundle
CONFIG += qt
CONFIG += c++11

QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage -O0

SUBDIRS = currency tests

CONFIG += ordered
