cmake_minimum_required(VERSION 3.26)
project(RoutePlanner)

set(PRIVATE_WITH_QT6 OFF)
set(PRIVATE_DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Data/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPRIVATE_DATA_DIR=\"${PRIVATE_DATA_DIR}\"")
message(STATUS "PRIVATE_DATA_DIR: ${PRIVATE_DATA_DIR}")
message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(PRIVATE_WITH_QT6)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWITH_QT6")
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(JSONCPP jsoncpp)
    include_directories(${JSONCPP_INCLUDE_DIRS})
    link_directories(${JSONCPP_LIBRARY_DIRS})
endif()

add_executable(RoutePlanner main.cpp
        EVE_SolarSystem.cpp
        EVE_SolarSystem.h
        SolarSystemsMap.cpp
        SolarSystemsMap.h
        EVE_RoutePlanner.cpp
        EVE_RoutePlanner.h
        EVE_ShortestRoute_BFS.cpp
        EVE_ShortestRoute_BFS.h
        EVE_ShortestRoute_BFS_Vertex.h
)

if(PRIVATE_WITH_QT6)
    target_link_libraries(RoutePlanner Qt6::Core)
else()
    target_link_libraries(RoutePlanner ${JSONCPP_LIBRARIES})
endif()