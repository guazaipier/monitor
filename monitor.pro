QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets gui network

CONFIG += c++17

INCLUDEPATH += "D:\3party\opencv\opencv-build\install\include"
LIBS += -L"D:\3party\opencv\opencv-build\install\x64\mingw\lib" -lopencv_core4110 -lopencv_highgui4110 -lopencv_imgcodecs4110 -lopencv_imgproc4110 -lopencv_objdetect4110

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    face.cpp \
    main.cpp \
    monitordialog.cpp

HEADERS += \
    face.h \
    monitordialog.h

FORMS += \
    monitordialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

