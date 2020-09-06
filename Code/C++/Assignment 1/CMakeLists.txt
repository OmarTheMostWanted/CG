# FetchContent = CMake 3.11
cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(ComputerGraphics CXX)

if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/framework")
	# Create framework library and include CMake scripts (compiler warnings, sanitizers and static analyzers).
	add_subdirectory("framework")
else()
	# During development the framework lives in parent folder.
	add_subdirectory("../../../framework/" "${CMAKE_BINARY_DIR}/framework/")
endif()
get_optional_packages(TARGET OptionalPackages PACKAGES "catch2" "assimp")

add_library(Practical1Lib "src/la_exercises.cpp" "src/cpp_exercises.cpp")
target_include_directories(Practical1Lib PUBLIC "src")
target_link_libraries(Practical1Lib PUBLIC CGFrameworkBase OptionalPackages)
target_compile_features(Practical1Lib PUBLIC cxx_std_17)

add_executable(Practical1
	"src/main.cpp")
target_compile_features(Practical1 PRIVATE cxx_std_17)
target_link_libraries(Practical1 PRIVATE CGFrameworkBase Practical1Lib)

if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/grading_tests/")
	add_subdirectory("grading_tests")
endif()

