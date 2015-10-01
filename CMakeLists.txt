project(transfer CXX)

cmake_minimum_required(VERSION 3.2.2)

add_definitions(-DVERSION_MAJOR=0)
add_definitions(-DVERSION_MINOR=0)
add_definitions(-DVERSION_PATCH=1)
add_definitions(-DAPPLICATION_NAME="Transfer")

find_package(Qt5 COMPONENTS Core Gui Widgets Qml Quick Sql)

set(CMAKE_AUTOMOC TRUE)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# C++11
add_definitions("-std=gnu++11")

# src
add_subdirectory(src)
add_subdirectory(testapp)
