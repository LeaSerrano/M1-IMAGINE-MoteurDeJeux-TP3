# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lea/M1-IMAGINE/S2/MoteurJeux/M1-IMAGINE-MoteurDeJeux-TP3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lea/M1-IMAGINE/S2/MoteurJeux/M1-IMAGINE-MoteurDeJeux-TP3/build

# Include any dependencies generated for this target.
include external/glfw-3.1.2/examples/CMakeFiles/simple.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include external/glfw-3.1.2/examples/CMakeFiles/simple.dir/compiler_depend.make

# Include the progress variables for this target.
include external/glfw-3.1.2/examples/CMakeFiles/simple.dir/progress.make

# Include the compile flags for this target's objects.
include external/glfw-3.1.2/examples/CMakeFiles/simple.dir/flags.make

external/glfw-3.1.2/examples/CMakeFiles/simple.dir/simple.c.o: external/glfw-3.1.2/examples/CMakeFiles/simple.dir/flags.make
external/glfw-3.1.2/examples/CMakeFiles/simple.dir/simple.c.o: ../external/glfw-3.1.2/examples/simple.c
external/glfw-3.1.2/examples/CMakeFiles/simple.dir/simple.c.o: external/glfw-3.1.2/examples/CMakeFiles/simple.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lea/M1-IMAGINE/S2/MoteurJeux/M1-IMAGINE-MoteurDeJeux-TP3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object external/glfw-3.1.2/examples/CMakeFiles/simple.dir/simple.c.o"
	cd /home/lea/M1-IMAGINE/S2/MoteurJeux/M1-IMAGINE-MoteurDeJeux-TP3/build/external/glfw-3.1.2/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT external/glfw-3.1.2/examples/CMakeFiles/simple.dir/simple.c.o -MF CMakeFiles/simple.dir/simple.c.o.d -o CMakeFiles/simple.dir/simple.c.o -c /home/lea/M1-IMAGINE/S2/MoteurJeux/M1-IMAGINE-MoteurDeJeux-TP3/external/glfw-3.1.2/examples/simple.c

external/glfw-3.1.2/examples/CMakeFiles/simple.dir/simple.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/simple.dir/simple.c.i"
	cd /home/lea/M1-IMAGINE/S2/MoteurJeux/M1-IMAGINE-MoteurDeJeux-TP3/build/external/glfw-3.1.2/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lea/M1-IMAGINE/S2/MoteurJeux/M1-IMAGINE-MoteurDeJeux-TP3/external/glfw-3.1.2/examples/simple.c > CMakeFiles/simple.dir/simple.c.i

external/glfw-3.1.2/examples/CMakeFiles/simple.dir/simple.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/simple.dir/simple.c.s"
	cd /home/lea/M1-IMAGINE/S2/MoteurJeux/M1-IMAGINE-MoteurDeJeux-TP3/build/external/glfw-3.1.2/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lea/M1-IMAGINE/S2/MoteurJeux/M1-IMAGINE-MoteurDeJeux-TP3/external/glfw-3.1.2/examples/simple.c -o CMakeFiles/simple.dir/simple.c.s

# Object files for target simple
simple_OBJECTS = \
"CMakeFiles/simple.dir/simple.c.o"

# External object files for target simple
simple_EXTERNAL_OBJECTS =

external/glfw-3.1.2/examples/simple: external/glfw-3.1.2/examples/CMakeFiles/simple.dir/simple.c.o
external/glfw-3.1.2/examples/simple: external/glfw-3.1.2/examples/CMakeFiles/simple.dir/build.make
external/glfw-3.1.2/examples/simple: external/glfw-3.1.2/src/libglfw3.a
external/glfw-3.1.2/examples/simple: /usr/lib/x86_64-linux-gnu/librt.a
external/glfw-3.1.2/examples/simple: /usr/lib/x86_64-linux-gnu/libm.so
external/glfw-3.1.2/examples/simple: /usr/lib/x86_64-linux-gnu/libX11.so
external/glfw-3.1.2/examples/simple: /usr/lib/x86_64-linux-gnu/libXrandr.so
external/glfw-3.1.2/examples/simple: /usr/lib/x86_64-linux-gnu/libXinerama.so
external/glfw-3.1.2/examples/simple: /usr/lib/x86_64-linux-gnu/libXi.so
external/glfw-3.1.2/examples/simple: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
external/glfw-3.1.2/examples/simple: /usr/lib/x86_64-linux-gnu/libXcursor.so
external/glfw-3.1.2/examples/simple: /usr/lib/x86_64-linux-gnu/libGL.so
external/glfw-3.1.2/examples/simple: external/glfw-3.1.2/examples/CMakeFiles/simple.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lea/M1-IMAGINE/S2/MoteurJeux/M1-IMAGINE-MoteurDeJeux-TP3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable simple"
	cd /home/lea/M1-IMAGINE/S2/MoteurJeux/M1-IMAGINE-MoteurDeJeux-TP3/build/external/glfw-3.1.2/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/simple.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/glfw-3.1.2/examples/CMakeFiles/simple.dir/build: external/glfw-3.1.2/examples/simple
.PHONY : external/glfw-3.1.2/examples/CMakeFiles/simple.dir/build

external/glfw-3.1.2/examples/CMakeFiles/simple.dir/clean:
	cd /home/lea/M1-IMAGINE/S2/MoteurJeux/M1-IMAGINE-MoteurDeJeux-TP3/build/external/glfw-3.1.2/examples && $(CMAKE_COMMAND) -P CMakeFiles/simple.dir/cmake_clean.cmake
.PHONY : external/glfw-3.1.2/examples/CMakeFiles/simple.dir/clean

external/glfw-3.1.2/examples/CMakeFiles/simple.dir/depend:
	cd /home/lea/M1-IMAGINE/S2/MoteurJeux/M1-IMAGINE-MoteurDeJeux-TP3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lea/M1-IMAGINE/S2/MoteurJeux/M1-IMAGINE-MoteurDeJeux-TP3 /home/lea/M1-IMAGINE/S2/MoteurJeux/M1-IMAGINE-MoteurDeJeux-TP3/external/glfw-3.1.2/examples /home/lea/M1-IMAGINE/S2/MoteurJeux/M1-IMAGINE-MoteurDeJeux-TP3/build /home/lea/M1-IMAGINE/S2/MoteurJeux/M1-IMAGINE-MoteurDeJeux-TP3/build/external/glfw-3.1.2/examples /home/lea/M1-IMAGINE/S2/MoteurJeux/M1-IMAGINE-MoteurDeJeux-TP3/build/external/glfw-3.1.2/examples/CMakeFiles/simple.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/glfw-3.1.2/examples/CMakeFiles/simple.dir/depend

