TARGET=FeatureExtractor

INCLUDEPATH += $$_PRO_FILE_PWD_/include/

QT += core
QT -= gui

CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

LIBS += -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab
LIBS += -lopendavinci -lopendlv -lautomotivedata
LIBS += -ljsoncpp

SOURCES += \
    src/main.cpp \
    src/data/region.cpp \
    src/data/feature.cpp \
    src/data/position.cpp \
    src/data/coordinates.cpp \
    src/data/frame.cpp \
    src/data/simulation.cpp \
    src/data/featuremodel.cpp \
    src/data/featureset.cpp \
    src/data/correlation.cpp \
    src/data/management/featuremodeldao.cpp \
    src/data/management/correlationdao.cpp \
    src/data/management/featuresetdao.cpp \
    src/data/management/ronidao.cpp


HEADERS += \
    src/data/region.h \
    src/data/feature.h \
    src/data/position.h \
    src/data/coordinates.h \
    src/data/frame.h \
    src/data/simulation.h \
    src/data/featuremodel.h \
    src/data/featureset.h \
    src/data/correlation.h \
    src/data/management/featuremodeldao.h \
    src/data/management/correlationdao.h \
    src/data/management/featuresetdao.h \
    src/data/management/ronidao.h

