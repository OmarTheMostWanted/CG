# Create library containing exercisese.h so we can "link" (header-only) to it from the tests.
add_library(RobotArmLib "src/robot_arm.cpp")
target_compile_features(RobotArmLib PUBLIC cxx_std_17) # C++17
target_include_directories(RobotArmLib PUBLIC "${CMAKE_CURRENT_LIST_DIR}/src")
target_link_libraries(RobotArmLib PUBLIC CGFramework)
set_project_warnings(RobotArmLib)
enable_sanitizers(RobotArmLib)

add_executable(RobotArm
	"src/draw.cpp"
	"src/main.cpp"
	"src/reference.cpp")
target_compile_features(RobotArm PRIVATE cxx_std_17) # C++17
target_link_libraries(RobotArm PRIVATE RobotArmLib CGFramework)
enable_sanitizers(RobotArm)
set_project_warnings(RobotArm)
target_compile_definitions(RobotArm PRIVATE "-DDATA_DIR=\"${CMAKE_CURRENT_LIST_DIR}/data/\"")

if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/grading_tests")
	add_subdirectory("grading_tests")
endif()