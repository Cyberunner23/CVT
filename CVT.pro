QT -= gui

TARGET = CVT

CONFIG += debug_and_release
CONFIG += c++11

OBJECTS_DIR = $$PWD/build/buildObj/

CONFIG(release, debug|release) {
    staticBuild: DESTDIR = $$PWD/build/release/static/
    dynamicBuild: DESTDIR = $$PWD/build/release/dynamic/
}
CONFIG(debug, debug|release) {
    staticBuild: DESTDIR = $$PWD/build/debug/static/
    dynamicBuild: DESTDIR = $$PWD/build/debug/dynamic/
}

INCLUDEPATH += $$PWD/

HEADERS +=

SOURCES += \
    src/main.cpp
