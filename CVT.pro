QT -= gui

TARGET = CVT

CONFIG += debug_and_release
CONFIG += c++11

OBJECTS_DIR = $$PWD/build/buildObj/

CONFIG(release, debug|release) {
    DESTDIR = $$PWD/build/release/
}
CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/build/debug/
}

INCLUDEPATH += $$PWD/

HEADERS +=

SOURCES += \
    src/main.cpp
