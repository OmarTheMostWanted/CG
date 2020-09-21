# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.17.3)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(gsllite-populate NONE)

include(ExternalProject)
ExternalProject_Add(gsllite-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/gsl-lite/gsl-lite.git" "GIT_TAG" "v0.37.0" "GIT_SHALLOW" "TRUE"
                    SOURCE_DIR          "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/gsllite-src"
                    BINARY_DIR          "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/gsllite-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)
