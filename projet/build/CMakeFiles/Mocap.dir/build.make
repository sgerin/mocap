# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/moi/M2/mocap/projet

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/moi/M2/mocap/projet/build

# Include any dependencies generated for this target.
include CMakeFiles/Mocap.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Mocap.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Mocap.dir/flags.make

CMakeFiles/Mocap.dir/src/scene.o: CMakeFiles/Mocap.dir/flags.make
CMakeFiles/Mocap.dir/src/scene.o: ../src/scene.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/moi/M2/mocap/projet/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Mocap.dir/src/scene.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Mocap.dir/src/scene.o -c /home/moi/M2/mocap/projet/src/scene.cpp

CMakeFiles/Mocap.dir/src/scene.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Mocap.dir/src/scene.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/moi/M2/mocap/projet/src/scene.cpp > CMakeFiles/Mocap.dir/src/scene.i

CMakeFiles/Mocap.dir/src/scene.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Mocap.dir/src/scene.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/moi/M2/mocap/projet/src/scene.cpp -o CMakeFiles/Mocap.dir/src/scene.s

CMakeFiles/Mocap.dir/src/scene.o.requires:
.PHONY : CMakeFiles/Mocap.dir/src/scene.o.requires

CMakeFiles/Mocap.dir/src/scene.o.provides: CMakeFiles/Mocap.dir/src/scene.o.requires
	$(MAKE) -f CMakeFiles/Mocap.dir/build.make CMakeFiles/Mocap.dir/src/scene.o.provides.build
.PHONY : CMakeFiles/Mocap.dir/src/scene.o.provides

CMakeFiles/Mocap.dir/src/scene.o.provides.build: CMakeFiles/Mocap.dir/src/scene.o

CMakeFiles/Mocap.dir/src/skel.o: CMakeFiles/Mocap.dir/flags.make
CMakeFiles/Mocap.dir/src/skel.o: ../src/skel.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/moi/M2/mocap/projet/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Mocap.dir/src/skel.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Mocap.dir/src/skel.o -c /home/moi/M2/mocap/projet/src/skel.cpp

CMakeFiles/Mocap.dir/src/skel.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Mocap.dir/src/skel.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/moi/M2/mocap/projet/src/skel.cpp > CMakeFiles/Mocap.dir/src/skel.i

CMakeFiles/Mocap.dir/src/skel.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Mocap.dir/src/skel.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/moi/M2/mocap/projet/src/skel.cpp -o CMakeFiles/Mocap.dir/src/skel.s

CMakeFiles/Mocap.dir/src/skel.o.requires:
.PHONY : CMakeFiles/Mocap.dir/src/skel.o.requires

CMakeFiles/Mocap.dir/src/skel.o.provides: CMakeFiles/Mocap.dir/src/skel.o.requires
	$(MAKE) -f CMakeFiles/Mocap.dir/build.make CMakeFiles/Mocap.dir/src/skel.o.provides.build
.PHONY : CMakeFiles/Mocap.dir/src/skel.o.provides

CMakeFiles/Mocap.dir/src/skel.o.provides.build: CMakeFiles/Mocap.dir/src/skel.o

CMakeFiles/Mocap.dir/src/main.o: CMakeFiles/Mocap.dir/flags.make
CMakeFiles/Mocap.dir/src/main.o: ../src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/moi/M2/mocap/projet/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Mocap.dir/src/main.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Mocap.dir/src/main.o -c /home/moi/M2/mocap/projet/src/main.cpp

CMakeFiles/Mocap.dir/src/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Mocap.dir/src/main.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/moi/M2/mocap/projet/src/main.cpp > CMakeFiles/Mocap.dir/src/main.i

CMakeFiles/Mocap.dir/src/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Mocap.dir/src/main.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/moi/M2/mocap/projet/src/main.cpp -o CMakeFiles/Mocap.dir/src/main.s

CMakeFiles/Mocap.dir/src/main.o.requires:
.PHONY : CMakeFiles/Mocap.dir/src/main.o.requires

CMakeFiles/Mocap.dir/src/main.o.provides: CMakeFiles/Mocap.dir/src/main.o.requires
	$(MAKE) -f CMakeFiles/Mocap.dir/build.make CMakeFiles/Mocap.dir/src/main.o.provides.build
.PHONY : CMakeFiles/Mocap.dir/src/main.o.provides

CMakeFiles/Mocap.dir/src/main.o.provides.build: CMakeFiles/Mocap.dir/src/main.o

# Object files for target Mocap
Mocap_OBJECTS = \
"CMakeFiles/Mocap.dir/src/scene.o" \
"CMakeFiles/Mocap.dir/src/skel.o" \
"CMakeFiles/Mocap.dir/src/main.o"

# External object files for target Mocap
Mocap_EXTERNAL_OBJECTS =

Mocap_d: CMakeFiles/Mocap.dir/src/scene.o
Mocap_d: CMakeFiles/Mocap.dir/src/skel.o
Mocap_d: CMakeFiles/Mocap.dir/src/main.o
Mocap_d: CMakeFiles/Mocap.dir/build.make
Mocap_d: /usr/lib/libOpenNI.so
Mocap_d: /usr/lib/x86_64-linux-gnu/libGLU.so
Mocap_d: /usr/lib/x86_64-linux-gnu/libGL.so
Mocap_d: /usr/lib/x86_64-linux-gnu/libSM.so
Mocap_d: /usr/lib/x86_64-linux-gnu/libICE.so
Mocap_d: /usr/lib/x86_64-linux-gnu/libX11.so
Mocap_d: /usr/lib/x86_64-linux-gnu/libXext.so
Mocap_d: /usr/lib/x86_64-linux-gnu/libglut.so
Mocap_d: /usr/lib/x86_64-linux-gnu/libXmu.so
Mocap_d: /usr/lib/x86_64-linux-gnu/libXi.so
Mocap_d: CMakeFiles/Mocap.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable Mocap_d"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Mocap.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Mocap.dir/build: Mocap_d
.PHONY : CMakeFiles/Mocap.dir/build

CMakeFiles/Mocap.dir/requires: CMakeFiles/Mocap.dir/src/scene.o.requires
CMakeFiles/Mocap.dir/requires: CMakeFiles/Mocap.dir/src/skel.o.requires
CMakeFiles/Mocap.dir/requires: CMakeFiles/Mocap.dir/src/main.o.requires
.PHONY : CMakeFiles/Mocap.dir/requires

CMakeFiles/Mocap.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Mocap.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Mocap.dir/clean

CMakeFiles/Mocap.dir/depend:
	cd /home/moi/M2/mocap/projet/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/moi/M2/mocap/projet /home/moi/M2/mocap/projet /home/moi/M2/mocap/projet/build /home/moi/M2/mocap/projet/build /home/moi/M2/mocap/projet/build/CMakeFiles/Mocap.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Mocap.dir/depend
