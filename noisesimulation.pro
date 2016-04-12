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
    src/framecorrelation.cpp \
    src/recording.cpp \
    src/simulation.cpp \
    src/frame.cpp \
    src/noise.cpp \
    src/sequence.cpp \
    src/main.cpp \
    src/savable.cpp \
    src/dataaccessobject.cpp \
    src/noisedao.cpp \
    src/framecorrelationdao.cpp \
    src/datasource.cpp \
    src/sqlitedatasource.cpp \
    src/filedatasource.cpp

HEADERS += \
    src/framecorrelation.h \
    src/recording.h \
    src/simulation.h \
    src/frame.h \
    src/noise.h \
    src/sequence.h \
    src/savable.h \
    src/dataaccessobject.h \
    src/noisedao.h \
    src/framecorrelationdao.h \
    src/datasource.h \
    src/sqlitedatasource.h \
    src/filedatasource.h
