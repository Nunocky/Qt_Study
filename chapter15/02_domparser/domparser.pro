greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE      = app
QT           += xml
CONFIG       += console
CONFIG       -= app_bundle
HEADERS       = domparser.h
SOURCES       = domparser.cc \
                main.cc
