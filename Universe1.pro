QT     += core gui widgets multimedia

CONFIG += c++17

DEFINES += UNIVERSE1_USE_QT_LIB

# RESOURCES = resources.qrc

HEADERS += \
    src/math/typeconst.h \
    src/math/type.h \
    src/math/vec2.h \
    src/math/vec3.h \
    src/math/quaternion.h \
    src/math/orientation.h \
    src/math/constellation.h \
    src/math/circle.h \
    src/math/sphere.h \
    src/math/spherecrosssection.h

HEADERS += src/video/material.h

HEADERS += src/video/config.h
SOURCES += src/video/config.cpp

HEADERS += src/video/dynamicproperty/dynamicproperty.h
HEADERS += src/video/dynamicproperty/dynamicvalue.h
HEADERS += src/video/dynamicproperty/dynamicenum.h

HEADERS += src/video/dynamicproperty/dynamicalign.h
SOURCES += src/video/dynamicproperty/dynamicalign.cpp

HEADERS += src/video/dynamicproperty/dynamicbool.h
SOURCES += src/video/dynamicproperty/dynamicbool.cpp

HEADERS += src/video/dynamicproperty/dynamicvec3.h
SOURCES += src/video/dynamicproperty/dynamicvec3.cpp

HEADERS += src/video/dynamicproperty/dynamiccolor.h
SOURCES += src/video/dynamicproperty/dynamiccolor.cpp

HEADERS += src/video/dynamicproperty/dynamicmaterialgroup.h
SOURCES += src/video/dynamicproperty/dynamicmaterialgroup.cpp

HEADERS += src/video/dynamicproperty/dynamicstring.h
SOURCES += src/video/dynamicproperty/dynamicstring.cpp

HEADERS += src/video/dynamicproperty/dynamictextgroup.h

HEADERS += src/video/camera.h
SOURCES += src/video/camera.cpp

HEADERS += src/video/data3d.h

HEADERS += src/video/shader.h
SOURCES += src/video/shader.cpp


SOURCES += src/main.cpp
