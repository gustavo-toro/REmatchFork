cmake_minimum_required(VERSION 3.14)

enable_testing()

project(rematch LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
	message(STATUS "Build type not specified. Using Release by default.")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(WIN32)
	if(NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
		message(FATAL_ERROR "On Windows MSVC is the only compiler tested, you are on your own.")
	endif()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W3")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Od -Z7")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -g0")
endif()

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

if(SWIG)
	find_package(SWIG 4.0 COMPONENTS python)
	IF(PYTHON_VERSION)
		find_package(Python3 ${PYTHON_VERSION} EXACT REQUIRED COMPONENTS Development)
	else()
		find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
	endif()
	include(${SWIG_USE_FILE})
	# Add support for .swg file
	set(SWIG_SOURCE_FILE_EXTENSIONS ".i" ".swg")
	set(CMAKE_SWIG_OUTDIR "${PROJECT_SOURCE_DIR}/python/packages/pyrematch")
endif()

add_definitions(-DNOPT_CROSSPROD)
# add_definitions(-DNOPT_OFFSET)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/thirdparty)

if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
	# In windows VS Cmake doesn't look for this versions
	set(Boost_ADDITIONAL_VERSIONS "1.74.0;1.74;1.73.0;1.73")
	find_package(Boost 1.58 REQUIRED)
	include_directories(${Boost_INCLUDE_DIRS})
	list(APPEND project_LIBS ${Boost_LIBRARIES})
endif()

add_subdirectory(src)

if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten" AND NOT SWIG AND NOT WIN32)
	add_subdirectory(tests)
endif()
