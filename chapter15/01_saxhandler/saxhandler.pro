greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE      = app
QT           += xml
CONFIG       -= app_bundle
CONFIG       += console
HEADERS       = saxhandler.h
SOURCES       = main.cc \
                saxhandler.cc
