QT     += core gui widgets multimedia

CONFIG += c++17

LIBS += -lgtest

# RESOURCES = resources.qrc

HEADERS += src/Math/type.h
HEADERS += src/Math/multithread.h
HEADERS += src/Math/vec2.h
HEADERS += src/Math/vec3.h
HEADERS += src/Math/colorrgb.h
HEADERS += src/Math/material.h
HEADERS += src/Math/camera.h
HEADERS += src/Math/orientation.h
HEADERS += src/Math/circle.h
HEADERS += src/Math/sphere.h
HEADERS += src/Math/spherecrosssection.h

SOURCES += src/main.cpp


SOURCES += src/UnitTests/test_math.cc
