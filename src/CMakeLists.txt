cmake_minimum_required (VERSION 2.6)
project (ADXAS)

# Flags
add_definitions("-std=c++11")

# The version number.
set (ADXAS_VERSION_MAJOR 0)
set (ADXAS_VERSION_MINOR 1)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/ADXASConfig.h.in"
  "${PROJECT_BINARY_DIR}/ADXASConfig.h"
  )

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

# Main exe (ADXAS)
add_executable(ADXAS main.cpp)

# BOOST
FIND_PACKAGE( Boost 1.40 COMPONENTS program_options thread REQUIRED )
target_link_libraries(ADXAS Boost::program_options Boost::thread)

