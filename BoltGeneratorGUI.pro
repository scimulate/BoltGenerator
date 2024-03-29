QT += core gui quick quickwidgets

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
    bolt.cpp \
    chamfer.cpp \
    convert.cpp \
    cut.cpp \
    dimensions.cpp \
    export.cpp \
    helix.cpp \
    hexagon.cpp \
    main.cpp \
    mainwindow.cpp \
    thread.cpp

HEADERS += \
    bolt.h \
    chamfer.h \
    convert.h \
    cut.h \
    dimensions.h \
    export.h \
    helix.h \
    hexagon.h \
    mainwindow.h \
    thread.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix: INCLUDEPATH += /usr/include/opencascade
unix: LIBS += \
    -lTKernel \
    -lTKBRep \
    -lTKBO \
    #-lTKFillet \
    -lTKG2d \
    -lTKG3d \
    -lTKGeomBase \
    -lTKMath \
    -lTKOffset \
    -lTKPrim \
    -lTKSTEP \
    -lTKTopAlgo \
    -lTKXSBase

win32: INCLUDEPATH += C:\OpenCASCADE-7.7.0-vc14-64\opencascade-7.7.0\inc
win32: DEPENDPATH += C:\OpenCASCADE-7.7.0-vc14-64\opencascade-7.7.0\win64\vc14\bin
win32: LIBS += -LC:\OpenCASCADE-7.7.0-vc14-64\opencascade-7.7.0\win64\vc14\lib\ \
    -lTKernel \
    -lTKBRep \
    -lTKBO \
    -lTKFillet \
    -lTKG2d \
    -lTKG3d \
    -lTKGeomBase \
    -lTKMath \
    -lTKOffset \
    -lTKPrim \
    -lTKSTEP \
    -lTKTopAlgo \
    -lTKXSBase

DISTFILES += \
    LICENSE

RESOURCES += \
    resources.qrc

#RC_ICONS = Icon.ico
