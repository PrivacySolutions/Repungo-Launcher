#
#

project(Repungo)
cmake_minimum_required(VERSION 2.8)

# Add path for custom modules
set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules"
  )

# compiler flags customization (by vendor)
add_definitions ( "-Wall -Wextra -fPIC" )

find_package (Qt5Core)
find_package (Qt5Gui)

# check for c++11 support
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" CXX11_SUPPORTED)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" CXX0X_SUPPORTED)
if (CXX11_SUPPORTED)
  add_definitions( "-std=c++11" )
elseif (CXX0X_SUPPORTED) # gcc 4.6
  add_definitions( "-std=c++0x" )
else ()
  message(SEND_ERROR "C++11 standart not seems to be supported by compiler. Too old version?")
endif ()

# paths
set ( CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules" )
set ( CMAKE_SOURCE_DIR "src" )
set ( PROJECT_ROOT "." )

set (SOURCE_FILES
  "${CMAKE_SOURCE_DIR}/main.cpp"
  "${CMAKE_SOURCE_DIR}/repugnoapplication.cpp"
  "${CMAKE_SOURCE_DIR}/repugnotray.cpp"
  "${CMAKE_SOURCE_DIR}/i2plauncher.cpp"
  "${CMAKE_SOURCE_DIR}/utils.cpp"
  "${CMAKE_SOURCE_DIR}/applauncher.cpp"
  "${CMAKE_SOURCE_DIR}/childprocessthread.cpp"
  )

file (GLOB HEADERS "${CMAKE_SOURCE_DIR}/*.h")
set ( HEADERS
  "${HEADERS}"
  "${PROJECT_ROOT}/build.h"
  )

# MSVS grouping
source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCE_FILES})

add_executable ( "repungo" ${SOURCE_FILES} )

