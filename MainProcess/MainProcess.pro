TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_LFLAGS += -lasound -lpthread

SOURCES += main.cpp \
    CAbsolutePattern.cpp \
    CConvertWav.cpp \
    CDistanceSensor.cpp \
    CGenerateSound.cpp \
    CHandSlideSensor.cpp \
    CLedMatrix.cpp \
    CMatrixSounds.cpp \
    CMig.cpp \
    CQuadrantRelativePattern.cpp \
    CRelativePattern.cpp \
    CSensors.cpp \
    CTouchMatrix.cpp

target.path = /root
INSTALLS += target

HEADERS += \
    CAbsolutePattern.h \
    CConvertWav.h \
    CDistanceSensor.h \
    CGenerateSound.h \
    CHandSlideSensor.h \
    CLedMatrix.h \
    CMatrixSounds.h \
    CMig.h \
    CQuadrantRelativePattern.h \
    CRelativePattern.h \
    CSensors.h \
    CTouchMatrix.h \
    main.h
