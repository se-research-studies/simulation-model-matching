TARGET = FeatureSimulationCommon
TEMPLATE = lib
CONFIG += c++11
CONFIG -= qt

INCLUDEPATH += $$_PRO_FILE_PWD_/include/

LIBS += -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab
LIBS += -lopendavinci -lopendlv -lautomotivedata
LIBS += -ljsoncpp -lsqlite3

HEADERS += \
    src/common/data/coordinates.h \
    src/common/data/feature.h \
    src/common/data/featureset.h \
    src/common/data/dirtyframe.h \
    src/common/data/region.h \
    src/common/datamanagement/correlationdao.h \
    src/common/datamanagement/featuresetdao.h \
    src/common/datamanagement/ronidao.h \
    src/common/datamanagement/database.h \
    src/common/datamanagement/cursor.h \
    src/common/makeunique.h \
    src/common/datamanagement/tablefield.h \
    src/common/utils.h \
    src/common/datamanagement/dataaccessobject.h \
    src/common/datamanagement/tablecolumn.h \
    src/common/data/simulationdata.h \
    src/common/data/simulationframedata.h \
    src/common/datamanagement/simulationdatadao.h \
    src/common/data/rectangle.h \
    src/common/data/recordingsection.h \
    src/common/data/correlation.h \
    src/common/data/permutation.h

SOURCES += \
    src/common/data/coordinates.cpp \
    src/common/data/feature.cpp \
    src/common/data/featureset.cpp \
    src/common/data/dirtyframe.cpp \
    src/common/data/region.cpp \
    src/common/datamanagement/correlationdao.cpp \
    src/common/datamanagement/featuresetdao.cpp \
    src/common/datamanagement/ronidao.cpp \
    src/common/datamanagement/database.cpp \
    src/common/datamanagement/cursor.cpp \
    src/common/datamanagement/tablefield.cpp \
    src/common/utils.cpp \
    src/common/datamanagement/dataaccessobject.cpp \
    src/common/datamanagement/tablecolumn.cpp \
    src/common/data/simulationframedata.cpp \
    src/common/data/simulationdata.cpp \
    src/common/datamanagement/simulationdatadao.cpp \
    src/common/data/rectangle.cpp \
    src/common/data/recordingsection.cpp \
    src/common/data/correlation.cpp \
    src/common/data/permutation.cpp
