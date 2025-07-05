QT += testlib gui widgets
CONFIG += qt console warn_on depend_includepath testcase

INCLUDEPATH += ../untitled
SOURCES += tst_test.cpp \
           ../untitled/mainwindow.cpp \
           ../untitled/math.cpp

HEADERS += ../untitled/mainwindow.h \
           ../untitled/math.h

FORMS += ../untitled/mainwindow.ui
