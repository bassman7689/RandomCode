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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.10.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.10.3/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ser/code/games/opengl_tut

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ser/code/games/opengl_tut

# Include any dependencies generated for this target.
include CMakeFiles/OpenGLTut.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/OpenGLTut.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OpenGLTut.dir/flags.make

CMakeFiles/OpenGLTut.dir/main.cpp.o: CMakeFiles/OpenGLTut.dir/flags.make
CMakeFiles/OpenGLTut.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ser/code/games/opengl_tut/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/OpenGLTut.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OpenGLTut.dir/main.cpp.o -c /Users/ser/code/games/opengl_tut/main.cpp

CMakeFiles/OpenGLTut.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenGLTut.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ser/code/games/opengl_tut/main.cpp > CMakeFiles/OpenGLTut.dir/main.cpp.i

CMakeFiles/OpenGLTut.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenGLTut.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ser/code/games/opengl_tut/main.cpp -o CMakeFiles/OpenGLTut.dir/main.cpp.s

CMakeFiles/OpenGLTut.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/OpenGLTut.dir/main.cpp.o.requires

CMakeFiles/OpenGLTut.dir/main.cpp.o.provides: CMakeFiles/OpenGLTut.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/OpenGLTut.dir/build.make CMakeFiles/OpenGLTut.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/OpenGLTut.dir/main.cpp.o.provides

CMakeFiles/OpenGLTut.dir/main.cpp.o.provides.build: CMakeFiles/OpenGLTut.dir/main.cpp.o


# Object files for target OpenGLTut
OpenGLTut_OBJECTS = \
"CMakeFiles/OpenGLTut.dir/main.cpp.o"

# External object files for target OpenGLTut
OpenGLTut_EXTERNAL_OBJECTS =

OpenGLTut: CMakeFiles/OpenGLTut.dir/main.cpp.o
OpenGLTut: CMakeFiles/OpenGLTut.dir/build.make
OpenGLTut: /usr/local/lib/libGLEW.dylib
OpenGLTut: /usr/local/lib/libglfw.3.2.dylib
OpenGLTut: /opt/local/lib/libSOIL.dylib
OpenGLTut: CMakeFiles/OpenGLTut.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/ser/code/games/opengl_tut/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable OpenGLTut"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OpenGLTut.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OpenGLTut.dir/build: OpenGLTut

.PHONY : CMakeFiles/OpenGLTut.dir/build

CMakeFiles/OpenGLTut.dir/requires: CMakeFiles/OpenGLTut.dir/main.cpp.o.requires

.PHONY : CMakeFiles/OpenGLTut.dir/requires

CMakeFiles/OpenGLTut.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OpenGLTut.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OpenGLTut.dir/clean

CMakeFiles/OpenGLTut.dir/depend:
	cd /Users/ser/code/games/opengl_tut && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ser/code/games/opengl_tut /Users/ser/code/games/opengl_tut /Users/ser/code/games/opengl_tut /Users/ser/code/games/opengl_tut /Users/ser/code/games/opengl_tut/CMakeFiles/OpenGLTut.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OpenGLTut.dir/depend

