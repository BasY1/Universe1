QT     += core gui widgets multimedia

CONFIG += c++17

LIBS += -lgtest

# RESOURCES = resources.qrc

HEADERS += src/Math/type.h
HEADERS += src/Math/multithread.h
HEADERS += src/Math/vec2.h
HEADERS += src/Math/vec3.h
HEADERS += src/Math/colorrgb.h

SOURCES += src/main.cpp


SOURCES += src/UnitTests/test_math.cc
