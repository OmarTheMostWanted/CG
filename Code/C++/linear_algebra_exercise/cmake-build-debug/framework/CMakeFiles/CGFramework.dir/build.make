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
CMAKE_COMMAND = /home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.6948.80/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.6948.80/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug

# Include any dependencies generated for this target.
include framework/CMakeFiles/CGFramework.dir/depend.make

# Include the progress variables for this target.
include framework/CMakeFiles/CGFramework.dir/progress.make

# Include the compile flags for this target's objects.
include framework/CMakeFiles/CGFramework.dir/flags.make

framework/CMakeFiles/CGFramework.dir/src/trackball.cpp.o: framework/CMakeFiles/CGFramework.dir/flags.make
framework/CMakeFiles/CGFramework.dir/src/trackball.cpp.o: ../framework/src/trackball.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object framework/CMakeFiles/CGFramework.dir/src/trackball.cpp.o"
	cd /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/framework && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CGFramework.dir/src/trackball.cpp.o -c /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/framework/src/trackball.cpp

framework/CMakeFiles/CGFramework.dir/src/trackball.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CGFramework.dir/src/trackball.cpp.i"
	cd /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/framework && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/framework/src/trackball.cpp > CMakeFiles/CGFramework.dir/src/trackball.cpp.i

framework/CMakeFiles/CGFramework.dir/src/trackball.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CGFramework.dir/src/trackball.cpp.s"
	cd /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/framework && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/framework/src/trackball.cpp -o CMakeFiles/CGFramework.dir/src/trackball.cpp.s

framework/CMakeFiles/CGFramework.dir/src/window.cpp.o: framework/CMakeFiles/CGFramework.dir/flags.make
framework/CMakeFiles/CGFramework.dir/src/window.cpp.o: ../framework/src/window.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object framework/CMakeFiles/CGFramework.dir/src/window.cpp.o"
	cd /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/framework && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CGFramework.dir/src/window.cpp.o -c /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/framework/src/window.cpp

framework/CMakeFiles/CGFramework.dir/src/window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CGFramework.dir/src/window.cpp.i"
	cd /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/framework && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/framework/src/window.cpp > CMakeFiles/CGFramework.dir/src/window.cpp.i

framework/CMakeFiles/CGFramework.dir/src/window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CGFramework.dir/src/window.cpp.s"
	cd /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/framework && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/framework/src/window.cpp -o CMakeFiles/CGFramework.dir/src/window.cpp.s

framework/CMakeFiles/CGFramework.dir/src/shader.cpp.o: framework/CMakeFiles/CGFramework.dir/flags.make
framework/CMakeFiles/CGFramework.dir/src/shader.cpp.o: ../framework/src/shader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object framework/CMakeFiles/CGFramework.dir/src/shader.cpp.o"
	cd /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/framework && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CGFramework.dir/src/shader.cpp.o -c /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/framework/src/shader.cpp

framework/CMakeFiles/CGFramework.dir/src/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CGFramework.dir/src/shader.cpp.i"
	cd /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/framework && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/framework/src/shader.cpp > CMakeFiles/CGFramework.dir/src/shader.cpp.i

framework/CMakeFiles/CGFramework.dir/src/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CGFramework.dir/src/shader.cpp.s"
	cd /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/framework && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/framework/src/shader.cpp -o CMakeFiles/CGFramework.dir/src/shader.cpp.s

framework/CMakeFiles/CGFramework.dir/src/imgui_impl_glfw.cpp.o: framework/CMakeFiles/CGFramework.dir/flags.make
framework/CMakeFiles/CGFramework.dir/src/imgui_impl_glfw.cpp.o: ../framework/src/imgui_impl_glfw.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object framework/CMakeFiles/CGFramework.dir/src/imgui_impl_glfw.cpp.o"
	cd /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/framework && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CGFramework.dir/src/imgui_impl_glfw.cpp.o -c /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/framework/src/imgui_impl_glfw.cpp

framework/CMakeFiles/CGFramework.dir/src/imgui_impl_glfw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CGFramework.dir/src/imgui_impl_glfw.cpp.i"
	cd /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/framework && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/framework/src/imgui_impl_glfw.cpp > CMakeFiles/CGFramework.dir/src/imgui_impl_glfw.cpp.i

framework/CMakeFiles/CGFramework.dir/src/imgui_impl_glfw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CGFramework.dir/src/imgui_impl_glfw.cpp.s"
	cd /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/framework && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/framework/src/imgui_impl_glfw.cpp -o CMakeFiles/CGFramework.dir/src/imgui_impl_glfw.cpp.s

