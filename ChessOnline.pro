#-------------------------------------------------
#
# Project created by QtCreator 2019-08-26T12:03:54
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChessOnline
TEMPLATE = app
RC_ICONS = chess.ico
VERSION = 1.1

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        Chessman/abstractchessman.cpp \
        Chessman/chessinfo.cpp \
        Chessman/chessmanbishop.cpp \
        Chessman/chessmanking.cpp \
        Chessman/chessmanknight.cpp \
        Chessman/chessmanpawn.cpp \
        Chessman/chessmanqueen.cpp \
        Chessman/chessmanrook.cpp \
        Chessman/pawnpromotion.cpp \
        Network/chessconnection.cpp \
        Network/chessmessage.cpp \
        Network/connectserver.cpp \
        Network/startserver.cpp \
        chessboard.cpp \
        gamesetting.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        Chessman/abstractchessman.h \
        Chessman/chessinfo.h \
        Chessman/chessmanbishop.h \
        Chessman/chessmanking.h \
        Chessman/chessmanknight.h \
        Chessman/chessmanpawn.h \
        Chessman/chessmanqueen.h \
        Chessman/chessmanrook.h \
        Chessman/chessmen \
        Chessman/pawnpromotion.h \
        Network/chessconnection.h \
        Network/chessmessage.h \
        Network/connectserver.h \
        Network/startserver.h \
        chessboard.h \
        gamesetting.h \
        mainwindow.h

FORMS += \
        Chessman/pawnpromotion.ui \
        Network/connectserver.ui \
        Network/startserver.ui \
        gamesetting.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES +=
