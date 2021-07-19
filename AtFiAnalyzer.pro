QT       += core gui charts printsupport

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
    mvp/common/mvpcanvas.cpp \
    mvp/common/presenter.cpp \
    mvp/common/router.cpp \
    mvp/common/view.cpp \
    mvp/components/customchart/customchart.cpp \
    mvp/components/navigatepanel/navigatepanel.cpp \
    mvp/gui/presenter/dashboardscreen/dashboardscreenpresenter.cpp \
    mvp/gui/presenter/setupscreen/setupscreenpresenter.cpp \
    mvp/gui/view/dashboardscreen/dashboardscreenview.cpp \
    mvp/gui/view/setupscreen/setupscreenview.cpp \
    mvp/model/model.cpp \
    mvp/model/settings.cpp \
    src/main.cpp \
    src/qcustomplot.cpp

HEADERS += \
    include/qcustomplot.h \
    mvp/common/mvpcanvas.h \
    mvp/common/presenter.h \
    mvp/common/router.h \
    mvp/common/view.h \
    mvp/components/customchart/customchart.h \
    mvp/components/navigatepanel/navigatepanel.h \
    mvp/gui/presenter/dashboardscreen/dashboardscreenpresenter.h \
    mvp/gui/presenter/setupscreen/setupscreenpresenter.h \
    mvp/gui/view/dashboardscreen/dashboardscreenview.h \
    mvp/gui/view/setupscreen/setupscreenview.h \
    mvp/model/model.h \
    mvp/model/settings.h

FORMS += \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += \
    include/

RESOURCES += \
    stylesheet/stylesheet.qrc

unix|win32: LIBS += -LC:\Workspace\AtFiAnalyzer\lib/ -llibfftw3-3

INCLUDEPATH += C:\Workspace\fftw-3.3.5-dll64
DEPENDPATH += C:\Workspace\AtFiAnalyzer\lib
