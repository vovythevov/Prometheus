# OS: Windows 7 x64
# Hardware: Intel Core2 Duo P8600 2.4GHz
# GPU: GeForce GTX 280M

# Note: The specific version and processor type of this machine should be reported in the
# header above. Indeed, this file will be send to the dashboard as a NOTE file.

#============================================================================
#
# Copyright (c) Kitware Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0.txt
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
#============================================================================

cmake_minimum_required(VERSION 2.8.10)

#-----------------------------------------------------------------------------
# Macro allowing to set a variable to its default value only if not already defined
macro(setOnlyIfNotDefined var defaultvalue)
  if(NOT DEFINED ${var})
    set(${var} "${defaultvalue}")
  endif()
endmacro()

#
# Dashboard properties
#
set(CTEST_PROJECT_NAME "VesselView")

set(CTEST_DASHBOARD_ROOT "/home/kitware/Dashboards/VesselView")
set(CTEST_SITE "melcor.kitware") # for example: mymachine.kitware, mymachine.dkfz, ...
set(MY_OPERATING_SYSTEM "Linux") # Windows, Linux, Darwin...

setOnlyIfNotDefined(MY_CMAKE_VERSION "2.8.10")
setOnlyIfNotDefined(CTEST_CMAKE_COMMAND "usr/bin/cmake.exe") # "C:/Program Files (x86)/CMake ${MY_CMAKE_VERSION}/bin/cmake.exe")

# Compiler to use to compile the project.
# E.g. GCC-4.7, VS2008Express...
setOnlyIfNotDefined(MY_COMPILER "GCC-4.7")
# Bitness of the compiler to use. It can be different than the machine.
# E.g. 64, 32
setOnlyIfNotDefined(MY_BITNESS "32")
# Generator to use when configuring the CMake project.
# E.g. Unix Makefiles, Visual Studio 9 Win32
setOnlyIfNotDefined(CTEST_CMAKE_GENERATOR "Unix Makefiles")
# Build configuration
# E.g. Release, RelWithDebInfo, Debug
setOnlyIfNotDefined(CTEST_BUILD_CONFIGURATION "Release")

# Qt version to use when compiling the project.
# E.g. 4.7.4, 4.8.5
setOnlyIfNotDefined(MY_QT_VERSION "4.7")
# Path of the qmake executable
# E.g. /usr/bin/qmake, C:/work/Qt/qt-${MY_QT_VERSION}-debug-32bit-vs2008/bin/qmake.exe
setOnlyIfNotDefined(QT_QMAKE_EXECUTABLE "usr/bin/qmake.exe")

#
# Dashboard options
#
setOnlyIfNotDefined(WITH_KWSTYLE FALSE)
setOnlyIfNotDefined(WITH_MEMCHECK FALSE)
setOnlyIfNotDefined(WITH_COVERAGE FALSE)
setOnlyIfNotDefined(WITH_DOCUMENTATION FALSE)
setOnlyIfNotDefined(WITH_PACKAGES FALSE)

setOnlyIfNotDefined(CTEST_TEST_TIMEOUT 500)
# Build flags to pass to the generator.
# E.g. -j2, -j8, ""
setOnlyIfNotDefined(CTEST_BUILD_FLAGS "")

# Type of dashboard:
# experimental:
#     - run_ctest() macro will be called *ONE* time
#     - binary directory will *NOT* be cleaned
# continuous:
#     - run_ctest() macro will be called EVERY 5 minutes ...
#     - binary directory will *NOT* be cleaned
#     - configure/build will be executed *ONLY* if the repository has been updated
# nightly:
#     - run_ctest() macro will be called *ONE* time
#     - binary directory *WILL BE* cleaned
# E.g. experimental, continuous, nightly
setOnlyIfNotDefined(SCRIPT_MODE "nightly")

#
# Project specific properties
#
# Path where to save the downloaded (with git) the source of the project.
setOnlyIfNotDefined(CTEST_SOURCE_DIRECTORY "${CTEST_DASHBOARD_ROOT}/${CTEST_PROJECT_NAME}-${SCRIPT_MODE}")
# Path where to build the project
# Must be short (e.g. "c:\Work\D\B-nightly") on Windows
setOnlyIfNotDefined(CTEST_BINARY_DIRECTORY "${CTEST_DASHBOARD_ROOT}/${CTEST_PROJECT_NAME}-${SCRIPT_MODE}-${CTEST_BUILD_CONFIGURATION}-${MY_BITNESS}bits-Qt${MY_QT_VERSION}-CMake${MY_CMAKE_VERSION}")# Path where to save the build logs. Don't forget to create a "Logs" directory.
setOnlyIfNotDefined(CTEST_LOG_FILE "${CTEST_DASHBOARD_ROOT}/Logs/${CTEST_PROJECT_NAME}-${SCRIPT_MODE}-${CTEST_BUILD_CONFIGURATION}-${MY_BITNESS}bits.log")
# File to upload to CDash as notes. The first 3 lines of the script contain
# machine information that is read by CDash.
setOnlyIfNotDefined(CTEST_NOTES_FILES "${CTEST_SCRIPT_DIRECTORY}/${CTEST_SCRIPT_NAME}")

# Additionnal CMakeCache options
setOnlyIfNotDefined(ADDITIONNAL_CMAKECACHE_OPTION "")

# set any extra environment variables here
set(ENV{DISPLAY} ":0")

find_program(CTEST_COVERAGE_COMMAND NAMES gcov)
find_program(CTEST_MEMORYCHECK_COMMAND NAMES valgrind)
find_program(CTEST_GIT_COMMAND NAMES git
  PATHS "/usr/bin/git")

##########################################
# WARNING: DO NOT EDIT BEYOND THIS POINT #
##########################################

#
# Project specific properties
#
set(CTEST_BUILD_NAME "VesselView-${MY_OPERATING_SYSTEM}-${MY_COMPILER}-${MY_BITNESS}-QT${MY_QT_VERSION}-CMake${MY_CMAKE_VERSION}-${CTEST_BUILD_CONFIGURATION}")

#
# Display build info
#
message("site name: ${CTEST_SITE}")
message("build name: ${CTEST_BUILD_NAME}")
message("script mode: ${SCRIPT_MODE}")
message("coverage: ${WITH_COVERAGE}, memcheck: ${WITH_MEMCHECK}")

#
# Include dashboard driver script
#
include("${CTEST_SOURCE_DIRECTORY}/Utilities/Dashboards/VesselView-DashboardDriver.cmake.driver")
