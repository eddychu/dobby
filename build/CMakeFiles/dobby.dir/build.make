# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_SOURCE_DIR = /home/eddy/Projects/dobby

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/eddy/Projects/dobby/build

# Include any dependencies generated for this target.
include CMakeFiles/dobby.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/dobby.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/dobby.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dobby.dir/flags.make

CMakeFiles/dobby.dir/main.cpp.o: CMakeFiles/dobby.dir/flags.make
CMakeFiles/dobby.dir/main.cpp.o: ../main.cpp
CMakeFiles/dobby.dir/main.cpp.o: CMakeFiles/dobby.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eddy/Projects/dobby/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/dobby.dir/main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/dobby.dir/main.cpp.o -MF CMakeFiles/dobby.dir/main.cpp.o.d -o CMakeFiles/dobby.dir/main.cpp.o -c /home/eddy/Projects/dobby/main.cpp

CMakeFiles/dobby.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dobby.dir/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/eddy/Projects/dobby/main.cpp > CMakeFiles/dobby.dir/main.cpp.i

CMakeFiles/dobby.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dobby.dir/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/eddy/Projects/dobby/main.cpp -o CMakeFiles/dobby.dir/main.cpp.s

# Object files for target dobby
dobby_OBJECTS = \
"CMakeFiles/dobby.dir/main.cpp.o"

# External object files for target dobby
dobby_EXTERNAL_OBJECTS =

dobby: CMakeFiles/dobby.dir/main.cpp.o
dobby: CMakeFiles/dobby.dir/build.make
dobby: /usr/lib/libSDL2main.a
dobby: /usr/lib/libSDL2-2.0.so.0.18.2
dobby: CMakeFiles/dobby.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/eddy/Projects/dobby/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable dobby"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dobby.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dobby.dir/build: dobby
.PHONY : CMakeFiles/dobby.dir/build

CMakeFiles/dobby.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dobby.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dobby.dir/clean

CMakeFiles/dobby.dir/depend:
	cd /home/eddy/Projects/dobby/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/eddy/Projects/dobby /home/eddy/Projects/dobby /home/eddy/Projects/dobby/build /home/eddy/Projects/dobby/build /home/eddy/Projects/dobby/build/CMakeFiles/dobby.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dobby.dir/depend
