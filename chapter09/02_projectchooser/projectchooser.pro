greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE      = app

HEADERS       = projectdialog.h \
                projectlistwidget.h

SOURCES       = main.cc \
                projectdialog.cpp \
                projectlistwidget.cc

FORMS         = projectdialog.ui

RESOURCES     = projectchooser.qrc
