# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug"

# Include any dependencies generated for this target.
include robot_arm/CMakeFiles/RobotArmLib.dir/depend.make

# Include the progress variables for this target.
include robot_arm/CMakeFiles/RobotArmLib.dir/progress.make

# Include the compile flags for this target's objects.
include robot_arm/CMakeFiles/RobotArmLib.dir/flags.make

robot_arm/CMakeFiles/RobotArmLib.dir/src/robot_arm.cpp.o: robot_arm/CMakeFiles/RobotArmLib.dir/flags.make
robot_arm/CMakeFiles/RobotArmLib.dir/src/robot_arm.cpp.o: ../robot_arm/src/robot_arm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object robot_arm/CMakeFiles/RobotArmLib.dir/src/robot_arm.cpp.o"
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/robot_arm" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RobotArmLib.dir/src/robot_arm.cpp.o -c "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/robot_arm/src/robot_arm.cpp"

robot_arm/CMakeFiles/RobotArmLib.dir/src/robot_arm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RobotArmLib.dir/src/robot_arm.cpp.i"
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/robot_arm" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/robot_arm/src/robot_arm.cpp" > CMakeFiles/RobotArmLib.dir/src/robot_arm.cpp.i

robot_arm/CMakeFiles/RobotArmLib.dir/src/robot_arm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RobotArmLib.dir/src/robot_arm.cpp.s"
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/robot_arm" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/robot_arm/src/robot_arm.cpp" -o CMakeFiles/RobotArmLib.dir/src/robot_arm.cpp.s

# Object files for target RobotArmLib
RobotArmLib_OBJECTS = \
"CMakeFiles/RobotArmLib.dir/src/robot_arm.cpp.o"

# External object files for target RobotArmLib
RobotArmLib_EXTERNAL_OBJECTS =

robot_arm/libRobotArmLib.a: robot_arm/CMakeFiles/RobotArmLib.dir/src/robot_arm.cpp.o
robot_arm/libRobotArmLib.a: robot_arm/CMakeFiles/RobotArmLib.dir/build.make
robot_arm/libRobotArmLib.a: robot_arm/CMakeFiles/RobotArmLib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libRobotArmLib.a"
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/robot_arm" && $(CMAKE_COMMAND) -P CMakeFiles/RobotArmLib.dir/cmake_clean_target.cmake
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/robot_arm" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RobotArmLib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
robot_arm/CMakeFiles/RobotArmLib.dir/build: robot_arm/libRobotArmLib.a

.PHONY : robot_arm/CMakeFiles/RobotArmLib.dir/build

robot_arm/CMakeFiles/RobotArmLib.dir/clean:
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/robot_arm" && $(CMAKE_COMMAND) -P CMakeFiles/RobotArmLib.dir/cmake_clean.cmake
.PHONY : robot_arm/CMakeFiles/RobotArmLib.dir/clean

robot_arm/CMakeFiles/RobotArmLib.dir/depend:
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2" "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/robot_arm" "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug" "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/robot_arm" "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/robot_arm/CMakeFiles/RobotArmLib.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : robot_arm/CMakeFiles/RobotArmLib.dir/depend

