# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.25.1/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.25.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/sonnyholland/Documents/gs/emct_final_proj/dev

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/sonnyholland/Documents/gs/emct_final_proj/dev/build

# Include any dependencies generated for this target.
include CMakeFiles/final_proj.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/final_proj.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/final_proj.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/final_proj.dir/flags.make

CMakeFiles/final_proj.dir/main.cpp.o: CMakeFiles/final_proj.dir/flags.make
CMakeFiles/final_proj.dir/main.cpp.o: /Users/sonnyholland/Documents/gs/emct_final_proj/dev/main.cpp
CMakeFiles/final_proj.dir/main.cpp.o: CMakeFiles/final_proj.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sonnyholland/Documents/gs/emct_final_proj/dev/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/final_proj.dir/main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/final_proj.dir/main.cpp.o -MF CMakeFiles/final_proj.dir/main.cpp.o.d -o CMakeFiles/final_proj.dir/main.cpp.o -c /Users/sonnyholland/Documents/gs/emct_final_proj/dev/main.cpp

CMakeFiles/final_proj.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/final_proj.dir/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sonnyholland/Documents/gs/emct_final_proj/dev/main.cpp > CMakeFiles/final_proj.dir/main.cpp.i

CMakeFiles/final_proj.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/final_proj.dir/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sonnyholland/Documents/gs/emct_final_proj/dev/main.cpp -o CMakeFiles/final_proj.dir/main.cpp.s

# Object files for target final_proj
final_proj_OBJECTS = \
"CMakeFiles/final_proj.dir/main.cpp.o"

# External object files for target final_proj
final_proj_EXTERNAL_OBJECTS =

final_proj: CMakeFiles/final_proj.dir/main.cpp.o
final_proj: CMakeFiles/final_proj.dir/build.make
final_proj: CMakeFiles/final_proj.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/sonnyholland/Documents/gs/emct_final_proj/dev/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable final_proj"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/final_proj.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/final_proj.dir/build: final_proj
.PHONY : CMakeFiles/final_proj.dir/build

CMakeFiles/final_proj.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/final_proj.dir/cmake_clean.cmake
.PHONY : CMakeFiles/final_proj.dir/clean

CMakeFiles/final_proj.dir/depend:
	cd /Users/sonnyholland/Documents/gs/emct_final_proj/dev/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/sonnyholland/Documents/gs/emct_final_proj/dev /Users/sonnyholland/Documents/gs/emct_final_proj/dev /Users/sonnyholland/Documents/gs/emct_final_proj/dev/build /Users/sonnyholland/Documents/gs/emct_final_proj/dev/build /Users/sonnyholland/Documents/gs/emct_final_proj/dev/build/CMakeFiles/final_proj.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/final_proj.dir/depend
