QT += core gui
QT += serialport  # прям из документации скопировал
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

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
    MClib/src/common/types.cpp\
    MClib/src/protocols/wake.cpp\
    analyzer.cpp \
    bit_manipulation.cpp \
    configuration.cpp \
    connectors.cpp \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp \
    transmitter.cpp

HEADERS += \
    MClib/include/common/types.h\
    MClib/include/common/buffer.h\
    MClib/include/common/wake_common.h\
    MClib/include/protocols/wake.h\
    analayzer.h \
    bit_manipulation.h \
    configuration.h \
    connectors.h \
    mainwindow.h \
    settingsdialog.h \
    transmitter.h

FORMS += \
    analayzer.ui \
    mainwindow.ui\
    settingsdialog.ui\
    configuration.ui\
    connectors.ui

RESOURCES += \
    images \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
