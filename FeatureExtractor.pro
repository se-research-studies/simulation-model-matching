TARGET=NoiseExtractor

INCLUDEPATH += $$_PRO_FILE_PWD_/include/

QT += core
QT -= gui

CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

LIBS += -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab
LIBS += -lopendavinci -lopendlv -lautomotivedata

SOURCES += \
    src/main.cpp \
    src/DataManagement/region.cpp \
    src/DataManagement/feature.cpp \
    src/DataManagement/position.cpp \
    src/DataManagement/coordinates.cpp


HEADERS += \
    src/DataManagement/region.h \
    src/DataManagement/feature.h \
    src/DataManagement/position.h \
    src/DataManagement/coordinates.h

