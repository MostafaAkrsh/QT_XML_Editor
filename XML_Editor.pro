QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    compression.cpp \
    dialog.cpp \
    global_objects.cpp \
    main.cpp \
    mainwindow.cpp \
    tree.cpp

HEADERS += \
    compression.h \
    dialog.h \
    global_objects.h \
    mainwindow.h \
    tree.h

FORMS += \
    dialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    q.qrc

DISTFILES += \
    myapp.rc

