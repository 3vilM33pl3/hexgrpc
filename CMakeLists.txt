cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
project(hexgrpc
        LANGUAGES CXX
        VERSION 0.1
        DESCRIPTION "Hexagon server"
        )

set(OPENSSL_NO_ASM TRUE)

# Let's ensure -std=c++xx instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(Doxygen)
if(Doxygen_FOUND)
    add_subdirectory(docs)
else()
    message(STATUS "Doxygen not found, not building docs")
endif()

include(FetchContent)

set(Boost_DEBUG ON)
set(BUILD_TESTING OFF)
set(Boost_USE_MULTITHREADED ON)

IF (WIN32)
#    set(BOOST_ROOT  $ENV{BOOST_ROOT_1_69_0})
#    set(BOOST_ROOT C:/local/boost_1_69_0)
    set(BOOST_ROOT C:/hostedtoolcache/windows/Boost/1.69.0)
    set(Boost_NO_SYSTEM_PATHS ON)
    set(Boost_USE_STATIC_LIBS        ON) # only find static libs
    set(Boost_LIB_VERSION mgw81)
    set(Boost_ARCHITECTURE -x64)
ENDIF()
find_package(Boost REQUIRED COMPONENTS program_options)
#find_package(Boost COMPONENTS program_options)

# Formatting library
FetchContent_Declare(
        fmtlib
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG        5.3.0
)
FetchContent_MakeAvailable(fmtlib)

FetchContent_Declare(
        grpc
        GIT_REPOSITORY https://github.com/3vilM33pl3/grpc
        GIT_TAG        master)
FetchContent_MakeAvailable(grpc)

FetchContent_Declare(
        cli
        GIT_REPOSITORY  https://github.com/daniele77/cli.git
        GIT_TAG         v1.1.1
)
FetchContent_MakeAvailable(cli)

add_subdirectory(hexlib)
#add_subdirectory(apps)

install(TARGETS grpc grpc++ grpc++_unsecure grpc_cpp_plugin LIBRARY)