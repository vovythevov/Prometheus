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

set(${APPLICATION_NAME}_DEPENDENCIES Slicer)

#-----------------------------------------------------------------------------
# WARNING - No change should be required after this comment
#           when you are adding a new external project dependency.
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Declare ${APPLICATION_NAME}_EXTERNAL_LIBRARY_DIRS variable - This variable stores
# the library output directory associated with the different external project
# It's then used in Utilities/LastConfigureStep/${APPLICATION_NAME}Generate${APPLICATION_NAME}Config.cmake to
# configure ${APPLICATION_NAME}Config.cmake.in
# This variable would then be exposed to project building against ${APPLICATION_NAME}
#SET(${APPLICATION_NAME}_EXTERNAL_LIBRARY_DIRS)

#-----------------------------------------------------------------------------
# Git protocole option
#
option(${APPLICATION_NAME}_USE_GIT_PROTOCOL "If behind a firewall turn this OFF to use http instead." ON)

set(git_protocol "git")
if(NOT ${APPLICATION_NAME}_USE_GIT_PROTOCOL)
  set(git_protocol "http")
endif()

#-----------------------------------------------------------------------------
# Enable and setup External project global properties
#

set(ep_suffix      "-cmake")
set(ep_common_c_flags "${CMAKE_C_FLAGS_INIT} ${ADDITIONAL_C_FLAGS}")
set(ep_common_cxx_flags "${CMAKE_CXX_FLAGS_INIT} ${ADDITIONAL_CXX_FLAGS}")

#-----------------------------------------------------------------------------
# Include external projects
#

ExternalProject_Include_Dependencies(${APPLICATION_NAME}
  PROJECT_VAR APPLICATION_NAME
  DEPENDS_VAR ${APPLICATION_NAME}_DEPENDENCIES)
