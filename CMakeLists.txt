#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(GneisEmuLib VERSION 0.2.0 LANGUAGES CXX DESCRIPTION "GNEIS Facility Emulation Library")

include(GNUInstallDirs)
set (CMAKE_CXX_STANDARD 11)
add_definitions(
  -DGNEISEMULIB_VERSION_MAJOR=${GneisEmuLib_VERSION_MAJOR}
  -DGNEISEMULIB_VERSION_MINOR=${GneisEmuLib_VERSION_MINOR}
  -DGNEISEMULIB_VERSION_PATCH=${GneisEmuLib_VERSION_PATCH})

#----------------------------------------------------------------------------
# Find Geant4 package
#
find_package(Geant4 REQUIRED ui_all vis_all)

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

