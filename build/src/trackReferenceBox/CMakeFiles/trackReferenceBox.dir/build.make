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
include src/trackReferenceBox/CMakeFiles/trackReferenceBox.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/trackReferenceBox/CMakeFiles/trackReferenceBox.dir/compiler_depend.make

# Include the progress variables for this target.
include src/trackReferenceBox/CMakeFiles/trackReferenceBox.dir/progress.make

# Include the compile flags for this target's objects.
include src/trackReferenceBox/CMakeFiles/trackReferenceBox.dir/flags.make

src/trackReferenceBox/CMakeFiles/trackReferenceBox.dir/trackReferenceBox.cpp.obj: src/trackReferenceBox/CMakeFiles/trackReferenceBox.dir/flags.make
src/trackReferenceBox/CMakeFiles/trackReferenceBox.dir/trackReferenceBox.cpp.obj: src/trackReferenceBox/CMakeFiles/trackReferenceBox.dir/includes_CXX.rsp
src/trackReferenceBox/CMakeFiles/trackReferenceBox.dir/trackReferenceBox.cpp.obj: ../src/trackReferenceBox/trackReferenceBox.cpp
src/trackReferenceBox/CMakeFiles/trackReferenceBox.dir/trackReferenceBox.cpp.obj: src/trackReferenceBox/CMakeFiles/trackReferenceBox.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:/Users/Administrator/Desktop/MP4decoder/mp4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/trackReferenceBox/CMakeFiles/trackReferenceBox.dir/trackReferenceBox.cpp.obj"
	cd C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/trackReferenceBox && "D:/Program Files (x86)/c++/bin/c++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/trackReferenceBox/CMakeFiles/trackReferenceBox.dir/trackReferenceBox.cpp.obj -MF CMakeFiles/trackReferenceBox.dir/trackReferenceBox.cpp.obj.d -o CMakeFiles/trackReferenceBox.dir/trackReferenceBox.cpp.obj -c C:/Users/Administrator/Desktop/MP4decoder/mp4/src/trackReferenceBox/trackReferenceBox.cpp

src/trackReferenceBox/CMakeFiles/trackReferenceBox.dir/trackReferenceBox.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/trackReferenceBox.dir/trackReferenceBox.cpp.i"
	cd C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/trackReferenceBox && "D:/Program Files (x86)/c++/bin/c++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:/Users/Administrator/Desktop/MP4decoder/mp4/src/trackReferenceBox/trackReferenceBox.cpp > CMakeFiles/trackReferenceBox.dir/trackReferenceBox.cpp.i

src/trackReferenceBox/CMakeFiles/trackReferenceBox.dir/trackReferenceBox.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/trackReferenceBox.dir/trackReferenceBox.cpp.s"
	cd C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/trackReferenceBox && "D:/Program Files (x86)/c++/bin/c++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:/Users/Administrator/Desktop/MP4decoder/mp4/src/trackReferenceBox/trackReferenceBox.cpp -o CMakeFiles/trackReferenceBox.dir/trackReferenceBox.cpp.s

trackReferenceBox: src/trackReferenceBox/CMakeFiles/trackReferenceBox.dir/trackReferenceBox.cpp.obj
trackReferenceBox: src/trackReferenceBox/CMakeFiles/trackReferenceBox.dir/build.make
.PHONY : trackReferenceBox

# Rule to build all files generated by this target.
src/trackReferenceBox/CMakeFiles/trackReferenceBox.dir/build: trackReferenceBox
.PHONY : src/trackReferenceBox/CMakeFiles/trackReferenceBox.dir/build

src/trackReferenceBox/CMakeFiles/trackReferenceBox.dir/clean:
	cd C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/trackReferenceBox && $(CMAKE_COMMAND) -P CMakeFiles/trackReferenceBox.dir/cmake_clean.cmake
.PHONY : src/trackReferenceBox/CMakeFiles/trackReferenceBox.dir/clean

src/trackReferenceBox/CMakeFiles/trackReferenceBox.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" C:/Users/Administrator/Desktop/MP4decoder/mp4 C:/Users/Administrator/Desktop/MP4decoder/mp4/src/trackReferenceBox C:/Users/Administrator/Desktop/MP4decoder/mp4/build C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/trackReferenceBox C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/trackReferenceBox/CMakeFiles/trackReferenceBox.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/trackReferenceBox/CMakeFiles/trackReferenceBox.dir/depend

