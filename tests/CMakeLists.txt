
set(GTEST_VERSION 1.10.0 CACHE STRING "Google test version")

################################
# GTest
################################
FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-${GTEST_VERSION})

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

enable_testing()

################################
# Unit Tests
################################
# Add test cpp file
set(CMAKE_CXX_FLAGS "-DGTEST_USE_OWN_TR1_TUPLE=1")
add_executable(runUnitTests HexagonLibraryTest.cpp)

target_include_directories(runUnitTests PRIVATE
        $<TARGET_PROPERTY:gtest,INTERFACE_SYSTEM_INCLUDE_DIRECTORIES>
        $<TARGET_PROPERTY:gtest_main,INTERFACE_SYSTEM_INCLUDE_DIRECTORIES>
        ../include)


# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTests gtest gtest_main)

add_test(runUnitTests runUnitTests)