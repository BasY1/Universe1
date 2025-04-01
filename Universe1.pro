QT     += core gui widgets multimedia opengl openglwidgets

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
SOURCES += src/Math/circle.cpp

HEADERS += src/Math/ellipse.h
HEADERS += src/Math/irregellipse.h

HEADERS += src/Math/planeindices.h
SOURCES += src/Math/planeindices.cpp

HEADERS += src/Math/sphere.h
SOURCES += src/Math/sphere.cpp

HEADERS += src/Math/ellipsoid.h
HEADERS += src/Math/irregellipsoid.h

HEADERS += src/Math/cylinder.h

HEADERS += src/Math/spherecrosssection.h

SOURCES += src/main.cpp


SOURCES += src/UnitTests/test_math.cc
