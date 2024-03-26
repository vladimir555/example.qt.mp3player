cmake_minimum_required(VERSION 3.5)

project(MP3Player VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets Multimedia REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/source)

file(GLOB_RECURSE SOURCE
    ${CMAKE_SOURCE_DIR}/source/*.h
    ${CMAKE_SOURCE_DIR}/source/*.cpp
)

source_group(TREE ${CMAKE_SOURCE_DIR}/source FILES ${SOURCE})

add_executable(MP3Player ${SOURCE})

target_link_libraries(${PROJECT_NAME} Qt6::Widgets Qt6::Multimedia)
