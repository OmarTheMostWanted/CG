
if(NOT "/home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp/glm-populate-gitinfo.txt" IS_NEWER_THAN "/home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp/glm-populate-gitclone-lastrun.txt")
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: '/home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp/glm-populate-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/_deps/glm-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/_deps/glm-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/bin/git"  clone --no-checkout --depth 1 --no-single-branch "https://github.com/g-truc/glm.git" "glm-src"
    WORKING_DIRECTORY "/home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/_deps"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/g-truc/glm.git'")
endif()

execute_process(
  COMMAND "/usr/bin/git"  checkout 0.9.9.8 --
  WORKING_DIRECTORY "/home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/_deps/glm-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: '0.9.9.8'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/usr/bin/git"  submodule update --recursive --init 
    WORKING_DIRECTORY "/home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/_deps/glm-src"
    RESULT_VARIABLE error_code
    )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/_deps/glm-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "/home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp/glm-populate-gitinfo.txt"
    "/home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp/glm-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/home/tmw/CLionProjects/CG/Code/C++/linear_algebra_exercise/cmake-build-debug/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp/glm-populate-gitclone-lastrun.txt'")
endif()

