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
include src/sampleTableBox/CMakeFiles/sampleTableBox.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/sampleTableBox/CMakeFiles/sampleTableBox.dir/compiler_depend.make

# Include the progress variables for this target.
include src/sampleTableBox/CMakeFiles/sampleTableBox.dir/progress.make

# Include the compile flags for this target's objects.
include src/sampleTableBox/CMakeFiles/sampleTableBox.dir/flags.make

src/sampleTableBox/CMakeFiles/sampleTableBox.dir/sampleTableBox.cpp.obj: src/sampleTableBox/CMakeFiles/sampleTableBox.dir/flags.make
src/sampleTableBox/CMakeFiles/sampleTableBox.dir/sampleTableBox.cpp.obj: src/sampleTableBox/CMakeFiles/sampleTableBox.dir/includes_CXX.rsp
src/sampleTableBox/CMakeFiles/sampleTableBox.dir/sampleTableBox.cpp.obj: ../src/sampleTableBox/sampleTableBox.cpp
src/sampleTableBox/CMakeFiles/sampleTableBox.dir/sampleTableBox.cpp.obj: src/sampleTableBox/CMakeFiles/sampleTableBox.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:/Users/Administrator/Desktop/MP4decoder/mp4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/sampleTableBox/CMakeFiles/sampleTableBox.dir/sampleTableBox.cpp.obj"
	cd C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/sampleTableBox && "D:/Program Files (x86)/c++/bin/c++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/sampleTableBox/CMakeFiles/sampleTableBox.dir/sampleTableBox.cpp.obj -MF CMakeFiles/sampleTableBox.dir/sampleTableBox.cpp.obj.d -o CMakeFiles/sampleTableBox.dir/sampleTableBox.cpp.obj -c C:/Users/Administrator/Desktop/MP4decoder/mp4/src/sampleTableBox/sampleTableBox.cpp

src/sampleTableBox/CMakeFiles/sampleTableBox.dir/sampleTableBox.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sampleTableBox.dir/sampleTableBox.cpp.i"
	cd C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/sampleTableBox && "D:/Program Files (x86)/c++/bin/c++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:/Users/Administrator/Desktop/MP4decoder/mp4/src/sampleTableBox/sampleTableBox.cpp > CMakeFiles/sampleTableBox.dir/sampleTableBox.cpp.i

src/sampleTableBox/CMakeFiles/sampleTableBox.dir/sampleTableBox.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sampleTableBox.dir/sampleTableBox.cpp.s"
	cd C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/sampleTableBox && "D:/Program Files (x86)/c++/bin/c++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:/Users/Administrator/Desktop/MP4decoder/mp4/src/sampleTableBox/sampleTableBox.cpp -o CMakeFiles/sampleTableBox.dir/sampleTableBox.cpp.s

sampleTableBox: src/sampleTableBox/CMakeFiles/sampleTableBox.dir/sampleTableBox.cpp.obj
sampleTableBox: src/sampleTableBox/CMakeFiles/sampleTableBox.dir/build.make
.PHONY : sampleTableBox

# Rule to build all files generated by this target.
src/sampleTableBox/CMakeFiles/sampleTableBox.dir/build: sampleTableBox
.PHONY : src/sampleTableBox/CMakeFiles/sampleTableBox.dir/build

src/sampleTableBox/CMakeFiles/sampleTableBox.dir/clean:
	cd C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/sampleTableBox && $(CMAKE_COMMAND) -P CMakeFiles/sampleTableBox.dir/cmake_clean.cmake
.PHONY : src/sampleTableBox/CMakeFiles/sampleTableBox.dir/clean

src/sampleTableBox/CMakeFiles/sampleTableBox.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" C:/Users/Administrator/Desktop/MP4decoder/mp4 C:/Users/Administrator/Desktop/MP4decoder/mp4/src/sampleTableBox C:/Users/Administrator/Desktop/MP4decoder/mp4/build C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/sampleTableBox C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/sampleTableBox/CMakeFiles/sampleTableBox.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/sampleTableBox/CMakeFiles/sampleTableBox.dir/depend

