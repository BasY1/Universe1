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
HEADERS += src/Math/cylinderarc.h

HEADERS += src/Math/spherecrosssection.h

######################################################3

HEADERS += src/Data3D/data3d.h
SOURCES += src/Data3D/data3d.cpp


HEADERS += src/Data3D/data3dpointsbase.h
SOURCES += src/Data3D/data3dpointsbase.cpp

HEADERS += src/Data3D/data3dpointssize.h
SOURCES += src/Data3D/data3dpointssize.cpp

HEADERS += src/Data3D/data3dpointsalpha.h
SOURCES += src/Data3D/data3dpointsalpha.cpp

HEADERS += src/Data3D/data3dpointscolor.h
SOURCES += src/Data3D/data3dpointscolor.cpp

HEADERS += src/Data3D/data3dpointscoloralpha.h
SOURCES += src/Data3D/data3dpointscoloralpha.cpp

HEADERS += src/Data3D/data3dpointssizealpha.h
SOURCES += src/Data3D/data3dpointssizealpha.cpp

HEADERS += src/Data3D/data3dpointssizecolor.h
SOURCES += src/Data3D/data3dpointssizecolor.cpp

HEADERS += src/Data3D/data3dpointssizecoloralpha.h
SOURCES += src/Data3D/data3dpointssizecoloralpha.cpp


HEADERS += src/Data3D/data3dmaterialbase.h
SOURCES += src/Data3D/data3dmaterialbase.cpp

HEADERS += src/Data3D/data3dmaterialalpha.h
SOURCES += src/Data3D/data3dmaterialalpha.cpp

HEADERS += src/Data3D/data3dmaterialnormal.h
SOURCES += src/Data3D/data3dmaterialnormal.cpp

HEADERS += src/Data3D/data3dmaterialnormalalpha.h
SOURCES += src/Data3D/data3dmaterialnormalalpha.cpp

######################################################3

SOURCES += src/main.cpp


SOURCES += src/UnitTests/test_math.cc
