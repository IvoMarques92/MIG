TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_LFLAGS += -lasound

SOURCES += main.cpp \
    Sources/CSoundDaemon.cpp \
    Sources/CSpeakerDaemon.cpp \
    Sources/main.cpp \
    CSoundDaemon.cpp \
    CSpeakerDaemon.cpp \
    main.cpp

#To use the RPI3
target.path = /root
INSTALLS += target

HEADERS += \
    Headers/CSoundDaemon.h \
    Headers/CSpeakerDaemon.h \
    CSoundDaemon.h \
    CSpeakerDaemon.h
