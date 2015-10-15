project(transfer CXX)

# cmake_minimum_required(VERSION 3.2.2)
cmake_minimum_required(VERSION 2.8.12)

add_definitions(-DVERSION_MAJOR=0)
add_definitions(-DVERSION_MINOR=0)
add_definitions(-DVERSION_PATCH=1)
add_definitions(-DAPPLICATION_NAME="Transfer")

find_package(Qt5 COMPONENTS Core Gui Widgets Qml Quick Sql)



option(ENABLE_DEBUG "Enable debug version" ON)
option(ENABLE_WERROR "Enables WError. Always enable when developing, and disable when releasing." ON)

set(CMAKE_AUTOMOC TRUE)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


if(${ENABLE_DEBUG})
    message(STATUS "Building DEBUG version")
    set(CMAKE_BUILD_TYPE Debug)
endif(${ENABLE_DEBUG})

if(${ENABLE_WERROR})
    message(STATUS "-Werror enabled")
    add_definitions("-Werror")
endif(${ENABLE_WERROR})


# C++11
add_definitions("-std=gnu++11")

# src
add_subdirectory(src)
add_subdirectory(testapp)
