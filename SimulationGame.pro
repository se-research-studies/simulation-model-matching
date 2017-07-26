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
    src/simulationgame/odvcontrol.cpp \
    src/simulationgame/autopilots/lanefollower.cpp \
    src/simulationgame/datagatherer.cpp \
    src/simulationgame/settings.cpp \
    src/simulationgame/gamerunner.cpp \
    src/simulationgame/simsettingsreader.cpp \
    src/simulationgame/abstractautopilot.cpp \
    src/simulationgame/autopilotregistry.cpp

HEADERS += \
    gamestarter.h \
    src/simulationgame/odvcontrol.h \
    src/simulationgame/autopilots/lanefollower.h \
    src/simulationgame/datagatherer.h \
    src/simulationgame/settings.h \
    src/simulationgame/gamerunner.h \
    src/simulationgame/simsettingsreader.h \
    src/simulationgame/abstractautopilot.h \
    src/simulationgame/autopilotregistry.h


