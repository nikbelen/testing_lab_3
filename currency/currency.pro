

CONFIG += c++11

LIBS += -lgcov

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QT       += core gui
QT       += network
QT       += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


QMAKE_CXXFLAGS += -Wall -Wextra -std=c++11 #-Werror
QMAKE_CFLAGS += -Wall -Wextra -std=c++11 #-Werror

SOURCES += \
    helper.cpp \
    main.cpp

HEADERS += \
    helper.h



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
