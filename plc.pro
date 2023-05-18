QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets charts sql

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basechange.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    myworker.cpp \
    rpmmeasurewidget.cpp \
    snap7.cpp \
    sqlite.cpp

HEADERS += \
    basechange.h \
    login.h \
    mainwindow.h \
    myworker.h \
    rpmmeasurewidget.h \
    snap7.h \
    sqlite.h

FORMS += \
    basechange.ui \
    login.ui \
    mainwindow.ui \
    rpmmeasurewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix|win32: LIBS += -L$$PWD/./ -lsnap7

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

RESOURCES += \
    img.qrc

DISTFILES +=
