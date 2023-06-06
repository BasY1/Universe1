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

HEADERS += src/video/dynamicproperty/dynamicstring.h
SOURCES += src/video/dynamicproperty/dynamicstring.cpp

HEADERS += src/video/dynamicproperty/group/dynamicmaterialgroup.h
SOURCES += src/video/dynamicproperty/group/dynamicmaterialgroup.cpp

HEADERS += src/video/dynamicproperty/group/dynamictextgroup.h

HEADERS += src/video/dynamicproperty/group/dynamicanglegroup.h
SOURCES += src/video/dynamicproperty/group/dynamicanglegroup.cpp

HEADERS += src/video/dynamicproperty/group/dynamicspingroup.h
SOURCES += src/video/dynamicproperty/group/dynamicspingroup.cpp

HEADERS += src/video/camera.h
SOURCES += src/video/camera.cpp

HEADERS += src/video/data3d.h

HEADERS += src/video/shader.h
SOURCES += src/video/shader.cpp

HEADERS += src/video/items/item.h
SOURCES += src/video/items/item.cpp

HEADERS += src/video/items/items2d/subs.h
SOURCES += src/video/items/items2d/subs.cpp

HEADERS += src/video/items/items2d/item2d.h
SOURCES += src/video/items/items2d/item2d.cpp

HEADERS += src/video/items/items2d/item2dimage.h
SOURCES += src/video/items/items2d/item2dimage.cpp

HEADERS += src/video/items/items3d/item3d.h
SOURCES += src/video/items/items3d/item3d.cpp

HEADERS += src/video/items/items3d/text3d/item3dtext.h
SOURCES += src/video/items/items3d/text3d/item3dtext.cpp

HEADERS += src/video/items/items3d/plane/item3dplane.h
SOURCES += src/video/items/items3d/plane/item3dplane.cpp

HEADERS += src/video/items/items3d/plane/item3dplanecircle.h
SOURCES += src/video/items/items3d/plane/item3dplanecircle.cpp

HEADERS += src/video/items/items3d/plane/item3dplanecircleslice.h
SOURCES += src/video/items/items3d/plane/item3dplanecircleslice.cpp

HEADERS += src/video/items/items3d/cone/item3dcone.h
SOURCES += src/video/items/items3d/cone/item3dcone.cpp

HEADERS += src/video/items/items3d/cone/item3dconeslice.h
SOURCES += src/video/items/items3d/cone/item3dconeslice.cpp

HEADERS += src/video/items/items3d/cylinder/item3dcylinder.h
SOURCES += src/video/items/items3d/cylinder/item3dcylinder.cpp

HEADERS += src/video/items/items3d/cylinder/item3dcylinderslice.h
SOURCES += src/video/items/items3d/cylinder/item3dcylinderslice.cpp

HEADERS += src/video/items/items3d/torus/item3dtorus.h
SOURCES += src/video/items/items3d/torus/item3dtorus.cpp

HEADERS += src/video/items/items3d/torus/item3dtoruscup.h
SOURCES += src/video/items/items3d/torus/item3dtoruscup.cpp

HEADERS += src/video/items/items3d/torus/item3dtorusslice.h
SOURCES += src/video/items/items3d/torus/item3dtorusslice.cpp

HEADERS += src/video/items/items3d/torus/item3dtorusarc.h
SOURCES += src/video/items/items3d/torus/item3dtorusarc.cpp

HEADERS += src/video/items/items3d/torus/item3dtorusarccup.h
SOURCES += src/video/items/items3d/torus/item3dtorusarccup.cpp

HEADERS += src/video/items/items3d/torus/item3dtorusarcslice.h
SOURCES += src/video/items/items3d/torus/item3dtorusarcslice.cpp

HEADERS += src/video/items/items3d/sphere/item3dsphere.h
SOURCES += src/video/items/items3d/sphere/item3dsphere.cpp

HEADERS += src/video/items/items3d/sphere/item3dspherecup.h
SOURCES += src/video/items/items3d/sphere/item3dspherecup.cpp

HEADERS += src/video/items/items3d/sphere/item3dsphereslice.h
SOURCES += src/video/items/items3d/sphere/item3dsphereslice.cpp

HEADERS += src/video/items/items3d/line/item3dline.h
SOURCES += src/video/items/items3d/line/item3dline.cpp

HEADERS += src/video/items/items3d/line/item3dlinedots.h
SOURCES += src/video/items/items3d/line/item3dlinedots.cpp

HEADERS += src/video/items/items3d/line/item3dlinedash.h
SOURCES += src/video/items/items3d/line/item3dlinedash.cpp

HEADERS += src/video/items/items3d/line/item3dlinetwist.h
SOURCES += src/video/items/items3d/line/item3dlinetwist.cpp

HEADERS += src/video/items/items3d/line/item3dlinecross.h
SOURCES += src/video/items/items3d/line/item3dlinecross.cpp

HEADERS += src/video/items/items3d/arc/item3dlinecircle.h
SOURCES += src/video/items/items3d/arc/item3dlinecircle.cpp

HEADERS += src/video/items/items3d/arc/item3dlinearc.h
SOURCES += src/video/items/items3d/arc/item3dlinearc.cpp

HEADERS += src/video/items/items3d/arc/item3dlinearcdots.h
SOURCES += src/video/items/items3d/arc/item3dlinearcdots.cpp

HEADERS += src/video/items/items3d/arc/item3dlinearcdash.h
SOURCES += src/video/items/items3d/arc/item3dlinearcdash.cpp

HEADERS += src/video/items/items3d/wiresphere/item3dwiresphere.h
SOURCES += src/video/items/items3d/wiresphere/item3dwiresphere.cpp

HEADERS += src/video/items/items3d/wiresphere/item3dwirespherecup.h
SOURCES += src/video/items/items3d/wiresphere/item3dwirespherecup.cpp

HEADERS += src/video/items/items3d/wiresphere/item3dwiresphereslice.h
SOURCES += src/video/items/items3d/wiresphere/item3dwiresphereslice.cpp

HEADERS += src/video/items/items3d/arrow/item3dlinearrow.h
SOURCES += src/video/items/items3d/arrow/item3dlinearrow.cpp

HEADERS += src/video/items/items3d/arrow/item3darcarrow.h
SOURCES += src/video/items/items3d/arrow/item3darcarrow.cpp

HEADERS += src/video/items/items3d/arrow/item3dangledim.h
SOURCES += src/video/items/items3d/arrow/item3dangledim.cpp

HEADERS += src/video/items/items3d/space/item3dspace.h
SOURCES += src/video/items/items3d/space/item3dspace.cpp

HEADERS += src/video/items/items3d/path/item3dpath.h
SOURCES += src/video/items/items3d/path/item3dpath.cpp

HEADERS += src/video/items/items3d/hand/item3dhand.h
SOURCES += src/video/items/items3d/hand/item3dhand.cpp

HEADERS += src/video/items/items3d/spin/item3dspin.h
SOURCES += src/video/items/items3d/spin/item3dspin.cpp

HEADERS += src/video/items/items3d/spin/item3dconstellation.h
SOURCES += src/video/items/items3d/spin/item3dconstellation.cpp

HEADERS += src/video/footage.h
SOURCES += src/video/footage.cpp

HEADERS += src/gui/mainwindow.h
SOURCES += src/gui/mainwindow.cpp

SOURCES += src/main.cpp
