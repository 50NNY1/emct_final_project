# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.24.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.24.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/sonnyholland/Documents/gs/emct_final_proj

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/sonnyholland/Documents/gs/emct_final_proj/build

# Include any dependencies generated for this target.
include _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_window.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_window.dir/compiler_depend.make

# Include the progress variables for this target.
include _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_window.dir/progress.make

# Include the compile flags for this target's objects.
include _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_window.dir/flags.make

_deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_window.dir/window.cpp.o: _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_window.dir/flags.make
_deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_window.dir/window.cpp.o: _deps/ftxui-src/examples/dom/window.cpp
_deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_window.dir/window.cpp.o: _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_window.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sonnyholland/Documents/gs/emct_final_proj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_window.dir/window.cpp.o"
	cd /Users/sonnyholland/Documents/gs/emct_final_proj/build/_deps/ftxui-build/examples/dom && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_window.dir/window.cpp.o -MF CMakeFiles/ftxui_example_window.dir/window.cpp.o.d -o CMakeFiles/ftxui_example_window.dir/window.cpp.o -c /Users/sonnyholland/Documents/gs/emct_final_proj/build/_deps/ftxui-src/examples/dom/window.cpp

_deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_window.dir/window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ftxui_example_window.dir/window.cpp.i"
	cd /Users/sonnyholland/Documents/gs/emct_final_proj/build/_deps/ftxui-build/examples/dom && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sonnyholland/Documents/gs/emct_final_proj/build/_deps/ftxui-src/examples/dom/window.cpp > CMakeFiles/ftxui_example_window.dir/window.cpp.i

_deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_window.dir/window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ftxui_example_window.dir/window.cpp.s"
	cd /Users/sonnyholland/Documents/gs/emct_final_proj/build/_deps/ftxui-build/examples/dom && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sonnyholland/Documents/gs/emct_final_proj/build/_deps/ftxui-src/examples/dom/window.cpp -o CMakeFiles/ftxui_example_window.dir/window.cpp.s

# Object files for target ftxui_example_window
ftxui_example_window_OBJECTS = \
"CMakeFiles/ftxui_example_window.dir/window.cpp.o"

# External object files for target ftxui_example_window
ftxui_example_window_EXTERNAL_OBJECTS =

_deps/ftxui-build/examples/dom/ftxui_example_window: _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_window.dir/window.cpp.o
_deps/ftxui-build/examples/dom/ftxui_example_window: _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_window.dir/build.make
_deps/ftxui-build/examples/dom/ftxui_example_window: _deps/ftxui-build/libftxui-dom.a
_deps/ftxui-build/examples/dom/ftxui_example_window: _deps/ftxui-build/libftxui-screen.a
_deps/ftxui-build/examples/dom/ftxui_example_window: _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_window.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/sonnyholland/Documents/gs/emct_final_proj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ftxui_example_window"
	cd /Users/sonnyholland/Documents/gs/emct_final_proj/build/_deps/ftxui-build/examples/dom && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ftxui_example_window.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
_deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_window.dir/build: _deps/ftxui-build/examples/dom/ftxui_example_window
.PHONY : _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_window.dir/build

_deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_window.dir/clean:
	cd /Users/sonnyholland/Documents/gs/emct_final_proj/build/_deps/ftxui-build/examples/dom && $(CMAKE_COMMAND) -P CMakeFiles/ftxui_example_window.dir/cmake_clean.cmake
.PHONY : _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_window.dir/clean

_deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_window.dir/depend:
	cd /Users/sonnyholland/Documents/gs/emct_final_proj/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/sonnyholland/Documents/gs/emct_final_proj /Users/sonnyholland/Documents/gs/emct_final_proj/build/_deps/ftxui-src/examples/dom /Users/sonnyholland/Documents/gs/emct_final_proj/build /Users/sonnyholland/Documents/gs/emct_final_proj/build/_deps/ftxui-build/examples/dom /Users/sonnyholland/Documents/gs/emct_final_proj/build/_deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_window.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_window.dir/depend

