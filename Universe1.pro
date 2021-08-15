# Universe1
# 

QT      += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#QT      += multimedia
#QT      += texttospeech

QT      += testlib
CONFIG += testcase

#CONFIG += c++11
CONFIG += c++17

TARGET   = Universe1
TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#LIBS += -lcuda -lnvrtc

SOURCES += \
    src/main.cpp

########################################################################################################################

HEADERS += \
    src/math/typeconst.h \
    src/math/type.h \
    src/math/texttools.h \
    src/math/vec3.h \
    \
    src/simulation/constants.h \
    src/simulation/timestamp.h \
    src/simulation/objecthistory.h \
    src/simulation/simulationproperty.h \
    src/simulation/simulation.h \
    \
    src/simulation/newton/newtontimestamp.h \
    src/simulation/newton/newtonobject.h \
    src/simulation/newton/newtonobjectcurrent.h \
    src/simulation/newton/newtonobjectbywave.h \
    src/simulation/newton/newtonsimulation.h \

########################################################################################################################

SOURCES += \
    src/qt/qsimulation.cpp \
    src/qt/qsimulationnewtoncurrent.cpp \
    \
    src/qt/opengl/camera.cpp \
    src/qt/opengl/shaderprogram.cpp \

HEADERS += \
    src/qt/qsimulation.h \
    src/qt/qsimulationnewtoncurrent.h \
    \
    src/qt/opengl/camera.h \
    src/qt/opengl/shaderprogram.h \


########################################################################################################################

SOURCES += \
    src/unit_tests/test_vec3.cpp \
    src/unit_tests/test_newton.cpp

HEADERS += \
    src/unit_tests/test_vec3.h \
    src/unit_tests/test_newton.h

########################################################################################################################

#TRANSLATIONS += \
#    Test_en_US.ts
#
OTHER_FILES += \
    doc/Doxyfile \
    README.md

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
