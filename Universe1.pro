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

HEADERS += \
    src/qt/qsimulation.h \
    src/qt/qsimulationnewtoncurrent.h \

########################################################################################################################

SOURCES += \
    src/qt/opengl/camera.cpp \
    src/qt/opengl/adscolors.cpp \
    src/qt/opengl/material.cpp \
    src/qt/opengl/lights.cpp \
    src/qt/opengl/shaderprogram.cpp \
    src/qt/opengl/glwidget.cpp \

HEADERS += \
    src/qt/opengl/camera.h \
    src/qt/opengl/adscolors.h \
    src/qt/opengl/material.h \
    src/qt/opengl/lights.h \
    src/qt/opengl/shaderprogram.h \
    src/qt/opengl/glwidget.h \

########################################################################################################################

SOURCES += \
    src/qt/opengl/models/glmodel.cpp \
    \
    src/qt/opengl/models/modeldots.cpp \
    src/qt/opengl/models/modelpath.cpp \
    \
    src/qt/opengl/models/linesmodel.cpp \
    src/qt/opengl/models/modelpointlight.cpp \
    src/qt/opengl/models/modelspotlight.cpp \
    \
    src/qt/opengl/models/meshmodel.cpp \
    src/qt/opengl/models/modeltriangle.cpp \
    src/qt/opengl/models/modelplane.cpp \
    src/qt/opengl/models/modelbox.cpp \
    src/qt/opengl/models/modelsphere.cpp \
    src/qt/opengl/models/modelarrow.cpp \

HEADERS += \
    src/qt/opengl/models/glmodel.h \
    \
    src/qt/opengl/models/modeldots.h \
    src/qt/opengl/models/modelpath.h \
    \
    src/qt/opengl/models/linesmodel.h \
    src/qt/opengl/models/modelpointlight.h \
    src/qt/opengl/models/modelspotlight.h \
    \
    src/qt/opengl/models/meshmodel.h \
    src/qt/opengl/models/modeltriangle.h \
    src/qt/opengl/models/modelplane.h \
    src/qt/opengl/models/modelbox.h \
    src/qt/opengl/models/modelsphere.h \
    src/qt/opengl/models/modelarrow.h \

########################################################################################################################

SOURCES += \
    src/qt/widgets/horizontallinespacer.cpp \
    src/qt/widgets/widgetbgcolor.cpp \
    src/qt/widgets/widgetglsettings.cpp \

HEADERS += \
    src/qt/widgets/horizontallinespacer.h \
    src/qt/widgets/widgetbgcolor.h \
    src/qt/widgets/widgetglsettings.h \

########################################################################################################################

SOURCES += \
    src/qt/widgets/gui/guiint.cpp \
    src/qt/widgets/gui/guifloat.cpp \
    src/qt/widgets/gui/guivector3d.cpp \
    src/qt/widgets/gui/guicolor.cpp \
    src/qt/widgets/gui/guicolorads.cpp \
    src/qt/widgets/gui/guimaterial.cpp \
    src/qt/widgets/gui/guidirectionlight.cpp \
    src/qt/widgets/gui/guipointlight.cpp \
    src/qt/widgets/gui/guispotlight.cpp \

HEADERS += \
    src/qt/widgets/gui/guiint.h \
    src/qt/widgets/gui/guifloat.h \
    src/qt/widgets/gui/guivector3d.h \
    src/qt/widgets/gui/guicolor.h \
    src/qt/widgets/gui/guicolorads.h \
    src/qt/widgets/gui/guimaterial.h \
    src/qt/widgets/gui/guidirectionlight.h \
    src/qt/widgets/gui/guipointlight.h \
    src/qt/widgets/gui/guispotlight.h \

########################################################################################################################

SOURCES += \
    src/qt/widgets/materialeditor/widgetview.cpp \
    src/qt/widgets/materialeditor/widgetmodels.cpp \
    src/qt/widgets/materialeditor/widgetmaterialeditor.cpp \
    src/qt/widgets/materialeditor/dialogmaterialeditor.cpp \

HEADERS += \
    src/qt/widgets/materialeditor/widgetview.h \
    src/qt/widgets/materialeditor/widgetmodels.h \
    src/qt/widgets/materialeditor/widgetmaterialeditor.h \
    src/qt/widgets/materialeditor/dialogmaterialeditor.h \


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
