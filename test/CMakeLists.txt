cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(IsnpEmuLibTest LANGUAGES CXX)

include(FindGTest)
find_package(GTest REQUIRED)
find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/include/*.hh)
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cc)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME isnpemutest)

target_link_libraries(${PROJECT_NAME} GTest::GTest GTest::Main)
target_link_libraries(${PROJECT_NAME} ${Geant4_LIBRARIES})
target_link_libraries(${PROJECT_NAME} IsnpEmuLib)

add_test(
  NAME ${PROJECT_NAME}
  COMMAND ${PROJECT_NAME}
)

