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

# Include any dependencies generated for this target.
include bst_tests/CMakeFiles/bst_tests.dir/depend.make

# Include the progress variables for this target.
include bst_tests/CMakeFiles/bst_tests.dir/progress.make

# Include the compile flags for this target's objects.
include bst_tests/CMakeFiles/bst_tests.dir/flags.make

bst_tests/CMakeFiles/bst_tests.dir/test_insert.cpp.o: bst_tests/CMakeFiles/bst_tests.dir/flags.make
bst_tests/CMakeFiles/bst_tests.dir/test_insert.cpp.o: bst_tests/test_insert.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/work/hw-juipohun/hw6/bst-avl/bst-avl-check/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bst_tests/CMakeFiles/bst_tests.dir/test_insert.cpp.o"
	cd /work/hw-juipohun/hw6/bst-avl/bst-avl-check/bst_tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bst_tests.dir/test_insert.cpp.o -c /work/hw-juipohun/hw6/bst-avl/bst-avl-check/bst_tests/test_insert.cpp

bst_tests/CMakeFiles/bst_tests.dir/test_insert.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bst_tests.dir/test_insert.cpp.i"
	cd /work/hw-juipohun/hw6/bst-avl/bst-avl-check/bst_tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /work/hw-juipohun/hw6/bst-avl/bst-avl-check/bst_tests/test_insert.cpp > CMakeFiles/bst_tests.dir/test_insert.cpp.i

bst_tests/CMakeFiles/bst_tests.dir/test_insert.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bst_tests.dir/test_insert.cpp.s"
	cd /work/hw-juipohun/hw6/bst-avl/bst-avl-check/bst_tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /work/hw-juipohun/hw6/bst-avl/bst-avl-check/bst_tests/test_insert.cpp -o CMakeFiles/bst_tests.dir/test_insert.cpp.s

bst_tests/CMakeFiles/bst_tests.dir/test_insert.cpp.o.requires:

.PHONY : bst_tests/CMakeFiles/bst_tests.dir/test_insert.cpp.o.requires

bst_tests/CMakeFiles/bst_tests.dir/test_insert.cpp.o.provides: bst_tests/CMakeFiles/bst_tests.dir/test_insert.cpp.o.requires
	$(MAKE) -f bst_tests/CMakeFiles/bst_tests.dir/build.make bst_tests/CMakeFiles/bst_tests.dir/test_insert.cpp.o.provides.build
.PHONY : bst_tests/CMakeFiles/bst_tests.dir/test_insert.cpp.o.provides

bst_tests/CMakeFiles/bst_tests.dir/test_insert.cpp.o.provides.build: bst_tests/CMakeFiles/bst_tests.dir/test_insert.cpp.o


bst_tests/CMakeFiles/bst_tests.dir/test_remove.cpp.o: bst_tests/CMakeFiles/bst_tests.dir/flags.make
bst_tests/CMakeFiles/bst_tests.dir/test_remove.cpp.o: bst_tests/test_remove.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/work/hw-juipohun/hw6/bst-avl/bst-avl-check/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object bst_tests/CMakeFiles/bst_tests.dir/test_remove.cpp.o"
	cd /work/hw-juipohun/hw6/bst-avl/bst-avl-check/bst_tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bst_tests.dir/test_remove.cpp.o -c /work/hw-juipohun/hw6/bst-avl/bst-avl-check/bst_tests/test_remove.cpp

bst_tests/CMakeFiles/bst_tests.dir/test_remove.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bst_tests.dir/test_remove.cpp.i"
	cd /work/hw-juipohun/hw6/bst-avl/bst-avl-check/bst_tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /work/hw-juipohun/hw6/bst-avl/bst-avl-check/bst_tests/test_remove.cpp > CMakeFiles/bst_tests.dir/test_remove.cpp.i

bst_tests/CMakeFiles/bst_tests.dir/test_remove.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bst_tests.dir/test_remove.cpp.s"
	cd /work/hw-juipohun/hw6/bst-avl/bst-avl-check/bst_tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /work/hw-juipohun/hw6/bst-avl/bst-avl-check/bst_tests/test_remove.cpp -o CMakeFiles/bst_tests.dir/test_remove.cpp.s

bst_tests/CMakeFiles/bst_tests.dir/test_remove.cpp.o.requires:

.PHONY : bst_tests/CMakeFiles/bst_tests.dir/test_remove.cpp.o.requires

bst_tests/CMakeFiles/bst_tests.dir/test_remove.cpp.o.provides: bst_tests/CMakeFiles/bst_tests.dir/test_remove.cpp.o.requires
	$(MAKE) -f bst_tests/CMakeFiles/bst_tests.dir/build.make bst_tests/CMakeFiles/bst_tests.dir/test_remove.cpp.o.provides.build
.PHONY : bst_tests/CMakeFiles/bst_tests.dir/test_remove.cpp.o.provides

bst_tests/CMakeFiles/bst_tests.dir/test_remove.cpp.o.provides.build: bst_tests/CMakeFiles/bst_tests.dir/test_remove.cpp.o


