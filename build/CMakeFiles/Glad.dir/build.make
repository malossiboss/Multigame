# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/iliya/workspace/Multigame

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/iliya/workspace/Multigame/build

# Include any dependencies generated for this target.
include CMakeFiles/Glad.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Glad.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Glad.dir/flags.make

CMakeFiles/Glad.dir/libs/glad.c.o: CMakeFiles/Glad.dir/flags.make
CMakeFiles/Glad.dir/libs/glad.c.o: ../libs/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/iliya/workspace/Multigame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Glad.dir/libs/glad.c.o"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Glad.dir/libs/glad.c.o   -c /home/iliya/workspace/Multigame/libs/glad.c

CMakeFiles/Glad.dir/libs/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Glad.dir/libs/glad.c.i"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/iliya/workspace/Multigame/libs/glad.c > CMakeFiles/Glad.dir/libs/glad.c.i

CMakeFiles/Glad.dir/libs/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Glad.dir/libs/glad.c.s"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/iliya/workspace/Multigame/libs/glad.c -o CMakeFiles/Glad.dir/libs/glad.c.s

# Object files for target Glad
Glad_OBJECTS = \
"CMakeFiles/Glad.dir/libs/glad.c.o"

# External object files for target Glad
Glad_EXTERNAL_OBJECTS =

libGlad.a: CMakeFiles/Glad.dir/libs/glad.c.o
libGlad.a: CMakeFiles/Glad.dir/build.make
libGlad.a: CMakeFiles/Glad.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/iliya/workspace/Multigame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libGlad.a"
	$(CMAKE_COMMAND) -P CMakeFiles/Glad.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Glad.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Glad.dir/build: libGlad.a

.PHONY : CMakeFiles/Glad.dir/build

CMakeFiles/Glad.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Glad.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Glad.dir/clean

CMakeFiles/Glad.dir/depend:
	cd /home/iliya/workspace/Multigame/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/iliya/workspace/Multigame /home/iliya/workspace/Multigame /home/iliya/workspace/Multigame/build /home/iliya/workspace/Multigame/build /home/iliya/workspace/Multigame/build/CMakeFiles/Glad.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Glad.dir/depend

