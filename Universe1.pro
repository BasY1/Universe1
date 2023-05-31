QT     += core gui widgets multimedia

CONFIG += c++17

DEFINES += UNIVERSE1_USE_QT_LIB

# RESOURCES = resources.qrc

HEADERS +=    \
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

# HEADERS +=
# SOURCES +=

# HEADERS +=
# SOURCES +=


SOURCES += src/main.cpp
