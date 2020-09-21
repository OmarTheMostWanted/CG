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

add_executable(LinearAlgebra
	"src/main.cpp"
	"src/la.cpp"
	"src/draw.cpp")
target_compile_features(LinearAlgebra PRIVATE cxx_std_17) # C++17
target_link_libraries(LinearAlgebra PRIVATE CGFramework)
enable_sanitizers(LinearAlgebra)
set_project_warnings(LinearAlgebra)
target_compile_definitions(LinearAlgebra PRIVATE "-DDATA_DIR=\"${CMAKE_CURRENT_LIST_DIR}/data/\"")
