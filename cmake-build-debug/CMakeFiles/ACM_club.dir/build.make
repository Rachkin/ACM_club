# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/vladimir/CLionProjects/ACM_club

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/vladimir/CLionProjects/ACM_club/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ACM_club.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ACM_club.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ACM_club.dir/flags.make

CMakeFiles/ACM_club.dir/main.cpp.o: CMakeFiles/ACM_club.dir/flags.make
CMakeFiles/ACM_club.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/vladimir/CLionProjects/ACM_club/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ACM_club.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ACM_club.dir/main.cpp.o -c /Users/vladimir/CLionProjects/ACM_club/main.cpp

CMakeFiles/ACM_club.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ACM_club.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/vladimir/CLionProjects/ACM_club/main.cpp > CMakeFiles/ACM_club.dir/main.cpp.i

CMakeFiles/ACM_club.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ACM_club.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/vladimir/CLionProjects/ACM_club/main.cpp -o CMakeFiles/ACM_club.dir/main.cpp.s

# Object files for target ACM_club
ACM_club_OBJECTS = \
"CMakeFiles/ACM_club.dir/main.cpp.o"

# External object files for target ACM_club
ACM_club_EXTERNAL_OBJECTS =

ACM_club: CMakeFiles/ACM_club.dir/main.cpp.o
ACM_club: CMakeFiles/ACM_club.dir/build.make
ACM_club: /usr/local/lib/libsfml-audio.dylib
ACM_club: /usr/local/lib/libsfml-graphics.dylib
ACM_club: /usr/local/lib/libsfml-window.dylib
ACM_club: /usr/local/lib/libsfml-system.dylib
ACM_club: /usr/local/lib/libsfml-network.dylib
ACM_club: CMakeFiles/ACM_club.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/vladimir/CLionProjects/ACM_club/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ACM_club"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ACM_club.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ACM_club.dir/build: ACM_club

.PHONY : CMakeFiles/ACM_club.dir/build

CMakeFiles/ACM_club.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ACM_club.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ACM_club.dir/clean

CMakeFiles/ACM_club.dir/depend:
	cd /Users/vladimir/CLionProjects/ACM_club/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/vladimir/CLionProjects/ACM_club /Users/vladimir/CLionProjects/ACM_club /Users/vladimir/CLionProjects/ACM_club/cmake-build-debug /Users/vladimir/CLionProjects/ACM_club/cmake-build-debug /Users/vladimir/CLionProjects/ACM_club/cmake-build-debug/CMakeFiles/ACM_club.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ACM_club.dir/depend

