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

add_library(Practical3Lib "src/shading.cpp" "src/user_interaction.cpp")
target_include_directories(Practical3Lib PUBLIC "src")
target_link_libraries(Practical3Lib PUBLIC CGFramework OptionalPackages)
target_compile_features(Practical3Lib PUBLIC cxx_std_17)
set_project_warnings(Practical3Lib)
enable_sanitizers(Practical3Lib)

add_executable(Practical3
	"src/main.cpp"
	"src/mesh.cpp"
	"src/draw.cpp")
target_compile_features(Practical3 PRIVATE cxx_std_17)
target_compile_definitions(Practical3 PRIVATE "-DDATA_DIR=\"${CMAKE_CURRENT_LIST_DIR}/data/\"")
target_link_libraries(Practical3 PRIVATE CGFramework Practical3Lib)
enable_sanitizers(Practical3)
set_project_warnings(Practical3)

if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/grading_tests/")
	add_subdirectory("grading_tests")
endif()

