QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_admin.cpp \
    addgoods.cpp \
    addmarket.cpp \
    ctrl_admin.cpp \
    file_reg.cpp \
    log_in.cpp \
    main.cpp \
    mainsystem.cpp \
    mainwindow.cpp \
    sell.cpp \
    sold.cpp

HEADERS += \
    add_admin.h \
    addgoods.h \
    addmarket.h \
    ctrl_admin.h \
    file_reg.h \
    log_in.h \
    mainsystem.h \
    mainwindow.h \
    sell.h \
    sold.h

FORMS += \
    add_admin.ui \
    addgoods.ui \
    addmarket.ui \
    ctrl_admin.ui \
    file_reg.ui \
    log_in.ui \
    mainsystem.ui \
    mainwindow.ui \
    sell.ui \
    sold.ui

TRANSLATIONS += \
    QtHomeWork_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
