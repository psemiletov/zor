VERSION = 0.0.3
QT += core
QT += gui

TEMPLATE = app

CONFIG += warn_on \
    thread \
    qt \
    release

SOURCES += main.cpp\
           cmainwindow.cpp

HEADERS  += cmainwindow.h

isEmpty(PREFIX):PREFIX = /usr/local
BINDIR = $$PREFIX/bin
DATADIR = $$PREFIX

TARGET = zor
target.path = $$BINDIR

INSTALLS += target

DISTFILES += ChangeLog \
    COPYING \
    README \
    NEWS \
    AUTHORS \