framework/CMakeFiles/CGFramework.dir/src/imgui_impl_opengl2.cpp.o: framework/CMakeFiles/CGFramework.dir/flags.make
framework/CMakeFiles/CGFramework.dir/src/imgui_impl_opengl2.cpp.o: ../framework/src/imgui_impl_opengl2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object framework/CMakeFiles/CGFramework.dir/src/imgui_impl_opengl2.cpp.o"
	cd /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/framework && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CGFramework.dir/src/imgui_impl_opengl2.cpp.o -c /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/framework/src/imgui_impl_opengl2.cpp

framework/CMakeFiles/CGFramework.dir/src/imgui_impl_opengl2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CGFramework.dir/src/imgui_impl_opengl2.cpp.i"
	cd /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/framework && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/framework/src/imgui_impl_opengl2.cpp > CMakeFiles/CGFramework.dir/src/imgui_impl_opengl2.cpp.i

framework/CMakeFiles/CGFramework.dir/src/imgui_impl_opengl2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CGFramework.dir/src/imgui_impl_opengl2.cpp.s"
	cd /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/framework && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/framework/src/imgui_impl_opengl2.cpp -o CMakeFiles/CGFramework.dir/src/imgui_impl_opengl2.cpp.s

framework/CMakeFiles/CGFramework.dir/src/imgui_impl_opengl3.cpp.o: framework/CMakeFiles/CGFramework.dir/flags.make
framework/CMakeFiles/CGFramework.dir/src/imgui_impl_opengl3.cpp.o: ../framework/src/imgui_impl_opengl3.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object framework/CMakeFiles/CGFramework.dir/src/imgui_impl_opengl3.cpp.o"
	cd /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/framework && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CGFramework.dir/src/imgui_impl_opengl3.cpp.o -c /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/framework/src/imgui_impl_opengl3.cpp

framework/CMakeFiles/CGFramework.dir/src/imgui_impl_opengl3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CGFramework.dir/src/imgui_impl_opengl3.cpp.i"
	cd /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/framework && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/framework/src/imgui_impl_opengl3.cpp > CMakeFiles/CGFramework.dir/src/imgui_impl_opengl3.cpp.i

framework/CMakeFiles/CGFramework.dir/src/imgui_impl_opengl3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CGFramework.dir/src/imgui_impl_opengl3.cpp.s"
	cd /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/framework && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/framework/src/imgui_impl_opengl3.cpp -o CMakeFiles/CGFramework.dir/src/imgui_impl_opengl3.cpp.s

# Object files for target CGFramework
CGFramework_OBJECTS = \
"CMakeFiles/CGFramework.dir/src/trackball.cpp.o" \
"CMakeFiles/CGFramework.dir/src/window.cpp.o" \
"CMakeFiles/CGFramework.dir/src/shader.cpp.o" \
"CMakeFiles/CGFramework.dir/src/imgui_impl_glfw.cpp.o" \
"CMakeFiles/CGFramework.dir/src/imgui_impl_opengl2.cpp.o" \
"CMakeFiles/CGFramework.dir/src/imgui_impl_opengl3.cpp.o"

# External object files for target CGFramework
CGFramework_EXTERNAL_OBJECTS =

framework/libCGFramework.a: framework/CMakeFiles/CGFramework.dir/src/trackball.cpp.o
framework/libCGFramework.a: framework/CMakeFiles/CGFramework.dir/src/window.cpp.o
framework/libCGFramework.a: framework/CMakeFiles/CGFramework.dir/src/shader.cpp.o
framework/libCGFramework.a: framework/CMakeFiles/CGFramework.dir/src/imgui_impl_glfw.cpp.o
framework/libCGFramework.a: framework/CMakeFiles/CGFramework.dir/src/imgui_impl_opengl2.cpp.o
framework/libCGFramework.a: framework/CMakeFiles/CGFramework.dir/src/imgui_impl_opengl3.cpp.o
framework/libCGFramework.a: framework/CMakeFiles/CGFramework.dir/build.make
framework/libCGFramework.a: framework/CMakeFiles/CGFramework.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX static library libCGFramework.a"
	cd /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/framework && $(CMAKE_COMMAND) -P CMakeFiles/CGFramework.dir/cmake_clean_target.cmake
	cd /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/framework && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CGFramework.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
framework/CMakeFiles/CGFramework.dir/build: framework/libCGFramework.a

.PHONY : framework/CMakeFiles/CGFramework.dir/build

framework/CMakeFiles/CGFramework.dir/clean:
	cd /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/framework && $(CMAKE_COMMAND) -P CMakeFiles/CGFramework.dir/cmake_clean.cmake
.PHONY : framework/CMakeFiles/CGFramework.dir/clean

framework/CMakeFiles/CGFramework.dir/depend:
	cd /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/framework /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/framework /home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/framework/CMakeFiles/CGFramework.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : framework/CMakeFiles/CGFramework.dir/depend

