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

# Utility rule file for NightlyStart.

# Include the progress variables for this target.
include _deps/catch2-build/CMakeFiles/NightlyStart.dir/progress.make

_deps/catch2-build/CMakeFiles/NightlyStart:
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/catch2-build" && /home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/ctest -D NightlyStart

NightlyStart: _deps/catch2-build/CMakeFiles/NightlyStart
NightlyStart: _deps/catch2-build/CMakeFiles/NightlyStart.dir/build.make

.PHONY : NightlyStart

# Rule to build all files generated by this target.
_deps/catch2-build/CMakeFiles/NightlyStart.dir/build: NightlyStart

.PHONY : _deps/catch2-build/CMakeFiles/NightlyStart.dir/build

_deps/catch2-build/CMakeFiles/NightlyStart.dir/clean:
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/catch2-build" && $(CMAKE_COMMAND) -P CMakeFiles/NightlyStart.dir/cmake_clean.cmake
.PHONY : _deps/catch2-build/CMakeFiles/NightlyStart.dir/clean

_deps/catch2-build/CMakeFiles/NightlyStart.dir/depend:
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2" "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/catch2-src" "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug" "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/catch2-build" "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/catch2-build/CMakeFiles/NightlyStart.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : _deps/catch2-build/CMakeFiles/NightlyStart.dir/depend

