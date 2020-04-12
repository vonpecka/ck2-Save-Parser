QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_parser.cpp

HEADERS += \
    abstracts.h \
    ortner.h

DISTFILES += \
    traits.csv


# custom added code to copy some files to the directory for building
copydata.commands = $(COPY_DIR) $$PWD/*.ck2 $$PWD/*.csv $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
