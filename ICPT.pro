QT        += core
QT        += gui
QT        += widgets
QT        += opengl
QT        += network
QT        += sql
QT        += script
QT        += xml

# CONFIG    += console

TARGET     = ICPT
TEMPLATE   = app

include ($${PWD}/CA/CA.pri)
include ($${PWD}/System/System.pri)
include ($${PWD}/UI/UI.pri)

DEFINES   += QT_DEPRECATED_WARNINGS

SOURCES   += $${PWD}/ICPT.cpp

HEADERS   += $${PWD}/ICPT.hpp

FORMS     += $${PWD}/ICPT.ui

RESOURCES += $${PWD}/RCC/ICPT.qrc

win32 {
LIBS      += -lopengl32
LIBS      += -lglu32
}
