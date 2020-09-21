# Create library containing exercisese.h so we can "link" (header-only) to it from the tests.
add_library(SolarSystemLib "src/solar_system.cpp")
target_include_directories(SolarSystemLib PUBLIC "${CMAKE_CURRENT_LIST_DIR}/src")
target_compile_features(SolarSystemLib PUBLIC cxx_std_17) # C++17
target_link_libraries(SolarSystemLib PUBLIC CGFramework)
set_project_warnings(SolarSystemLib)
enable_sanitizers(SolarSystemLib)

add_executable(SolarSystem
	"src/draw.cpp"
	"src/main.cpp"
	"src/reference.cpp")
target_compile_features(SolarSystem PRIVATE cxx_std_17) # C++17
target_link_libraries(SolarSystem PRIVATE SolarSystemLib CGFramework OptionalPackages)
enable_sanitizers(SolarSystem)
set_project_warnings(SolarSystem)
target_compile_definitions(SolarSystem PRIVATE "-DDATA_DIR=\"${CMAKE_CURRENT_LIST_DIR}/data/\"")

if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/grading_tests")
	add_subdirectory("grading_tests")
endif()