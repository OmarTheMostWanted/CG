# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.17.3)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(assimp-populate NONE)

include(ExternalProject)
ExternalProject_Add(assimp-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/assimp/assimp.git" "GIT_TAG" "v5.0.1" "GIT_SHALLOW" "TRUE"
                    SOURCE_DIR          "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src"
                    BINARY_DIR          "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)
