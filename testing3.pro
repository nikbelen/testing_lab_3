TEMPLATE = subdirs

CONFIG -= app_bundle
CONFIG += c++11
CONFIG += qt


QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage -O0 -std=c++11

SUBDIRS = currency tests

CONFIG += ordered
