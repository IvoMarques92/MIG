TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_LFLAGS += -lasound

SOURCES += main.cpp \
    CSpeakerDaemon.cpp

#To use the RPI3
target.path = /root
INSTALLS += target

HEADERS += \
           CSpeakerDaemon.h
