TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += \
        main.cpp

QMAKE_CXXFLAGS +=-fno-elide-constructors
