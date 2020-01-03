cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MACOSX_RPATH 1)

project(PiKv)

set(DLIB_DIR   ${CMAKE_SOURCE_DIR}/../minidl/install)
# set(OPENCV_DIR ${CMAKE_SOURCE_DIR}/../minicv/install)

add_subdirectory(dl)
add_subdirectory(PiMien)
# add_subdirectory(PiCim)
