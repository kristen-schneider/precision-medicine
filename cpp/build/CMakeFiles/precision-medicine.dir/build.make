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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sdp/precision-medicine/kristen/array_src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sdp/precision-medicine/kristen/array_src/build

# Include any dependencies generated for this target.
include CMakeFiles/precision-medicine.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/precision-medicine.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/precision-medicine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/precision-medicine.dir/flags.make

CMakeFiles/precision-medicine.dir/src/main.cpp.o: CMakeFiles/precision-medicine.dir/flags.make
CMakeFiles/precision-medicine.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/precision-medicine.dir/src/main.cpp.o: CMakeFiles/precision-medicine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sdp/precision-medicine/kristen/array_src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/precision-medicine.dir/src/main.cpp.o"
	/home/sdp/miniconda3/bin/x86_64-conda-linux-gnu-c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/precision-medicine.dir/src/main.cpp.o -MF CMakeFiles/precision-medicine.dir/src/main.cpp.o.d -o CMakeFiles/precision-medicine.dir/src/main.cpp.o -c /home/sdp/precision-medicine/kristen/array_src/src/main.cpp

CMakeFiles/precision-medicine.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/precision-medicine.dir/src/main.cpp.i"
	/home/sdp/miniconda3/bin/x86_64-conda-linux-gnu-c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sdp/precision-medicine/kristen/array_src/src/main.cpp > CMakeFiles/precision-medicine.dir/src/main.cpp.i

CMakeFiles/precision-medicine.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/precision-medicine.dir/src/main.cpp.s"
	/home/sdp/miniconda3/bin/x86_64-conda-linux-gnu-c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sdp/precision-medicine/kristen/array_src/src/main.cpp -o CMakeFiles/precision-medicine.dir/src/main.cpp.s

# Object files for target precision-medicine
precision__medicine_OBJECTS = \
"CMakeFiles/precision-medicine.dir/src/main.cpp.o"

# External object files for target precision-medicine
precision__medicine_EXTERNAL_OBJECTS =

precision-medicine: CMakeFiles/precision-medicine.dir/src/main.cpp.o
precision-medicine: CMakeFiles/precision-medicine.dir/build.make
precision-medicine: CMakeFiles/precision-medicine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sdp/precision-medicine/kristen/array_src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable precision-medicine"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/precision-medicine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/precision-medicine.dir/build: precision-medicine
.PHONY : CMakeFiles/precision-medicine.dir/build

CMakeFiles/precision-medicine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/precision-medicine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/precision-medicine.dir/clean

CMakeFiles/precision-medicine.dir/depend:
	cd /home/sdp/precision-medicine/kristen/array_src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sdp/precision-medicine/kristen/array_src /home/sdp/precision-medicine/kristen/array_src /home/sdp/precision-medicine/kristen/array_src/build /home/sdp/precision-medicine/kristen/array_src/build /home/sdp/precision-medicine/kristen/array_src/build/CMakeFiles/precision-medicine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/precision-medicine.dir/depend

