# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /work/hw-juipohun/hw6/bst-avl/bst-avl-check

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /work/hw-juipohun/hw6/bst-avl/bst-avl-check

# Utility rule file for debug-AVLRuntime.InsertAscending.

# Include the progress variables for this target.
include avl_tests/CMakeFiles/debug-AVLRuntime.InsertAscending.dir/progress.make

avl_tests/CMakeFiles/debug-AVLRuntime.InsertAscending:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/work/hw-juipohun/hw6/bst-avl/bst-avl-check/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Debugging AVLRuntime.InsertAscending with GDB..."
	cd /work/hw-juipohun/hw6/bst-avl && gdb --args /work/hw-juipohun/hw6/bst-avl/bst-avl-check/avl_tests/avl_runtime_tests --gtest_filter=AVLRuntime.InsertAscending

debug-AVLRuntime.InsertAscending: avl_tests/CMakeFiles/debug-AVLRuntime.InsertAscending
debug-AVLRuntime.InsertAscending: avl_tests/CMakeFiles/debug-AVLRuntime.InsertAscending.dir/build.make

.PHONY : debug-AVLRuntime.InsertAscending

# Rule to build all files generated by this target.
avl_tests/CMakeFiles/debug-AVLRuntime.InsertAscending.dir/build: debug-AVLRuntime.InsertAscending

.PHONY : avl_tests/CMakeFiles/debug-AVLRuntime.InsertAscending.dir/build

avl_tests/CMakeFiles/debug-AVLRuntime.InsertAscending.dir/clean:
	cd /work/hw-juipohun/hw6/bst-avl/bst-avl-check/avl_tests && $(CMAKE_COMMAND) -P CMakeFiles/debug-AVLRuntime.InsertAscending.dir/cmake_clean.cmake
.PHONY : avl_tests/CMakeFiles/debug-AVLRuntime.InsertAscending.dir/clean

avl_tests/CMakeFiles/debug-AVLRuntime.InsertAscending.dir/depend:
	cd /work/hw-juipohun/hw6/bst-avl/bst-avl-check && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /work/hw-juipohun/hw6/bst-avl/bst-avl-check /work/hw-juipohun/hw6/bst-avl/bst-avl-check/avl_tests /work/hw-juipohun/hw6/bst-avl/bst-avl-check /work/hw-juipohun/hw6/bst-avl/bst-avl-check/avl_tests /work/hw-juipohun/hw6/bst-avl/bst-avl-check/avl_tests/CMakeFiles/debug-AVLRuntime.InsertAscending.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : avl_tests/CMakeFiles/debug-AVLRuntime.InsertAscending.dir/depend

