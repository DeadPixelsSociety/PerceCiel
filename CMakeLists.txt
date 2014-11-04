cmake_minimum_required(VERSION 2.8)

project(PerceCiel CXX)

#set the path output exe. CMAKE_BUILD_TYPE add release or debug directory
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

#include SFML

# Linux

include(GNUInstallDirs)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML2 REQUIRED sfml-graphics>=2.1 sfml-audio>=2.1 sfml-network>=2.1)
#pkg_check_modules(LIBTMX REQUIRED libtmx0)
#set(Clibtmx0_DIR ~/Documents/lib/libtmx/build/lib)
#set(CMAKE_MODULE_PATH ~/Documents/lib/libtmx/src)

#endlinux

# Windows (don't forget to copy .dll in bin the dir)
## set the path of FindSFML.cmake
#set(CMAKE_MODULE_PATH C:/Libraries/SFML-2/SFML-2.1/cmake/Modules)
#find_package(SFML 2.1 REQUIRED graphics window system)
#endwindows

#compilation variables
add_definitions(-Wall -g -O2)
add_definitions(-std=c++11)

link_directories(${SFML2_sfml-graphics_LIBDIR})
include_directories(${SFML2_sfml-graphics_INCLUDEDIR})

#include .cpp
file(GLOB_RECURSE source_files src/* inc/*)

#include .h
include_directories(inc)

#Set executable name and sources for it. source_files is define in file()
add_executable(laucher ${source_files}) 

#Link executable with the library SFML
target_link_libraries(laucher ${SFML2_LIBRARIES})

#include(CPackConfig.cmake)

