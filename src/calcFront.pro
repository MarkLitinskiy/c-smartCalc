QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH += ../src/cpp

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    c/creditCalculation/creditCalculation.c \
    cpp/creditwindow.cpp \
    c/depositCalculation/depositCalculation.c \
    cpp/depositwindow.cpp \
    cpp/graphwindow.cpp \
    cpp/main.cpp \
    cpp/mainwindow.cpp \
    c/math_errors.c \
    c/parser_coder.c \
    c/parser_of_stacks.c \
    c/polsh_calculate.c \
    cpp/qcustomplot.cpp \
    c/s21_SmartCalc_v1.0.c \
    c/stack_functions.c

HEADERS += \
    c/creditCalculation/creditCalculation.h \
    cpp/creditwindow.h \
    c/depositCalculation/depositCalculation.h \
    cpp/depositwindow.h \
    cpp/graphwindow.h \
    cpp/mainwindow.h \
    cpp/qcustomplot.h \
    c/s21_SmartCalc_v1.0.h

FORMS += \
    ui/creditwindow.ui \
    ui/depositwindow.ui \
    ui/graphwindow.ui \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=
