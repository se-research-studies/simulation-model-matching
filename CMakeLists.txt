CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

PROJECT (FeatureSetCreator)

###########################################################################

SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

###########################################################################
# Set the search path for .cmake files.
SET (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake.Modules" ${CMAKE_MODULE_PATH})

# Add a local CMake module search path dependent on the desired installation destination.
# Thus, artifacts from the complete source build can be given precendence over any installed versions.
IF(UNIX)
    SET (CMAKE_MODULE_PATH "${CMAKE_INSTALL_PREFIX}/share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules" ${CMAKE_MODULE_PATH})
ENDIF()
IF(WIN32)
    SET (CMAKE_MODULE_PATH "${CMAKE_INSTALL_PREFIX}/CMake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules" ${CMAKE_MODULE_PATH})
ENDIF()

###########################################################################
# Include flags for compiling.
INCLUDE (CompileFlags)

###########################################################################
# Find OpenDaVINCI.
SET(OPENDAVINCI_DIR "${CMAKE_INSTALL_PREFIX}")
FIND_PACKAGE (OpenDaVINCI REQUIRED)

###########################################################################
# Find AutomotiveData.
SET(AUTOMOTIVEDATA_DIR "${CMAKE_INSTALL_PREFIX}")
FIND_PACKAGE (AutomotiveData REQUIRED)

###########################################################################
# Find OpenCV.
SET(OpenCV_DIR "/usr")
FIND_PACKAGE (OpenCV REQUIRED)

###########################################################################
# Try to find OpenDLV.
SET(OPENDLV_DIR "${CMAKE_INSTALL_PREFIX}")
FIND_PACKAGE (OpenDLV)

###########################################################################
FIND_PATH(JSONCPP_INCLUDE_DIR NAMES NAMES json/features.h PATH_SUFFIXES jsoncpp PATHS ${Jsoncpp_PKGCONF_INCLUDE_DIRS})
FIND_LIBRARY(JSONCPP_LIBRARY NAMES jsoncpp PATHS ${Jsoncpp_PKGCONF_LIBRARY_DIRS})
if(NOT JSONCPP_INCLUDE_DIR)
  message(SEND_ERROR "Failed to find json/features.h")
endif()
if(NOT JSONCPP_LIBRARY)
  message(SEND_ERROR "Failed to find the jsoncpp library")
endif()

FIND_PATH(SQLITE3_INCLUDE_DIR sqlite3.h)
FIND_LIBRARY(SQLITE3_LIBRARY sqlite3)
if(NOT SQLITE3_INCLUDE_DIR)
  message(SEND_ERROR "Failed to find sqlite3.h")
endif()
if(NOT SQLITE3_LIBRARY)
  message(SEND_ERROR "Failed to find the sqlite3 library")
endif()


###########################################################################
# Set header files from OpenDaVINCI.
INCLUDE_DIRECTORIES (${OPENDAVINCI_INCLUDE_DIRS})
# Set header files from AutomotiveData.
INCLUDE_DIRECTORIES (${AUTOMOTIVEDATA_INCLUDE_DIRS})
# Set header files from OpenDLV.
INCLUDE_DIRECTORIES (${OPENDLV_INCLUDE_DIRS})
# Header for jsoncpp and sqlite3
INCLUDE_DIRECTORIES (${JSONCPP_INCLUDE_DIR})
INCLUDE_DIRECTORIES (${SQLITE3_INCLUDE_DIR})
# Set include directory.
INCLUDE_DIRECTORIES (${PROJECT_SOURCE_DIR}/include)
message(STATUS "Include Dir: " ${PROJECT_SOURCE_DIR}/include)

###########################################################################
# Build the common sources as library
message(STATUS "CommonLib base path: " ${PROJECT_SOURCE_DIR}/src/common/)
FILE(GLOB_RECURSE COMMON_SOURCES ${PROJECT_SOURCE_DIR}/src/common/*.cpp)
FILE(GLOB_RECURSE COMMON_HEADERS ${PROJECT_SOURCE_DIR}/src/common/*.h)
ADD_LIBRARY(CommonLib ${COMMON_SOURCES} ${COMMON_HEADERS})
TARGET_LINK_LIBRARIES (CommonLib ${OPENDAVINCI_LIBRARIES} ${AUTOMOTIVEDATA_LIBRARIES} ${OPENDLV_LIBRARIES} ${OpenCV_LIBS} ${JSONCPP_LIBRARY} ${SQLITE3_LIBRARY}) 

###########################################################################
# Build the FeatureSetCreator sources as library
message(STATUS "FeatureSetCreationLib base path: " ${PROJECT_SOURCE_DIR}/src/featuresetcreation/)
FILE(GLOB_RECURSE FEATURESETCREATION_SOURCES ${PROJECT_SOURCE_DIR}/src/featuresetcreation/*.cpp)
FILE(GLOB_RECURSE FEATURESETCREATION_HEADERS ${PROJECT_SOURCE_DIR}/src/featuresetcreation/*.h)
ADD_LIBRARY(FeatureSetCreationLib ${FEATURESETCREATION_SOURCES} ${FEATURESETCREATION_HEADERS})
TARGET_LINK_LIBRARIES (FeatureSetCreationLib CommonLib) 

###########################################################################
# Build the SimulationGame sources as library
#message(STATUS "SimulationGameLib base path: " ${PROJECT_SOURCE_DIR}/src/simulationgame/)
#FILE(GLOB_RECURSE SIMULATIONGAME_SOURCES ${PROJECT_SOURCE_DIR}/src/simulationgame/*.cpp)
#FILE(GLOB_RECURSE SIMULATIONGAME_HEADERS ${PROJECT_SOURCE_DIR}/src/simulationgame/*.h)
#ADD_LIBRARY(SimulationGameLib ${SIMULATIONGAME_SOURCES} ${SIMULATIONGAME_HEADERS})
#TARGET_LINK_LIBRARIES (SimulationGameLib CommonLib) 

###########################################################################
# Build the CommonTest sources as library
#message(STATUS "CommonTestsLib base path: " ${PROJECT_SOURCE_DIR}/test/common/)
#FILE(GLOB_RECURSE COMMON_TESTS_SOURCES ${PROJECT_SOURCE_DIR}/test/common/*.cpp)
#FILE(GLOB_RECURSE COMMON_TESTS_HEADERS ${PROJECT_SOURCE_DIR}/test/common/*.h)
#ADD_LIBRARY(CommonTestsLib ${COMMON_TESTS_SOURCES} ${COMMON_TESTS_HEADERS})
#TARGET_LINK_LIBRARIES (CommonTestsLib CommonLib) 

###########################################################################
# Build createFeatureSet executable.
message(STATUS "Main file for createFeatureSet: " ${PROJECT_SOURCE_DIR}/src/main_featuresetcreator.cpp)
ADD_EXECUTABLE (createFeatureSet ${PROJECT_SOURCE_DIR}/src/main_featuresetcreator.cpp)
TARGET_LINK_LIBRARIES (createFeatureSet FeatureSetCreationLib) 

###########################################################################
# Build simulationGame executable.
#message(STATUS "Main file for simulationGame: " ${PROJECT_SOURCE_DIR}/src/main_simulationgame.cpp)
#ADD_EXECUTABLE (simulationGame ${PROJECT_SOURCE_DIR}/src/main_simulationgame.cpp)
#TARGET_LINK_LIBRARIES (simulationGame SimulationGameLib) 

###########################################################################
# Build commonTests executable.
#message(STATUS "Main file for commonTests: " ${PROJECT_SOURCE_DIR}/test/main_common_test.cpp)
#ADD_EXECUTABLE (commonTests ${PROJECT_SOURCE_DIR}/test/main_common_test.cpp)
#TARGET_LINK_LIBRARIES (commonTests CommonTestsLib) 

###########################################################################
# This project will not be installed.

