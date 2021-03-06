#######################################################################################################################
#                                    Ground speed regulator for the taxing and run-out stage.                         #
#                                                                                                                     #
# Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                          Created 24 may 2017 at 08:14 #
#######################################################################################################################

TEMPLATE=app
TARGET=build/tengu_ground_speed_regulator

QT += core
QT -= network widgets gui

CONFIG += qt warn_on release thread rtti c++11
#
#QMAKE_CXXFLAGS += -fPIC -pthread

MOC_DIR=build/moc
UI_DIR=build/uic
RCC_DIR=build/obj
OBJECTS_DIR=build/obj

LIBS += -L../../core -L../../loredis -ltengu_common -lLoRedis -levent -lhiredis 
#-lopencv_core -lopencv_video -lopencv_highgui -lopencv_imgproc 

INCLUDEPATH += ../../core  ../  ../../loredis/src/

HEADERS += 

SOURCES += main.cpp  


