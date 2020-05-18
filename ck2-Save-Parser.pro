QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_parser.cpp \
    texttools.cpp \
    datafile.cpp \
    parser.cpp \
    entity.cpp \
    dynasties.cpp \
    titles.cpp \
    characters.cpp \
    parseddata.cpp \
    metadata.cpp \
    province.cpp \
    landedtitleparser.cpp

HEADERS += \
    abstracts.h \
    texttools.h \
    datafile.h \
    parser.h \
    entity.h \
    dynasties.h \
    titles.h \
    characters.h \
    parseddata.h \
    metadata.h \
    province.h \
    landedtitleparser.h

DISTFILES += \
    traits.csv


# custom added code to copy some files to the directory for building
copydata.commands = $(COPY_DIR) $$PWD/*.ck2 $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
