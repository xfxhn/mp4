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
CMAKE_COMMAND = D:/softwares/cmake/bin/cmake.exe

# The command to remove a file.
RM = D:/softwares/cmake/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:/Users/Administrator/Desktop/MP4decoder/mp4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:/Users/Administrator/Desktop/MP4decoder/mp4/build

# Include any dependencies generated for this target.
include src/box/CMakeFiles/box.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/box/CMakeFiles/box.dir/compiler_depend.make

# Include the progress variables for this target.
include src/box/CMakeFiles/box.dir/progress.make

# Include the compile flags for this target's objects.
include src/box/CMakeFiles/box.dir/flags.make

src/box/CMakeFiles/box.dir/box.cpp.obj: src/box/CMakeFiles/box.dir/flags.make
src/box/CMakeFiles/box.dir/box.cpp.obj: src/box/CMakeFiles/box.dir/includes_CXX.rsp
src/box/CMakeFiles/box.dir/box.cpp.obj: ../src/box/box.cpp
src/box/CMakeFiles/box.dir/box.cpp.obj: src/box/CMakeFiles/box.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:/Users/Administrator/Desktop/MP4decoder/mp4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/box/CMakeFiles/box.dir/box.cpp.obj"
	cd C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/box && "D:/Program Files (x86)/c++/bin/c++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/box/CMakeFiles/box.dir/box.cpp.obj -MF CMakeFiles/box.dir/box.cpp.obj.d -o CMakeFiles/box.dir/box.cpp.obj -c C:/Users/Administrator/Desktop/MP4decoder/mp4/src/box/box.cpp

src/box/CMakeFiles/box.dir/box.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/box.dir/box.cpp.i"
	cd C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/box && "D:/Program Files (x86)/c++/bin/c++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:/Users/Administrator/Desktop/MP4decoder/mp4/src/box/box.cpp > CMakeFiles/box.dir/box.cpp.i

src/box/CMakeFiles/box.dir/box.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/box.dir/box.cpp.s"
	cd C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/box && "D:/Program Files (x86)/c++/bin/c++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:/Users/Administrator/Desktop/MP4decoder/mp4/src/box/box.cpp -o CMakeFiles/box.dir/box.cpp.s

box: src/box/CMakeFiles/box.dir/box.cpp.obj
box: src/box/CMakeFiles/box.dir/build.make
.PHONY : box

# Rule to build all files generated by this target.
src/box/CMakeFiles/box.dir/build: box
.PHONY : src/box/CMakeFiles/box.dir/build

src/box/CMakeFiles/box.dir/clean:
	cd C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/box && $(CMAKE_COMMAND) -P CMakeFiles/box.dir/cmake_clean.cmake
.PHONY : src/box/CMakeFiles/box.dir/clean

src/box/CMakeFiles/box.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" C:/Users/Administrator/Desktop/MP4decoder/mp4 C:/Users/Administrator/Desktop/MP4decoder/mp4/src/box C:/Users/Administrator/Desktop/MP4decoder/mp4/build C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/box C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/box/CMakeFiles/box.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/box/CMakeFiles/box.dir/depend
