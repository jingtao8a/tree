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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yuxintao/tree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yuxintao/tree/build

# Include any dependencies generated for this target.
include CMakeFiles/create_btree.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/create_btree.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/create_btree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/create_btree.dir/flags.make

CMakeFiles/create_btree.dir/src/create_btree.cpp.o: CMakeFiles/create_btree.dir/flags.make
CMakeFiles/create_btree.dir/src/create_btree.cpp.o: /home/yuxintao/tree/src/create_btree.cpp
CMakeFiles/create_btree.dir/src/create_btree.cpp.o: CMakeFiles/create_btree.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yuxintao/tree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/create_btree.dir/src/create_btree.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/create_btree.dir/src/create_btree.cpp.o -MF CMakeFiles/create_btree.dir/src/create_btree.cpp.o.d -o CMakeFiles/create_btree.dir/src/create_btree.cpp.o -c /home/yuxintao/tree/src/create_btree.cpp

CMakeFiles/create_btree.dir/src/create_btree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/create_btree.dir/src/create_btree.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yuxintao/tree/src/create_btree.cpp > CMakeFiles/create_btree.dir/src/create_btree.cpp.i

CMakeFiles/create_btree.dir/src/create_btree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/create_btree.dir/src/create_btree.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yuxintao/tree/src/create_btree.cpp -o CMakeFiles/create_btree.dir/src/create_btree.cpp.s

# Object files for target create_btree
create_btree_OBJECTS = \
"CMakeFiles/create_btree.dir/src/create_btree.cpp.o"

# External object files for target create_btree
create_btree_EXTERNAL_OBJECTS =

/home/yuxintao/tree/bin/create_btree: CMakeFiles/create_btree.dir/src/create_btree.cpp.o
/home/yuxintao/tree/bin/create_btree: CMakeFiles/create_btree.dir/build.make
/home/yuxintao/tree/bin/create_btree: CMakeFiles/create_btree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yuxintao/tree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/yuxintao/tree/bin/create_btree"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/create_btree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/create_btree.dir/build: /home/yuxintao/tree/bin/create_btree
.PHONY : CMakeFiles/create_btree.dir/build

CMakeFiles/create_btree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/create_btree.dir/cmake_clean.cmake
.PHONY : CMakeFiles/create_btree.dir/clean

CMakeFiles/create_btree.dir/depend:
	cd /home/yuxintao/tree/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yuxintao/tree /home/yuxintao/tree /home/yuxintao/tree/build /home/yuxintao/tree/build /home/yuxintao/tree/build/CMakeFiles/create_btree.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/create_btree.dir/depend

