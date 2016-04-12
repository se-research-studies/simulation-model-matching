TARGET=SimulationModelMatching

INCLUDEPATH += $$_PRO_FILE_PWD_/include/

QT += core
QT -= gui

CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

LIBS += -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab
LIBS += -lopendavinci -lopendlv -lautomotivedata

SOURCES += $$PWD/apps/simulation-model-matching.cpp \
    src/Correspondence.cpp \
    src/FeatureExtractor.cpp \
    src/Historizer.cpp \
    src/LineDetector.cpp \
    src/Noise.cpp \
    src/ORBMatcher.cpp \
    src/RecordedSequence.cpp \
    src/ShiTomasiMatcher.cpp \
    src/SimulationModelMatching.cpp

HEADERS += \
    src/Correspondence.h \
    src/FeatureExtractor.h \
    src/Historizer.h \
    src/LineDetector.h \
    src/Noise.h \
    src/ORBMatcher.h \
    src/RecordedSequence.h \
    src/ShiTomasiMatcher.h