bst_tests/CMakeFiles/bst_tests.dir/test_balance.cpp.o: bst_tests/CMakeFiles/bst_tests.dir/flags.make
bst_tests/CMakeFiles/bst_tests.dir/test_balance.cpp.o: bst_tests/test_balance.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/work/hw-juipohun/hw6/bst-avl/bst-avl-check/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object bst_tests/CMakeFiles/bst_tests.dir/test_balance.cpp.o"
	cd /work/hw-juipohun/hw6/bst-avl/bst-avl-check/bst_tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bst_tests.dir/test_balance.cpp.o -c /work/hw-juipohun/hw6/bst-avl/bst-avl-check/bst_tests/test_balance.cpp

bst_tests/CMakeFiles/bst_tests.dir/test_balance.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bst_tests.dir/test_balance.cpp.i"
	cd /work/hw-juipohun/hw6/bst-avl/bst-avl-check/bst_tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /work/hw-juipohun/hw6/bst-avl/bst-avl-check/bst_tests/test_balance.cpp > CMakeFiles/bst_tests.dir/test_balance.cpp.i

bst_tests/CMakeFiles/bst_tests.dir/test_balance.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bst_tests.dir/test_balance.cpp.s"
	cd /work/hw-juipohun/hw6/bst-avl/bst-avl-check/bst_tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /work/hw-juipohun/hw6/bst-avl/bst-avl-check/bst_tests/test_balance.cpp -o CMakeFiles/bst_tests.dir/test_balance.cpp.s

bst_tests/CMakeFiles/bst_tests.dir/test_balance.cpp.o.requires:

.PHONY : bst_tests/CMakeFiles/bst_tests.dir/test_balance.cpp.o.requires

bst_tests/CMakeFiles/bst_tests.dir/test_balance.cpp.o.provides: bst_tests/CMakeFiles/bst_tests.dir/test_balance.cpp.o.requires
	$(MAKE) -f bst_tests/CMakeFiles/bst_tests.dir/build.make bst_tests/CMakeFiles/bst_tests.dir/test_balance.cpp.o.provides.build
.PHONY : bst_tests/CMakeFiles/bst_tests.dir/test_balance.cpp.o.provides

bst_tests/CMakeFiles/bst_tests.dir/test_balance.cpp.o.provides.build: bst_tests/CMakeFiles/bst_tests.dir/test_balance.cpp.o


# Object files for target bst_tests
bst_tests_OBJECTS = \
"CMakeFiles/bst_tests.dir/test_insert.cpp.o" \
"CMakeFiles/bst_tests.dir/test_remove.cpp.o" \
"CMakeFiles/bst_tests.dir/test_balance.cpp.o"

# External object files for target bst_tests
bst_tests_EXTERNAL_OBJECTS =

bst_tests/bst_tests: bst_tests/CMakeFiles/bst_tests.dir/test_insert.cpp.o
bst_tests/bst_tests: bst_tests/CMakeFiles/bst_tests.dir/test_remove.cpp.o
bst_tests/bst_tests: bst_tests/CMakeFiles/bst_tests.dir/test_balance.cpp.o
bst_tests/bst_tests: bst_tests/CMakeFiles/bst_tests.dir/build.make
bst_tests/bst_tests: testing_utils/libtesting_utils.a
bst_tests/bst_tests: /usr/lib/libgtest_main.a
bst_tests/bst_tests: /usr/lib/libgtest.a
bst_tests/bst_tests: testing_utils/kwsys/libkwsys.a
bst_tests/bst_tests: testing_utils/libperf/libperf.a
bst_tests/bst_tests: bst_tests/CMakeFiles/bst_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/work/hw-juipohun/hw6/bst-avl/bst-avl-check/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable bst_tests"
	cd /work/hw-juipohun/hw6/bst-avl/bst-avl-check/bst_tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bst_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bst_tests/CMakeFiles/bst_tests.dir/build: bst_tests/bst_tests

.PHONY : bst_tests/CMakeFiles/bst_tests.dir/build

bst_tests/CMakeFiles/bst_tests.dir/requires: bst_tests/CMakeFiles/bst_tests.dir/test_insert.cpp.o.requires
bst_tests/CMakeFiles/bst_tests.dir/requires: bst_tests/CMakeFiles/bst_tests.dir/test_remove.cpp.o.requires
bst_tests/CMakeFiles/bst_tests.dir/requires: bst_tests/CMakeFiles/bst_tests.dir/test_balance.cpp.o.requires

.PHONY : bst_tests/CMakeFiles/bst_tests.dir/requires

bst_tests/CMakeFiles/bst_tests.dir/clean:
	cd /work/hw-juipohun/hw6/bst-avl/bst-avl-check/bst_tests && $(CMAKE_COMMAND) -P CMakeFiles/bst_tests.dir/cmake_clean.cmake
.PHONY : bst_tests/CMakeFiles/bst_tests.dir/clean

bst_tests/CMakeFiles/bst_tests.dir/depend:
	cd /work/hw-juipohun/hw6/bst-avl/bst-avl-check && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /work/hw-juipohun/hw6/bst-avl/bst-avl-check /work/hw-juipohun/hw6/bst-avl/bst-avl-check/bst_tests /work/hw-juipohun/hw6/bst-avl/bst-avl-check /work/hw-juipohun/hw6/bst-avl/bst-avl-check/bst_tests /work/hw-juipohun/hw6/bst-avl/bst-avl-check/bst_tests/CMakeFiles/bst_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bst_tests/CMakeFiles/bst_tests.dir/depend

