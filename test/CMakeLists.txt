cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(GneisEmuLibTest LANGUAGES CXX)

include(FindGTest)
find_package(GTest REQUIRED)
find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/*.cc)

add_executable(${PROJECT_NAME} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME gneisemutest)

target_link_libraries(${PROJECT_NAME} GTest::GTest GTest::Main)
target_link_libraries(${PROJECT_NAME} ${Geant4_LIBRARIES})
target_link_libraries(${PROJECT_NAME} GneisEmuLib)

add_test(
  NAME ${PROJECT_NAME}
  COMMAND ${PROJECT_NAME}
)

