# Universe1 QT unit test
# @author Michal Steller

QT      += core testlib

# QT      += gui
# greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += testcase
CONFIG += c++17

TEMPLATE = app

TARGET   = Universe1_tests
DESTDIR_TARGET = ../build

DESTDIR = ../build/build_Universe1_tests

OBJECTS_DIR = $$DESTDIR/obj
MOC_DIR = $$DESTDIR/moc
RCC_DIR = $$DESTDIR/rcc
UI_DIR = $$DESTDIR/ui

! include( math.pri ) {
    error( "Couldn't find the math.pri file!" )
}

INCLUDEPATH += .

SOURCES += unit_test/main.cpp

SOURCES += unit_test/test_vec3.cpp
HEADERS += unit_test/test_vec3.h

