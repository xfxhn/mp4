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
include src/visualSampleEntry/CMakeFiles/visualSampleEntry.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/visualSampleEntry/CMakeFiles/visualSampleEntry.dir/compiler_depend.make

# Include the progress variables for this target.
include src/visualSampleEntry/CMakeFiles/visualSampleEntry.dir/progress.make

# Include the compile flags for this target's objects.
include src/visualSampleEntry/CMakeFiles/visualSampleEntry.dir/flags.make

src/visualSampleEntry/CMakeFiles/visualSampleEntry.dir/visualSampleEntry.cpp.obj: src/visualSampleEntry/CMakeFiles/visualSampleEntry.dir/flags.make
src/visualSampleEntry/CMakeFiles/visualSampleEntry.dir/visualSampleEntry.cpp.obj: src/visualSampleEntry/CMakeFiles/visualSampleEntry.dir/includes_CXX.rsp
src/visualSampleEntry/CMakeFiles/visualSampleEntry.dir/visualSampleEntry.cpp.obj: ../src/visualSampleEntry/visualSampleEntry.cpp
src/visualSampleEntry/CMakeFiles/visualSampleEntry.dir/visualSampleEntry.cpp.obj: src/visualSampleEntry/CMakeFiles/visualSampleEntry.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:/Users/Administrator/Desktop/MP4decoder/mp4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/visualSampleEntry/CMakeFiles/visualSampleEntry.dir/visualSampleEntry.cpp.obj"
	cd C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/visualSampleEntry && "D:/Program Files (x86)/c++/bin/c++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/visualSampleEntry/CMakeFiles/visualSampleEntry.dir/visualSampleEntry.cpp.obj -MF CMakeFiles/visualSampleEntry.dir/visualSampleEntry.cpp.obj.d -o CMakeFiles/visualSampleEntry.dir/visualSampleEntry.cpp.obj -c C:/Users/Administrator/Desktop/MP4decoder/mp4/src/visualSampleEntry/visualSampleEntry.cpp

src/visualSampleEntry/CMakeFiles/visualSampleEntry.dir/visualSampleEntry.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/visualSampleEntry.dir/visualSampleEntry.cpp.i"
	cd C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/visualSampleEntry && "D:/Program Files (x86)/c++/bin/c++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:/Users/Administrator/Desktop/MP4decoder/mp4/src/visualSampleEntry/visualSampleEntry.cpp > CMakeFiles/visualSampleEntry.dir/visualSampleEntry.cpp.i

src/visualSampleEntry/CMakeFiles/visualSampleEntry.dir/visualSampleEntry.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/visualSampleEntry.dir/visualSampleEntry.cpp.s"
	cd C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/visualSampleEntry && "D:/Program Files (x86)/c++/bin/c++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:/Users/Administrator/Desktop/MP4decoder/mp4/src/visualSampleEntry/visualSampleEntry.cpp -o CMakeFiles/visualSampleEntry.dir/visualSampleEntry.cpp.s

visualSampleEntry: src/visualSampleEntry/CMakeFiles/visualSampleEntry.dir/visualSampleEntry.cpp.obj
visualSampleEntry: src/visualSampleEntry/CMakeFiles/visualSampleEntry.dir/build.make
.PHONY : visualSampleEntry

# Rule to build all files generated by this target.
src/visualSampleEntry/CMakeFiles/visualSampleEntry.dir/build: visualSampleEntry
.PHONY : src/visualSampleEntry/CMakeFiles/visualSampleEntry.dir/build

src/visualSampleEntry/CMakeFiles/visualSampleEntry.dir/clean:
	cd C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/visualSampleEntry && $(CMAKE_COMMAND) -P CMakeFiles/visualSampleEntry.dir/cmake_clean.cmake
.PHONY : src/visualSampleEntry/CMakeFiles/visualSampleEntry.dir/clean

src/visualSampleEntry/CMakeFiles/visualSampleEntry.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" C:/Users/Administrator/Desktop/MP4decoder/mp4 C:/Users/Administrator/Desktop/MP4decoder/mp4/src/visualSampleEntry C:/Users/Administrator/Desktop/MP4decoder/mp4/build C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/visualSampleEntry C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/visualSampleEntry/CMakeFiles/visualSampleEntry.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/visualSampleEntry/CMakeFiles/visualSampleEntry.dir/depend
