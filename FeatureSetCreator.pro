TARGET = createFeatureSet
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$_PRO_FILE_PWD_/include/

LIBS += -L$$PWD/bin/ -lFeatureSimulationCommon
LIBS += -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab
LIBS += -lopendavinci -lopendlv -lautomotivedata

SOURCES += \
    src/main_featuresetcreator.cpp \
    src/featuresetcreation/featuredetector.cpp \
    src/featuresetcreation/featuredetectororb.cpp

HEADERS += \
    src/featuresetcreation/featuredetector.h \
    src/featuresetcreation/featuredetectororb.h


