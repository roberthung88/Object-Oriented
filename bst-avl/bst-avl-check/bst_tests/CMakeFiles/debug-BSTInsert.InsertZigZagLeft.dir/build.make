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

# Utility rule file for debug-BSTInsert.InsertZigZagLeft.

# Include the progress variables for this target.
include bst_tests/CMakeFiles/debug-BSTInsert.InsertZigZagLeft.dir/progress.make

bst_tests/CMakeFiles/debug-BSTInsert.InsertZigZagLeft:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/work/hw-juipohun/hw6/bst-avl/bst-avl-check/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Debugging BSTInsert.InsertZigZagLeft with GDB..."
	cd /work/hw-juipohun/hw6/bst-avl && gdb --args /work/hw-juipohun/hw6/bst-avl/bst-avl-check/bst_tests/bst_tests --gtest_filter=BSTInsert.InsertZigZagLeft

debug-BSTInsert.InsertZigZagLeft: bst_tests/CMakeFiles/debug-BSTInsert.InsertZigZagLeft
debug-BSTInsert.InsertZigZagLeft: bst_tests/CMakeFiles/debug-BSTInsert.InsertZigZagLeft.dir/build.make

.PHONY : debug-BSTInsert.InsertZigZagLeft

# Rule to build all files generated by this target.
bst_tests/CMakeFiles/debug-BSTInsert.InsertZigZagLeft.dir/build: debug-BSTInsert.InsertZigZagLeft

.PHONY : bst_tests/CMakeFiles/debug-BSTInsert.InsertZigZagLeft.dir/build

bst_tests/CMakeFiles/debug-BSTInsert.InsertZigZagLeft.dir/clean:
	cd /work/hw-juipohun/hw6/bst-avl/bst-avl-check/bst_tests && $(CMAKE_COMMAND) -P CMakeFiles/debug-BSTInsert.InsertZigZagLeft.dir/cmake_clean.cmake
.PHONY : bst_tests/CMakeFiles/debug-BSTInsert.InsertZigZagLeft.dir/clean

bst_tests/CMakeFiles/debug-BSTInsert.InsertZigZagLeft.dir/depend:
	cd /work/hw-juipohun/hw6/bst-avl/bst-avl-check && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /work/hw-juipohun/hw6/bst-avl/bst-avl-check /work/hw-juipohun/hw6/bst-avl/bst-avl-check/bst_tests /work/hw-juipohun/hw6/bst-avl/bst-avl-check /work/hw-juipohun/hw6/bst-avl/bst-avl-check/bst_tests /work/hw-juipohun/hw6/bst-avl/bst-avl-check/bst_tests/CMakeFiles/debug-BSTInsert.InsertZigZagLeft.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bst_tests/CMakeFiles/debug-BSTInsert.InsertZigZagLeft.dir/depend

