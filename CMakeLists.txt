cmake_minimum_required(VERSION 2.8)
project(djiosdk-linux-sample)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -g -O0")


if(NOT CMAKE_MODULE_PATH)
    set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/Onboard-SDK/contrib)
endif()

include(${CMAKE_MODULE_PATH}/DJIConfig.cmake)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/libs)


option(LIDAR_LOGGING "Build VLP16 Puck LiDAR logging" OFF)
option(USE_PRECISION_MISSIONS "Use DJI precision-missions library" OFF)
option(PRECISION_MISSIONS_LIBRARY "WARNING: for custom precision-missions Library only, point to a library location"
    PATH)
option(PRECISION_MISSIONS_INCLUDE_DIR "WARNING: for custom precision-missions library only, point to headers location"
    PATH)
option(PRECISION_MISSIONS_DEPENDENCIES_DIR "WARNING: for custom precision-missions library only, point to dependencies
loacation")
option(USE_COLLISION_AVOIDANCE "Use DJI collision avoidance library" OFF)
option(USE_POINTCLOUD2LAS "Use DJI pointcloud to LAS converter library" OFF)


add_subdirectory(./Onboard-SDK/osdk-core)
add_subdirectory(./Onboard-SDK/osdk-wrapper)
add_subdirectory(./Onboard-SDK/platform/linux)

include_directories(./Onboard-SDK/osdk-core/inc)
include_directories(./Onboard-SDK/osdk-wrapper/inc)
include_directories(./Onboard-SDK/platform/linux/inc)
include_directories(./inc)

FILE(GLOB SOURCE_FILES inc/*.h src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_dependencies(${PROJECT_NAME} djiosdk-wrapper)

set(BLOCKING_LINK_LIBRARIES djiosdk-core djiosdk-platform djiosdk-wrapper)

target_link_libraries(${PROJECT_NAME} ${BLOCKING_LINK_LIBRARIES})

