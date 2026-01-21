QT += core gui network widgets

CONFIG += c++17

SOURCES += main.cpp \
    mainwindow.cpp \
    server.cpp

HEADERS += mainwindow.h \
    server.h

# Добавляем стиль (опционально)
DISTFILES += style.qss

