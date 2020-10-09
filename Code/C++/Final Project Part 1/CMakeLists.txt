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

# Create library containing the code that the students need to implement. This library is linked to both
# the main application as well as the grading tests. 
add_library(FinalProject1Lib STATIC "src/ray_tracing.cpp" "src/scene.cpp" "src/mesh.cpp")
target_include_directories(FinalProject1Lib PUBLIC "src")
target_link_libraries(FinalProject1Lib PUBLIC CGFramework OptionalPackages)
target_compile_features(FinalProject1Lib PUBLIC cxx_std_17)
set_project_warnings(FinalProject1Lib)
enable_sanitizers(FinalProject1Lib)

add_executable(FinalProject1
	"src/main.cpp"
	"src/draw.cpp")
# Link to all dependencies / make their header files available.
target_link_libraries(FinalProject1 PRIVATE FinalProject1Lib CGFramework)
target_compile_features(FinalProject1 PRIVATE cxx_std_17) # C++17
enable_sanitizers(FinalProject1)
set_project_warnings(FinalProject1)

target_compile_definitions(FinalProject1 PRIVATE
	"-DDATA_DIR=\"${CMAKE_CURRENT_LIST_DIR}/data/\""
	"-DOUTPUT_DIR=\"${CMAKE_CURRENT_LIST_DIR}/\"")

if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/grading_tests/")
	add_subdirectory("grading_tests")
endif()
