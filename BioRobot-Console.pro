QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets quickwidgets webenginewidgets gamepad

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gamepad/readinput.cpp \
    main.cpp \
    mainwindow.cpp \
    video/fullscreennotification.cpp \
    video/fullscreenwindow.cpp

HEADERS += \
    gamepad/readinput.h \
    mainwindow.h \
    video/fullscreennotification.h \
    video/fullscreenwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    gamepad/ButtonImage.qml \
    gamepad/DPad.qml \
    gamepad/JoystickViewer.qml \
    gamepad/LeftThumbstick.qml \
    gamepad/RightThumbstick.qml \
    gamepad/main.qml \
    trajectory/3d_points_view.qml

RESOURCES += \
    resources.qrc
