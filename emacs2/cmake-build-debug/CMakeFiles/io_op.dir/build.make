# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/paulhondola/Faculta/sda_2_1_hondola_paul/emacs2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/paulhondola/Faculta/sda_2_1_hondola_paul/emacs2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/io_op.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/io_op.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/io_op.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/io_op.dir/flags.make

CMakeFiles/io_op.dir/src/lib/io_op/io_op.c.o: CMakeFiles/io_op.dir/flags.make
CMakeFiles/io_op.dir/src/lib/io_op/io_op.c.o: /Users/paulhondola/Faculta/sda_2_1_hondola_paul/emacs2/src/lib/io_op/io_op.c
CMakeFiles/io_op.dir/src/lib/io_op/io_op.c.o: CMakeFiles/io_op.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/paulhondola/Faculta/sda_2_1_hondola_paul/emacs2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/io_op.dir/src/lib/io_op/io_op.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/io_op.dir/src/lib/io_op/io_op.c.o -MF CMakeFiles/io_op.dir/src/lib/io_op/io_op.c.o.d -o CMakeFiles/io_op.dir/src/lib/io_op/io_op.c.o -c /Users/paulhondola/Faculta/sda_2_1_hondola_paul/emacs2/src/lib/io_op/io_op.c

CMakeFiles/io_op.dir/src/lib/io_op/io_op.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/io_op.dir/src/lib/io_op/io_op.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/paulhondola/Faculta/sda_2_1_hondola_paul/emacs2/src/lib/io_op/io_op.c > CMakeFiles/io_op.dir/src/lib/io_op/io_op.c.i

CMakeFiles/io_op.dir/src/lib/io_op/io_op.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/io_op.dir/src/lib/io_op/io_op.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/paulhondola/Faculta/sda_2_1_hondola_paul/emacs2/src/lib/io_op/io_op.c -o CMakeFiles/io_op.dir/src/lib/io_op/io_op.c.s

# Object files for target io_op
io_op_OBJECTS = \
"CMakeFiles/io_op.dir/src/lib/io_op/io_op.c.o"

# External object files for target io_op
io_op_EXTERNAL_OBJECTS =

libio_op.a: CMakeFiles/io_op.dir/src/lib/io_op/io_op.c.o
libio_op.a: CMakeFiles/io_op.dir/build.make
libio_op.a: CMakeFiles/io_op.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/paulhondola/Faculta/sda_2_1_hondola_paul/emacs2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libio_op.a"
	$(CMAKE_COMMAND) -P CMakeFiles/io_op.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/io_op.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/io_op.dir/build: libio_op.a
.PHONY : CMakeFiles/io_op.dir/build

CMakeFiles/io_op.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/io_op.dir/cmake_clean.cmake
.PHONY : CMakeFiles/io_op.dir/clean

CMakeFiles/io_op.dir/depend:
	cd /Users/paulhondola/Faculta/sda_2_1_hondola_paul/emacs2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/paulhondola/Faculta/sda_2_1_hondola_paul/emacs2 /Users/paulhondola/Faculta/sda_2_1_hondola_paul/emacs2 /Users/paulhondola/Faculta/sda_2_1_hondola_paul/emacs2/cmake-build-debug /Users/paulhondola/Faculta/sda_2_1_hondola_paul/emacs2/cmake-build-debug /Users/paulhondola/Faculta/sda_2_1_hondola_paul/emacs2/cmake-build-debug/CMakeFiles/io_op.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/io_op.dir/depend
