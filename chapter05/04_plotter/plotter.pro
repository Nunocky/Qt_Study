greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE      = app
HEADERS       = plotter.h
SOURCES       = main.cc \
                plotter.cc
RESOURCES     = plotter.qrc
