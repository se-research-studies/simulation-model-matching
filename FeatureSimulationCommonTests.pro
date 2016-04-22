TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$_PRO_FILE_PWD_/include/

unix:!macx: LIBS += -L$$PWD/build/ -lFeatureSimulationCommon
LIBS += -lpthread -lgtest -pthread

HEADERS += \
    test/common/datamanagement/correlationdao_test.h

SOURCES += \
    test/common/datamanagement/correlationdao_test.cpp \
    test/test_main.cpp

