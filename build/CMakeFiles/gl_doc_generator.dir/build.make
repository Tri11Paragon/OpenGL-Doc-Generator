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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/brett/Documents/code/c++/gl_doc_generator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/brett/Documents/code/c++/gl_doc_generator/build

# Include any dependencies generated for this target.
include CMakeFiles/gl_doc_generator.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/gl_doc_generator.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/gl_doc_generator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gl_doc_generator.dir/flags.make

CMakeFiles/gl_doc_generator.dir/src/load_file.cpp.o: CMakeFiles/gl_doc_generator.dir/flags.make
CMakeFiles/gl_doc_generator.dir/src/load_file.cpp.o: /home/brett/Documents/code/c++/gl_doc_generator/src/load_file.cpp
CMakeFiles/gl_doc_generator.dir/src/load_file.cpp.o: CMakeFiles/gl_doc_generator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brett/Documents/code/c++/gl_doc_generator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/gl_doc_generator.dir/src/load_file.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/gl_doc_generator.dir/src/load_file.cpp.o -MF CMakeFiles/gl_doc_generator.dir/src/load_file.cpp.o.d -o CMakeFiles/gl_doc_generator.dir/src/load_file.cpp.o -c /home/brett/Documents/code/c++/gl_doc_generator/src/load_file.cpp

CMakeFiles/gl_doc_generator.dir/src/load_file.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gl_doc_generator.dir/src/load_file.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brett/Documents/code/c++/gl_doc_generator/src/load_file.cpp > CMakeFiles/gl_doc_generator.dir/src/load_file.cpp.i

CMakeFiles/gl_doc_generator.dir/src/load_file.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gl_doc_generator.dir/src/load_file.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brett/Documents/code/c++/gl_doc_generator/src/load_file.cpp -o CMakeFiles/gl_doc_generator.dir/src/load_file.cpp.s

CMakeFiles/gl_doc_generator.dir/src/main.cpp.o: CMakeFiles/gl_doc_generator.dir/flags.make
CMakeFiles/gl_doc_generator.dir/src/main.cpp.o: /home/brett/Documents/code/c++/gl_doc_generator/src/main.cpp
CMakeFiles/gl_doc_generator.dir/src/main.cpp.o: CMakeFiles/gl_doc_generator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brett/Documents/code/c++/gl_doc_generator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/gl_doc_generator.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/gl_doc_generator.dir/src/main.cpp.o -MF CMakeFiles/gl_doc_generator.dir/src/main.cpp.o.d -o CMakeFiles/gl_doc_generator.dir/src/main.cpp.o -c /home/brett/Documents/code/c++/gl_doc_generator/src/main.cpp

CMakeFiles/gl_doc_generator.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gl_doc_generator.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/brett/Documents/code/c++/gl_doc_generator/src/main.cpp > CMakeFiles/gl_doc_generator.dir/src/main.cpp.i

CMakeFiles/gl_doc_generator.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gl_doc_generator.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/brett/Documents/code/c++/gl_doc_generator/src/main.cpp -o CMakeFiles/gl_doc_generator.dir/src/main.cpp.s

# Object files for target gl_doc_generator
gl_doc_generator_OBJECTS = \
"CMakeFiles/gl_doc_generator.dir/src/load_file.cpp.o" \
"CMakeFiles/gl_doc_generator.dir/src/main.cpp.o"

# External object files for target gl_doc_generator
gl_doc_generator_EXTERNAL_OBJECTS =

gl_doc_generator: CMakeFiles/gl_doc_generator.dir/src/load_file.cpp.o
gl_doc_generator: CMakeFiles/gl_doc_generator.dir/src/main.cpp.o
gl_doc_generator: CMakeFiles/gl_doc_generator.dir/build.make
gl_doc_generator: libraries/BLT/libBLT.a
gl_doc_generator: /usr/lib/x86_64-linux-gnu/libz.so
gl_doc_generator: CMakeFiles/gl_doc_generator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/brett/Documents/code/c++/gl_doc_generator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable gl_doc_generator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gl_doc_generator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gl_doc_generator.dir/build: gl_doc_generator
.PHONY : CMakeFiles/gl_doc_generator.dir/build

CMakeFiles/gl_doc_generator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gl_doc_generator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gl_doc_generator.dir/clean

CMakeFiles/gl_doc_generator.dir/depend:
	cd /home/brett/Documents/code/c++/gl_doc_generator/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/brett/Documents/code/c++/gl_doc_generator /home/brett/Documents/code/c++/gl_doc_generator /home/brett/Documents/code/c++/gl_doc_generator/build /home/brett/Documents/code/c++/gl_doc_generator/build /home/brett/Documents/code/c++/gl_doc_generator/build/CMakeFiles/gl_doc_generator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gl_doc_generator.dir/depend

