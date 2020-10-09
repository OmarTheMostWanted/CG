# Install script for directory: /home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-build/code/libassimpd.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/anim.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/aabb.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/ai_assert.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/camera.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/color4.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/color4.inl"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-build/code/../include/assimp/config.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/defs.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/Defines.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/cfileio.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/light.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/material.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/material.inl"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/matrix3x3.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/matrix3x3.inl"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/matrix4x4.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/matrix4x4.inl"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/mesh.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/pbrmaterial.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/postprocess.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/quaternion.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/quaternion.inl"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/scene.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/metadata.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/texture.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/types.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/vector2.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/vector2.inl"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/vector3.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/vector3.inl"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/version.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/cimport.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/importerdesc.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/Importer.hpp"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/DefaultLogger.hpp"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/ProgressHandler.hpp"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/IOStream.hpp"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/IOSystem.hpp"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/Logger.hpp"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/LogStream.hpp"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/NullLogger.hpp"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/cexport.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/Exporter.hpp"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/DefaultIOStream.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/DefaultIOSystem.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/ZipArchiveIOSystem.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/SceneCombiner.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/fast_atof.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/qnan.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/BaseImporter.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/Hash.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/MemoryIOWrapper.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/ParsingUtils.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/StreamReader.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/StreamWriter.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/StringComparison.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/StringUtils.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/SGSpatialSort.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/GenericProperty.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/SpatialSort.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/SkeletonMeshBuilder.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/SmoothingGroups.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/SmoothingGroups.inl"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/StandardShapes.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/RemoveComments.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/Subdivision.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/Vertex.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/LineSplitter.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/TinyFormatter.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/Profiler.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/LogAux.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/Bitmap.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/XMLTools.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/IOStreamBuffer.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/CreateAnimMesh.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/irrXMLWrapper.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/BlobIOSystem.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/MathFunctions.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/Macros.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/Exceptional.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/ByteSwapper.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/Compiler/pushpack1.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/Compiler/poppack1.h"
    "/home/tmw/CLionProjects/CG/Code/C++/Final Project Part 1/cmake-build-debug/_deps/assimp-src/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

