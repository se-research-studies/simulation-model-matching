TARGET = createFeatureSet
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$_PRO_FILE_PWD_/include/

LIBS += -L$$PWD/bin/ -lFeatureSimulationCommon
LIBS += -lopencv_core -lopencv_features2d -lopencv_highgui -lopencv_imgproc
LIBS += -lopendavinci -lopendlv -lautomotivedata

SOURCES += \
    src/main_featuresetcreator.cpp \
    src/featuresetcreation/featuredetector.cpp \
    src/featuresetcreation/featuresetcreator.cpp \
    src/featuresetcreation/featuredetectororb.cpp \
    src/featuresetcreation/settings.cpp \
    src/featuresetcreation/settingsvalidator.cpp \
    src/featuresetcreation/featuredetectorshitomasi.cpp \
    src/featuresetcreation/recordingplayer.cpp \
    src/featuresetcreation/guicontroler.cpp \
    src/featuresetcreation/imagemasker.cpp \
    src/featuresetcreation/featuresettingsreader.cpp \
    src/featuresetcreation/lanemarkingfilter.cpp

HEADERS += \
    src/featuresetcreation/featuredetector.h \
    src/featuresetcreation/featuresetcreator.h \
    src/featuresetcreation/featuredetectororb.h \
    src/featuresetcreation/settings.h \
    src/featuresetcreation/settingsvalidator.h \
    src/featuresetcreation/featuredetectorshitomasi.h \
    src/featuresetcreation/recordingplayer.h \
    src/featuresetcreation/imagemasker.h \
    src/featuresetcreation/featuresettingsreader.h \
    src/featuresetcreation/guicontroller.h \
    src/featuresetcreation/lanemarkingfilter.h


