# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/dorus/Documenti/Serious Business/Esami da dare/2.2 Source Coding/Progetto/LZ_compressor"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/dorus/Documenti/Serious Business/Esami da dare/2.2 Source Coding/Progetto/LZ_compressor/build"

# Include any dependencies generated for this target.
include CMakeFiles/LZ78.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/LZ78.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LZ78.dir/flags.make

CMakeFiles/LZ78.dir/src/LZ_78.cc.o: CMakeFiles/LZ78.dir/flags.make
CMakeFiles/LZ78.dir/src/LZ_78.cc.o: ../src/LZ_78.cc
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/dorus/Documenti/Serious Business/Esami da dare/2.2 Source Coding/Progetto/LZ_compressor/build/CMakeFiles" $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/LZ78.dir/src/LZ_78.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/LZ78.dir/src/LZ_78.cc.o -c "/home/dorus/Documenti/Serious Business/Esami da dare/2.2 Source Coding/Progetto/LZ_compressor/src/LZ_78.cc"

CMakeFiles/LZ78.dir/src/LZ_78.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LZ78.dir/src/LZ_78.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/home/dorus/Documenti/Serious Business/Esami da dare/2.2 Source Coding/Progetto/LZ_compressor/src/LZ_78.cc" > CMakeFiles/LZ78.dir/src/LZ_78.cc.i

CMakeFiles/LZ78.dir/src/LZ_78.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LZ78.dir/src/LZ_78.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/home/dorus/Documenti/Serious Business/Esami da dare/2.2 Source Coding/Progetto/LZ_compressor/src/LZ_78.cc" -o CMakeFiles/LZ78.dir/src/LZ_78.cc.s

CMakeFiles/LZ78.dir/src/LZ_78.cc.o.requires:
.PHONY : CMakeFiles/LZ78.dir/src/LZ_78.cc.o.requires

CMakeFiles/LZ78.dir/src/LZ_78.cc.o.provides: CMakeFiles/LZ78.dir/src/LZ_78.cc.o.requires
	$(MAKE) -f CMakeFiles/LZ78.dir/build.make CMakeFiles/LZ78.dir/src/LZ_78.cc.o.provides.build
.PHONY : CMakeFiles/LZ78.dir/src/LZ_78.cc.o.provides

CMakeFiles/LZ78.dir/src/LZ_78.cc.o.provides.build: CMakeFiles/LZ78.dir/src/LZ_78.cc.o

CMakeFiles/LZ78.dir/src/bit_IO.cc.o: CMakeFiles/LZ78.dir/flags.make
CMakeFiles/LZ78.dir/src/bit_IO.cc.o: ../src/bit_IO.cc
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/dorus/Documenti/Serious Business/Esami da dare/2.2 Source Coding/Progetto/LZ_compressor/build/CMakeFiles" $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/LZ78.dir/src/bit_IO.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/LZ78.dir/src/bit_IO.cc.o -c "/home/dorus/Documenti/Serious Business/Esami da dare/2.2 Source Coding/Progetto/LZ_compressor/src/bit_IO.cc"

CMakeFiles/LZ78.dir/src/bit_IO.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LZ78.dir/src/bit_IO.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/home/dorus/Documenti/Serious Business/Esami da dare/2.2 Source Coding/Progetto/LZ_compressor/src/bit_IO.cc" > CMakeFiles/LZ78.dir/src/bit_IO.cc.i

CMakeFiles/LZ78.dir/src/bit_IO.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LZ78.dir/src/bit_IO.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/home/dorus/Documenti/Serious Business/Esami da dare/2.2 Source Coding/Progetto/LZ_compressor/src/bit_IO.cc" -o CMakeFiles/LZ78.dir/src/bit_IO.cc.s

CMakeFiles/LZ78.dir/src/bit_IO.cc.o.requires:
.PHONY : CMakeFiles/LZ78.dir/src/bit_IO.cc.o.requires

CMakeFiles/LZ78.dir/src/bit_IO.cc.o.provides: CMakeFiles/LZ78.dir/src/bit_IO.cc.o.requires
	$(MAKE) -f CMakeFiles/LZ78.dir/build.make CMakeFiles/LZ78.dir/src/bit_IO.cc.o.provides.build
.PHONY : CMakeFiles/LZ78.dir/src/bit_IO.cc.o.provides

CMakeFiles/LZ78.dir/src/bit_IO.cc.o.provides.build: CMakeFiles/LZ78.dir/src/bit_IO.cc.o

# Object files for target LZ78
LZ78_OBJECTS = \
"CMakeFiles/LZ78.dir/src/LZ_78.cc.o" \
"CMakeFiles/LZ78.dir/src/bit_IO.cc.o"

# External object files for target LZ78
LZ78_EXTERNAL_OBJECTS =

libLZ78.a: CMakeFiles/LZ78.dir/src/LZ_78.cc.o
libLZ78.a: CMakeFiles/LZ78.dir/src/bit_IO.cc.o
libLZ78.a: CMakeFiles/LZ78.dir/build.make
libLZ78.a: CMakeFiles/LZ78.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libLZ78.a"
	$(CMAKE_COMMAND) -P CMakeFiles/LZ78.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LZ78.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LZ78.dir/build: libLZ78.a
.PHONY : CMakeFiles/LZ78.dir/build

CMakeFiles/LZ78.dir/requires: CMakeFiles/LZ78.dir/src/LZ_78.cc.o.requires
CMakeFiles/LZ78.dir/requires: CMakeFiles/LZ78.dir/src/bit_IO.cc.o.requires
.PHONY : CMakeFiles/LZ78.dir/requires

CMakeFiles/LZ78.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LZ78.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LZ78.dir/clean

CMakeFiles/LZ78.dir/depend:
	cd "/home/dorus/Documenti/Serious Business/Esami da dare/2.2 Source Coding/Progetto/LZ_compressor/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/dorus/Documenti/Serious Business/Esami da dare/2.2 Source Coding/Progetto/LZ_compressor" "/home/dorus/Documenti/Serious Business/Esami da dare/2.2 Source Coding/Progetto/LZ_compressor" "/home/dorus/Documenti/Serious Business/Esami da dare/2.2 Source Coding/Progetto/LZ_compressor/build" "/home/dorus/Documenti/Serious Business/Esami da dare/2.2 Source Coding/Progetto/LZ_compressor/build" "/home/dorus/Documenti/Serious Business/Esami da dare/2.2 Source Coding/Progetto/LZ_compressor/build/CMakeFiles/LZ78.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/LZ78.dir/depend
