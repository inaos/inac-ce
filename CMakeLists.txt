#
# Copyright INAOS GmbH, Thalwil, 2018. All rights reserved
#
# This software is the confidential and proprietary information of INAOS GmbH
# ("Confidential Information"). You shall not disclose such Confidential
# Information and shall use it only in accordance with the terms of the
# license agreement you entered into with INAOS GmbH.
#
cmake_minimum_required(VERSION 3.7)
project(inac-ce VERSION 1.0.1)
if(NOT EXISTS "${CMAKE_BINARY_DIR}/inac.cmake")
	if (NOT EXISTS "${CMAKE_SOURCE_DIR}/inac.cmake")
		message(STATUS "Downloading inac.cmake from https://github.com/inaos/inac-cmake")
		file(DOWNLOAD "https://raw.githubusercontent.com/inaos/inac-cmake/0.1/inac.cmake"
			"${CMAKE_BINARY_DIR}/inac.cmake" STATUS DS)
		if(NOT "${DS}"  MATCHES "0;")
			file(REMOVE "${CMAKE_BINARY_DIR}/inac.cmake")
			message(FATAL_ERROR "Failed to download inac.cmake")
		endif()
	else()
		message(STATUS "Use local inac.cmake")
		configure_file("${CMAKE_SOURCE_DIR}/inac.cmake" "${CMAKE_BINARY_DIR}/inac.cmake" COPYONLY)
	endif()
endif()
include("${CMAKE_BINARY_DIR}/inac.cmake")

inac_version_header(include/libinac-ce/version.h)
inac_enable_aes()
inac_enable_sse4()


file(GLOB src ${SRC_DIR}/*.c)
add_library(inac-ce ${src})
set_target_properties(
		inac-ce
		PROPERTIES
		COMPILE_DEFINITIONS INA_LIB=1)


install(TARGETS inac-ce
		DESTINATION lib
		COMPONENT libraries)

inac_package()
