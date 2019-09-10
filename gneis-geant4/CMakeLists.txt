#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(GneisGeant4Lib VERSION 0.6.5 LANGUAGES CXX DESCRIPTION "GNEIS Facility Modeling Library")

include(GNUInstallDirs)
set (CMAKE_CXX_STANDARD 14)
add_definitions(
  -DGNEISGEANT4LIB_VERSION_MAJOR=${GneisGeant4Lib_VERSION_MAJOR}
  -DGNEISGEANT4LIB_VERSION_MINOR=${GneisGeant4Lib_VERSION_MINOR}
  -DGNEISGEANT4LIB_VERSION_PATCH=${GneisGeant4Lib_VERSION_PATCH})

#----------------------------------------------------------------------------
# Find Geant4 package
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
  add_definitions(-DGNEISGEANT4LIB_NO_VIS)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/private-include)
include(GNUInstallDirs)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/include/*.hh)
file(GLOB_RECURSE PRIVATE_HEADERS ${PROJECT_SOURCE_DIR}/private-include/*.hh)

#----------------------------------------------------------------------------
# Add and configure the library
#
add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${PRIVATE_HEADERS})
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME gneis-geant4)
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

#----------------------------------------------------------------------------
# Configure tests
#
enable_testing()
add_subdirectory(test)

#----------------------------------------------------------------------------
# Install the library
#
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT ${PROJECT_NAME}Config DESTINATION share/${PROJECT_NAME}/cmake)
export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}Config.cmake)

