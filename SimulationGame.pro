TARGET = simulationGame
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$_PRO_FILE_PWD_/include/

LIBS += -L$$PWD/bin/ -lFeatureSimulationCommon

SOURCES += \
    src/main_simulationgame.cpp \
    src/simulationgame/measurementtaker.cpp \
    src/simulationgame/odvcontrol.cpp

HEADERS += \
    gamestarter.h \
    src/simulationgame/measurementtaker.h \
    src/simulationgame/odvcontrol.h


