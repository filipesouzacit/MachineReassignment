# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/filipe/CLionProjects/MachineReassignment

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/filipe/CLionProjects/MachineReassignment/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/steel_mill.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/steel_mill.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/steel_mill.dir/flags.make

CMakeFiles/steel_mill.dir/chuffed/examples/steel_mill.cpp.o: CMakeFiles/steel_mill.dir/flags.make
CMakeFiles/steel_mill.dir/chuffed/examples/steel_mill.cpp.o: ../chuffed/examples/steel_mill.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/filipe/CLionProjects/MachineReassignment/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/steel_mill.dir/chuffed/examples/steel_mill.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/steel_mill.dir/chuffed/examples/steel_mill.cpp.o -c /Users/filipe/CLionProjects/MachineReassignment/chuffed/examples/steel_mill.cpp

CMakeFiles/steel_mill.dir/chuffed/examples/steel_mill.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/steel_mill.dir/chuffed/examples/steel_mill.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/filipe/CLionProjects/MachineReassignment/chuffed/examples/steel_mill.cpp > CMakeFiles/steel_mill.dir/chuffed/examples/steel_mill.cpp.i

CMakeFiles/steel_mill.dir/chuffed/examples/steel_mill.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/steel_mill.dir/chuffed/examples/steel_mill.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/filipe/CLionProjects/MachineReassignment/chuffed/examples/steel_mill.cpp -o CMakeFiles/steel_mill.dir/chuffed/examples/steel_mill.cpp.s

# Object files for target steel_mill
steel_mill_OBJECTS = \
"CMakeFiles/steel_mill.dir/chuffed/examples/steel_mill.cpp.o"

# External object files for target steel_mill
steel_mill_EXTERNAL_OBJECTS =

steel_mill: CMakeFiles/steel_mill.dir/chuffed/examples/steel_mill.cpp.o
steel_mill: CMakeFiles/steel_mill.dir/build.make
steel_mill: libchuffed_fzn.a
steel_mill: libchuffed.a
steel_mill: CMakeFiles/steel_mill.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/filipe/CLionProjects/MachineReassignment/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable steel_mill"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/steel_mill.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/steel_mill.dir/build: steel_mill

.PHONY : CMakeFiles/steel_mill.dir/build

CMakeFiles/steel_mill.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/steel_mill.dir/cmake_clean.cmake
.PHONY : CMakeFiles/steel_mill.dir/clean

CMakeFiles/steel_mill.dir/depend:
	cd /Users/filipe/CLionProjects/MachineReassignment/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/filipe/CLionProjects/MachineReassignment /Users/filipe/CLionProjects/MachineReassignment /Users/filipe/CLionProjects/MachineReassignment/cmake-build-debug /Users/filipe/CLionProjects/MachineReassignment/cmake-build-debug /Users/filipe/CLionProjects/MachineReassignment/cmake-build-debug/CMakeFiles/steel_mill.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/steel_mill.dir/depend
