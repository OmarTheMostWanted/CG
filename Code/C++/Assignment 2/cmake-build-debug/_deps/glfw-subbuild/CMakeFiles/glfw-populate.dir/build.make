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
CMAKE_SOURCE_DIR = "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild"

# Utility rule file for glfw-populate.

# Include the progress variables for this target.
include CMakeFiles/glfw-populate.dir/progress.make

CMakeFiles/glfw-populate: CMakeFiles/glfw-populate-complete


CMakeFiles/glfw-populate-complete: glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-install
CMakeFiles/glfw-populate-complete: glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-mkdir
CMakeFiles/glfw-populate-complete: glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-download
CMakeFiles/glfw-populate-complete: glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-update
CMakeFiles/glfw-populate-complete: glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-patch
CMakeFiles/glfw-populate-complete: glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-configure
CMakeFiles/glfw-populate-complete: glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-build
CMakeFiles/glfw-populate-complete: glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-install
CMakeFiles/glfw-populate-complete: glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-test
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Completed 'glfw-populate'"
	/home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake -E make_directory "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild/CMakeFiles"
	/home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake -E touch "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild/CMakeFiles/glfw-populate-complete"
	/home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake -E touch "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-done"

glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-install: glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-build
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "No install step for 'glfw-populate'"
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-build" && /home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake -E echo_append
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-build" && /home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake -E touch "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-install"

glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Creating directories for 'glfw-populate'"
	/home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake -E make_directory "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-src"
	/home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake -E make_directory "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-build"
	/home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake -E make_directory "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild/glfw-populate-prefix"
	/home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake -E make_directory "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild/glfw-populate-prefix/tmp"
	/home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake -E make_directory "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp"
	/home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake -E make_directory "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild/glfw-populate-prefix/src"
	/home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake -E make_directory "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp"
	/home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake -E touch "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-mkdir"

glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-download: glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-gitinfo.txt
glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-download: glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Performing download step (git clone) for 'glfw-populate'"
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps" && /home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake -P "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild/glfw-populate-prefix/tmp/glfw-populate-gitclone.cmake"
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps" && /home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake -E touch "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-download"

glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-update: glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Performing update step for 'glfw-populate'"
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-src" && /home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake -P "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild/glfw-populate-prefix/tmp/glfw-populate-gitupdate.cmake"

glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-patch: glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "No patch step for 'glfw-populate'"
	/home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake -E echo_append
	/home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake -E touch "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-patch"

glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-configure: glfw-populate-prefix/tmp/glfw-populate-cfgcmd.txt
glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-configure: glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-update
glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-configure: glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "No configure step for 'glfw-populate'"
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-build" && /home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake -E echo_append
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-build" && /home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake -E touch "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-configure"

glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-build: glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "No build step for 'glfw-populate'"
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-build" && /home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake -E echo_append
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-build" && /home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake -E touch "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-build"

glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-test: glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-install
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "No test step for 'glfw-populate'"
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-build" && /home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake -E echo_append
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-build" && /home/tmw/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7319.72/bin/cmake/linux/bin/cmake -E touch "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-test"

glfw-populate: CMakeFiles/glfw-populate
glfw-populate: CMakeFiles/glfw-populate-complete
glfw-populate: glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-install
glfw-populate: glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-mkdir
glfw-populate: glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-download
glfw-populate: glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-update
glfw-populate: glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-patch
glfw-populate: glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-configure
glfw-populate: glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-build
glfw-populate: glfw-populate-prefix/src/glfw-populate-stamp/glfw-populate-test
glfw-populate: CMakeFiles/glfw-populate.dir/build.make

.PHONY : glfw-populate

# Rule to build all files generated by this target.
CMakeFiles/glfw-populate.dir/build: glfw-populate

.PHONY : CMakeFiles/glfw-populate.dir/build

CMakeFiles/glfw-populate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/glfw-populate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/glfw-populate.dir/clean

CMakeFiles/glfw-populate.dir/depend:
	cd "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild" "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild" "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild" "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild" "/home/tmw/CLionProjects/CG/Code/C++/Assignment 2/cmake-build-debug/_deps/glfw-subbuild/CMakeFiles/glfw-populate.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/glfw-populate.dir/depend

