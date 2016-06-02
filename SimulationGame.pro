TARGET = simulationGame
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$_PRO_FILE_PWD_/include/

LIBS += -L$$PWD/bin/ -lFeatureSimulationCommon
LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc
LIBS += -lopendavinci -lopendlv -lautomotivedata

SOURCES += \
    src/main_simulationgame.cpp \
    src/simulationgame/measurementtaker.cpp \
    src/simulationgame/odvcontrol.cpp \
    src/simulationgame/participantregistry.cpp \
    src/simulationgame/abstractparticipant.cpp \
    src/simulationgame/participants/lanefollower.cpp

HEADERS += \
    gamestarter.h \
    src/simulationgame/measurementtaker.h \
    src/simulationgame/odvcontrol.h \
    src/simulationgame/participantregistry.h \
    src/simulationgame/abstractparticipant.h \
    src/simulationgame/participants/lanefollower.h


