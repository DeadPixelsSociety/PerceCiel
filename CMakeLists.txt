cmake_minimum_required(VERSION 2.8)

project(PerceCiel CXX)

include(GNUInstallDirs)

find_package(Boost REQUIRED COMPONENTS filesystem system)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML2 REQUIRED sfml-graphics>=2.1 sfml-audio>=2.1 sfml-network>=2.1)
pkg_check_modules(LIBTMX REQUIRED libtmx0)

add_definitions(-Wall -g -O2)
add_definitions(-std=c++11)

add_subdirectory(games)
