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
INCLUDE_DIRECTORIES (${CMAKE_CURRENT_SOURCE_DIR}/include)
# Set include directory.
INCLUDE_DIRECTORIES(include)

###########################################################################
# Build this project.
FILE(GLOB_RECURSE thisproject-sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
ADD_LIBRARY (${PROJECT_NAME}lib STATIC ${thisproject-sources})
ADD_EXECUTABLE (${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/src/main_featuresetcreator.cpp")
TARGET_LINK_LIBRARIES (${PROJECT_NAME} ${PROJECT_NAME}lib ${LIBRARIES}
	       ${JSONCPP_LIBRARY}
               ${SQLITE3_LIBRARY}) 

###########################################################################
# This project will not be installed.

