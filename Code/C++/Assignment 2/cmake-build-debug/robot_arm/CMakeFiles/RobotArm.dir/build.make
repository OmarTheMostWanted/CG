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
include robot_arm/CMakeFiles/RobotArm.dir/depend.make

# Include the progress variables for this target.
include robot_arm/CMakeFiles/RobotArm.dir/progress.make

# Include the compile flags for this target's objects.
include robot_arm/CMakeFiles/RobotArm.dir/flags.make

robot_arm/CMakeFiles/RobotArm.dir/src/draw.cpp.o: robot_arm/CMakeFiles/RobotArm.dir/flags.make
robot_arm/CMakeFiles/RobotArm.dir/src/draw.cpp.o: ../robot_arm/src/draw.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object robot_arm/CMakeFiles/RobotArm.dir/src/draw.cpp.o"
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/robot_arm" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RobotArm.dir/src/draw.cpp.o -c "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/robot_arm/src/draw.cpp"

robot_arm/CMakeFiles/RobotArm.dir/src/draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RobotArm.dir/src/draw.cpp.i"
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/robot_arm" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/robot_arm/src/draw.cpp" > CMakeFiles/RobotArm.dir/src/draw.cpp.i

robot_arm/CMakeFiles/RobotArm.dir/src/draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RobotArm.dir/src/draw.cpp.s"
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/robot_arm" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/robot_arm/src/draw.cpp" -o CMakeFiles/RobotArm.dir/src/draw.cpp.s

robot_arm/CMakeFiles/RobotArm.dir/src/main.cpp.o: robot_arm/CMakeFiles/RobotArm.dir/flags.make
robot_arm/CMakeFiles/RobotArm.dir/src/main.cpp.o: ../robot_arm/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object robot_arm/CMakeFiles/RobotArm.dir/src/main.cpp.o"
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/robot_arm" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RobotArm.dir/src/main.cpp.o -c "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/robot_arm/src/main.cpp"

robot_arm/CMakeFiles/RobotArm.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RobotArm.dir/src/main.cpp.i"
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/robot_arm" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/robot_arm/src/main.cpp" > CMakeFiles/RobotArm.dir/src/main.cpp.i

robot_arm/CMakeFiles/RobotArm.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RobotArm.dir/src/main.cpp.s"
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/robot_arm" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/robot_arm/src/main.cpp" -o CMakeFiles/RobotArm.dir/src/main.cpp.s

robot_arm/CMakeFiles/RobotArm.dir/src/reference.cpp.o: robot_arm/CMakeFiles/RobotArm.dir/flags.make
robot_arm/CMakeFiles/RobotArm.dir/src/reference.cpp.o: ../robot_arm/src/reference.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object robot_arm/CMakeFiles/RobotArm.dir/src/reference.cpp.o"
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/robot_arm" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RobotArm.dir/src/reference.cpp.o -c "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/robot_arm/src/reference.cpp"

robot_arm/CMakeFiles/RobotArm.dir/src/reference.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RobotArm.dir/src/reference.cpp.i"
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/robot_arm" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/robot_arm/src/reference.cpp" > CMakeFiles/RobotArm.dir/src/reference.cpp.i

robot_arm/CMakeFiles/RobotArm.dir/src/reference.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RobotArm.dir/src/reference.cpp.s"
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/robot_arm" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/robot_arm/src/reference.cpp" -o CMakeFiles/RobotArm.dir/src/reference.cpp.s

# Object files for target RobotArm
RobotArm_OBJECTS = \
"CMakeFiles/RobotArm.dir/src/draw.cpp.o" \
"CMakeFiles/RobotArm.dir/src/main.cpp.o" \
"CMakeFiles/RobotArm.dir/src/reference.cpp.o"

# External object files for target RobotArm
RobotArm_EXTERNAL_OBJECTS =

robot_arm/RobotArm: robot_arm/CMakeFiles/RobotArm.dir/src/draw.cpp.o
robot_arm/RobotArm: robot_arm/CMakeFiles/RobotArm.dir/src/main.cpp.o
robot_arm/RobotArm: robot_arm/CMakeFiles/RobotArm.dir/src/reference.cpp.o
robot_arm/RobotArm: robot_arm/CMakeFiles/RobotArm.dir/build.make
robot_arm/RobotArm: robot_arm/libRobotArmLib.a
robot_arm/RobotArm: framework/libCGFramework.a
robot_arm/RobotArm: /usr/lib64/libGLU.so
robot_arm/RobotArm: /usr/lib64/libGLX.so
robot_arm/RobotArm: /usr/lib64/libOpenGL.so
robot_arm/RobotArm: framework/libimgui.a
robot_arm/RobotArm: _deps/glfw-build/src/libglfw3.a
robot_arm/RobotArm: /usr/lib64/librt.so
robot_arm/RobotArm: /usr/lib64/libm.so
robot_arm/RobotArm: /usr/lib64/libX11.so
robot_arm/RobotArm: framework/glad/libglad.a
robot_arm/RobotArm: _deps/fmt-build/libfmtd.a
robot_arm/RobotArm: robot_arm/CMakeFiles/RobotArm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable RobotArm"
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/robot_arm" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RobotArm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
robot_arm/CMakeFiles/RobotArm.dir/build: robot_arm/RobotArm

.PHONY : robot_arm/CMakeFiles/RobotArm.dir/build

robot_arm/CMakeFiles/RobotArm.dir/clean:
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/robot_arm" && $(CMAKE_COMMAND) -P CMakeFiles/RobotArm.dir/cmake_clean.cmake
.PHONY : robot_arm/CMakeFiles/RobotArm.dir/clean

robot_arm/CMakeFiles/RobotArm.dir/depend:
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2" "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/robot_arm" "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug" "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/robot_arm" "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/robot_arm/CMakeFiles/RobotArm.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : robot_arm/CMakeFiles/RobotArm.dir/depend

