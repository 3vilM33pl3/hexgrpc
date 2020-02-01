cmake_minimum_required(VERSION 3.15)

project(hexgrpc
        VERSION 0.1
        DESCRIPTION "Hexagon server"
        LANGUAGES CXX)

# Let's ensure -std=c++xx instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
include(CTest)
find_package(Doxygen)
if(Doxygen_FOUND)
    add_subdirectory(docs)
else()
    message(STATUS "Doxygen not found, not building docs")
endif()

set(Boost_USE_MULTITHREADED ON)
find_package(Boost REQUIRED program_options)

include(FetchContent)

# Formatting library
FetchContent_Declare(
        fmtlib
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG        5.3.0
)
FetchContent_MakeAvailable(fmtlib)

FetchContent_Declare(
        grpc
        GIT_REPOSITORY https://github.com/grpc/grpc.git
        GIT_TAG        v1.26.0)
FetchContent_MakeAvailable(grpc)

FetchContent_Declare(
        cli
        GIT_REPOSITORY  https://github.com/daniele77/cli.git
        GIT_TAG         v1.1.1
)
FetchContent_MakeAvailable(cli)

add_subdirectory(hexlib)
add_subdirectory(apps)