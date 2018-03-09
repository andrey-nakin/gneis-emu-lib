#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(gneis-emu-lib VERSION 0.1.0 DESCRIPTION "GNEIS Facility Emulation Library")
set (CMAKE_CXX_STANDARD 11)

set(GNEISEMULIB_MAJOR_VERSION 0)
set(GNEISEMULIB_MINOR_VERSION 1)
set(GNEISEMULIB_PATCH_VERSION 0)
set(GNEISEMULIB_VERSION
  ${GNEISEMULIB_MAJOR_VERSION}.${GNEISEMULIB_MINOR_VERSION}.${GNEISEMULIB_PATCH_VERSION})

#----------------------------------------------------------------------------
# Find Geant4 package
#
find_package(Geant4 REQUIRED)

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add and configure the library
#
add_library(gneis-emu-lib STATIC ${SOURCES} ${HEADERS})
set_target_properties(gneis-emu-lib PROPERTIES VERSION ${PROJECT_VERSION})
#set_target_properties(gneis-emu-lib PROPERTIES PUBLIC_HEADER ${HEADERS})
target_include_directories(gneis-emu-lib PRIVATE include)
include(GNUInstallDirs)

set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include")

configure_file(cmake/gneis-emu-lib-config.cmake.in
  "${PROJECT_BINARY_DIR}/gneis-emu-lib-config.cmake" @ONLY)
configure_file(cmake/gneis-emu-lib-config-version.cmake.in
  "${PROJECT_BINARY_DIR}/gneis-emu-lib-config-version.cmake" @ONLY)

#----------------------------------------------------------------------------
# Install the library
#
install(TARGETS gneis-emu-lib
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

