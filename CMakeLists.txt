cmake_minimum_required(VERSION 2.8)

project(PerceCiel)

include(GNUInstallDirs)

#set the path output exe. CMAKE_BUILD_TYPE add release or debug directory
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

#include SFML
find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML2 REQUIRED sfml-graphics>=2.1 sfml-audio>=2.1 sfml-network>=2.1)

#link_directories(${SFML2_sfml-graphics_LIBDIR})
#include_directories(${SFML2_sfml-graphics_INCLUDEDIR})


#include .cpp
file(GLOB_RECURSE source_files src/*)

#include .h
include_directories(include)

#Set executable name and sources for it. source_files is define in file()
add_executable(laucher ${source_files}) 

#Link executable with the library SFML
target_link_libraries(

        laucher

        ${SFML2_LIBRARIES}

)

#include(CPackConfig.cmake)

