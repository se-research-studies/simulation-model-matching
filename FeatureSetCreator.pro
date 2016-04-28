TARGET = createFeatureSet
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$_PRO_FILE_PWD_/include/

LIBS += -L$$PWD/bin/ -lFeatureSimulationCommon

SOURCES += \
    src/main_featuresetcreator.cpp \
    src/featuresetcreation/featuredetector.cpp \
    src/featuresetcreation/featuredetectororb.cpp

HEADERS += \
    src/featuresetcreation/featuredetector.h \
    src/featuresetcreation/featuredetectororb.h


