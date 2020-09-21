# Generated by CMake

if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.5)
   message(FATAL_ERROR "CMake >= 2.6.0 required")
endif()
cmake_policy(PUSH)
cmake_policy(VERSION 2.6)
#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

if(CMAKE_VERSION VERSION_LESS 3.0.0)
  message(FATAL_ERROR "This file relies on consumers using CMake 3.0.0 or greater.")
endif()

# Protect against multiple inclusion, which would fail when already imported targets are added once more.
set(_targetsDefined)
set(_targetsNotDefined)
set(_expectedTargets)
foreach(_expectedTarget gsl::gsl-lite gsl::gsl-lite-v0 gsl::gsl-lite-v1)
  list(APPEND _expectedTargets ${_expectedTarget})
  if(NOT TARGET ${_expectedTarget})
    list(APPEND _targetsNotDefined ${_expectedTarget})
  endif()
  if(TARGET ${_expectedTarget})
    list(APPEND _targetsDefined ${_expectedTarget})
  endif()
endforeach()
if("${_targetsDefined}" STREQUAL "${_expectedTargets}")
  unset(_targetsDefined)
  unset(_targetsNotDefined)
  unset(_expectedTargets)
  set(CMAKE_IMPORT_FILE_VERSION)
  cmake_policy(POP)
  return()
endif()
if(NOT "${_targetsDefined}" STREQUAL "")
  message(FATAL_ERROR "Some (but not all) targets in this export set were already defined.\nTargets Defined: ${_targetsDefined}\nTargets not yet defined: ${_targetsNotDefined}\n")
endif()
unset(_targetsDefined)
unset(_targetsNotDefined)
unset(_expectedTargets)


# Create imported target gsl::gsl-lite
add_library(gsl::gsl-lite INTERFACE IMPORTED)

set_target_properties(gsl::gsl-lite PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/gsllite-src/include"
  INTERFACE_SOURCES "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/gsllite-src/gsl-lite.natvis"
)

# Create imported target gsl::gsl-lite-v0
add_library(gsl::gsl-lite-v0 INTERFACE IMPORTED)

set_target_properties(gsl::gsl-lite-v0 PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/gsllite-src/include"
  INTERFACE_SOURCES "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/gsllite-src/gsl-lite.natvis"
)

# Create imported target gsl::gsl-lite-v1
add_library(gsl::gsl-lite-v1 INTERFACE IMPORTED)

set_target_properties(gsl::gsl-lite-v1 PROPERTIES
  INTERFACE_COMPILE_DEFINITIONS "gsl_CONFIG_DEFAULTS_VERSION=1"
  INTERFACE_COMPILE_OPTIONS "-DGSL_THROW_ON_CONTRACT_VIOLATION=1"
  INTERFACE_INCLUDE_DIRECTORIES "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/gsllite-src/include"
  INTERFACE_SOURCES "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/gsllite-src/gsl-lite.natvis"
)

# This file does not depend on other imported targets which have
# been exported from the same project but in a separate export set.

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
cmake_policy(POP)
