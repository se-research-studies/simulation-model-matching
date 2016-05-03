TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$_PRO_FILE_PWD_/include/

LIBS += -L$$PWD/bin/ -lFeatureSimulationCommon
LIBS += -lpthread -lgtest -pthread

HEADERS += \
    test/common/datamanagement/correlationdao_test.h \
    test/common/datamanagement/ronidao_test.h \
    test/common/datamanagement/featuresetdao_test.h \
    test/common/datamanagement/feature_test.h \
    test/common/datamanagement/frame_test.h \
    test/common/datamanagement/featuremodeldao_test.h \
    test/common/datamanagement/position_test.h \
    test/common/datamanagement/featureset_test.h

SOURCES += \
    test/common/datamanagement/correlationdao_test.cpp \
    test/main_common_test.cpp \
    test/common/datamanagement/ronidao_test.cpp \
    test/common/datamanagement/featuresetdao_test.cpp \
    test/common/datamanagement/feature_test.cpp \
    test/common/datamanagement/frame_test.cpp \
    test/common/datamanagement/featuremodeldao_test.cpp \
    test/common/datamanagement/position_test.cpp \
    test/common/datamanagement/featureset_test.cpp

