QT += widgets

TEMPLATE      = app
CONFIG       += console thread
CONFIG       -= app_bundle
HEADERS       = thread.h \
                threaddialog.h
SOURCES       = main.cc \
                thread.cc \
                threaddialog.cc
