cmake_minimum_required(VERSION 2.8)
project(WORD-CLASSIFIER)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set( CMAKE_VERBOSE_MAKEFILE on )

# QT Imports
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)


set(INCLUDE_DIRECTORIES ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS})

include_directories(${INCLUDE_DIRECTORIES})

set(GUI_LIBS Qt5::Widgets Qt5::Core Qt5::Gui)
set(LIB_LIBS Qt5::Core Qt5::Gui)

set(CMAKE_AUTOMOC ON)

SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${OpenMP_CXX_FLAGS} -O2 -g -std=c++11 -pthread")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OpenMP_CXX_FLAGS} -O2 -std=c++11 -pthread")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${OpenMP_CXX_FLAGS} -O0 -g -std=c++11 -pthread")
SET(CMAKE_BUILD_TYPE DEBUG)
#SET(CMAKE_BUILD_TYPE RELEASE)
#SET(CMAKE_BUILD_TYPE RELWITHDEBINFO)

SET(FILE_MANAGER_SRC filemanager/tree_file_strength filemanager/tree_file_strength.tpp
filemanager/utils filemanager/tree_file_elimination filemanager/constants filemanager/converter
filemanager/file_utils filemanager/tree_file_elimination.tpp filemanager/endings_analyzer filemanager/endings_analyzer.tpp
filemanager/start_analyzer filemanager/start_analyzer.tpp filemanager/settings
filemanager/char_combination filemanager/combination_filewriter filemanager/combination_filewriter.tpp
filemanager/character_occurence_analyzer filemanager/logger)
SET(SRC_FILES main)

add_executable(Analyzer ${SRC_FILES} ${FILE_MANAGER_SRC})

#add_library(RadialDistributionAnalyser SHARED ${ANALYSER_SRC_FILES} ${CORE_SRC_FILES} ${UTILS_SRC_FILES})
#target_link_libraries(RadialDistributionAnalyser ${LIB_LIBS})

#add_library(RadialDistributionReproducer SHARED ${REPRODUCTION_SRC_FILES} ${CORE_SRC_FILES} ${UTILS_SRC_FILES} analyser/analysis_configuration)
#target_link_libraries(RadialDistributionReproducer ${LIB_LIBS})

