# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /home/lenovo/Pulpit/IDEBibliotekiIInne/clion-2017.2.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/lenovo/Pulpit/IDEBibliotekiIInne/clion-2017.2.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/lenovo/Pulpit/Materiały/5. semestr/Mikro/cSerializer"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/lenovo/Pulpit/Materiały/5. semestr/Mikro/cSerializer/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/cSerializer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cSerializer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cSerializer.dir/flags.make

CMakeFiles/cSerializer.dir/main.c.o: CMakeFiles/cSerializer.dir/flags.make
CMakeFiles/cSerializer.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/lenovo/Pulpit/Materiały/5. semestr/Mikro/cSerializer/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cSerializer.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cSerializer.dir/main.c.o   -c "/home/lenovo/Pulpit/Materiały/5. semestr/Mikro/cSerializer/main.c"

CMakeFiles/cSerializer.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cSerializer.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/lenovo/Pulpit/Materiały/5. semestr/Mikro/cSerializer/main.c" > CMakeFiles/cSerializer.dir/main.c.i

CMakeFiles/cSerializer.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cSerializer.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/lenovo/Pulpit/Materiały/5. semestr/Mikro/cSerializer/main.c" -o CMakeFiles/cSerializer.dir/main.c.s

CMakeFiles/cSerializer.dir/main.c.o.requires:

.PHONY : CMakeFiles/cSerializer.dir/main.c.o.requires

CMakeFiles/cSerializer.dir/main.c.o.provides: CMakeFiles/cSerializer.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/cSerializer.dir/build.make CMakeFiles/cSerializer.dir/main.c.o.provides.build
.PHONY : CMakeFiles/cSerializer.dir/main.c.o.provides

CMakeFiles/cSerializer.dir/main.c.o.provides.build: CMakeFiles/cSerializer.dir/main.c.o


# Object files for target cSerializer
cSerializer_OBJECTS = \
"CMakeFiles/cSerializer.dir/main.c.o"

# External object files for target cSerializer
cSerializer_EXTERNAL_OBJECTS =

cSerializer: CMakeFiles/cSerializer.dir/main.c.o
cSerializer: CMakeFiles/cSerializer.dir/build.make
cSerializer: CMakeFiles/cSerializer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/lenovo/Pulpit/Materiały/5. semestr/Mikro/cSerializer/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable cSerializer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cSerializer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cSerializer.dir/build: cSerializer

.PHONY : CMakeFiles/cSerializer.dir/build

CMakeFiles/cSerializer.dir/requires: CMakeFiles/cSerializer.dir/main.c.o.requires

.PHONY : CMakeFiles/cSerializer.dir/requires

CMakeFiles/cSerializer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cSerializer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cSerializer.dir/clean

CMakeFiles/cSerializer.dir/depend:
	cd "/home/lenovo/Pulpit/Materiały/5. semestr/Mikro/cSerializer/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/lenovo/Pulpit/Materiały/5. semestr/Mikro/cSerializer" "/home/lenovo/Pulpit/Materiały/5. semestr/Mikro/cSerializer" "/home/lenovo/Pulpit/Materiały/5. semestr/Mikro/cSerializer/cmake-build-debug" "/home/lenovo/Pulpit/Materiały/5. semestr/Mikro/cSerializer/cmake-build-debug" "/home/lenovo/Pulpit/Materiały/5. semestr/Mikro/cSerializer/cmake-build-debug/CMakeFiles/cSerializer.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/cSerializer.dir/depend

