QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cfiles/affine.c \
    cfiles/objfiles.c \
    gifanimcplusplus/gifanim.cpp \
    main.cpp \
    mainscene.cpp \
    mainwindow.cpp \
    scenesettings.cpp

HEADERS += \
    cfiles/affine.h \
    cfiles/objfiles.h \
    gifanimcplusplus/gifanim.h \
    mainscene.h \
    mainwindow.h \
    scenesettings.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=

DISTFILES += \
    README.md \
    gifanimcplusplus/LICENSE \
    gifanimcplusplus/README.md
