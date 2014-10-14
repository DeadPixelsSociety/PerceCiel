cmake_minimum_required(VERSION 2.8)

project(PerceCiel)

include(GNUInstallDirs)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML2 REQUIRED sfml-graphics>=2.1 sfml-audio>=2.1 sfml-network>=2.1)

file(GLOB_RECURSE source_files src/*)

add_executable(laucher ${source_files}) 

#include(CPackConfig.cmake)

