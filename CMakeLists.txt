#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(GNEISEMULIB LANGUAGES CXX VERSION 0.2.0 DESCRIPTION "GNEIS Facility Emulation Library")

set (CMAKE_CXX_STANDARD 11)
add_definitions(
  -DGNEISEMULIB_VERSION_MAJOR=${GNEISEMULIB_VERSION_MAJOR}
  -DGNEISEMULIB_VERSION_MINOR=${GNEISEMULIB_VERSION_MINOR}
  -DGNEISEMULIB_VERSION_PATCH=${GNEISEMULIB_VERSION_PATCH})

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
include(GNUInstallDirs)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add and configure the library
#
add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME gneisemu)
target_include_directories(${PROJECT_NAME} PRIVATE include)

set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include")

configure_file(cmake/gneis-emu-lib-config.cmake.in
  "${PROJECT_BINARY_DIR}/gneis-emu-lib-config.cmake" @ONLY)
configure_file(cmake/gneis-emu-lib-config-version.cmake.in
  "${PROJECT_BINARY_DIR}/gneis-emu-lib-config-version.cmake" @ONLY)

#----------------------------------------------------------------------------
# Configure tests
#
enable_testing()
add_subdirectory(test)

#----------------------------------------------------------------------------
# Install the library
#
install(TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/gneis DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

