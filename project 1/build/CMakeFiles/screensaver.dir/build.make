# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/hiddensharp429/Code/C/C++/Computer Graphics/project 1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/hiddensharp429/Code/C/C++/Computer Graphics/project 1/build"

# Include any dependencies generated for this target.
include CMakeFiles/screensaver.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/screensaver.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/screensaver.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/screensaver.dir/flags.make

CMakeFiles/screensaver.dir/codegen:
.PHONY : CMakeFiles/screensaver.dir/codegen

CMakeFiles/screensaver.dir/screensaver.cpp.o: CMakeFiles/screensaver.dir/flags.make
CMakeFiles/screensaver.dir/screensaver.cpp.o: /Users/hiddensharp429/Code/C/C++/Computer\ Graphics/project\ 1/screensaver.cpp
CMakeFiles/screensaver.dir/screensaver.cpp.o: CMakeFiles/screensaver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/hiddensharp429/Code/C/C++/Computer Graphics/project 1/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/screensaver.dir/screensaver.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/screensaver.dir/screensaver.cpp.o -MF CMakeFiles/screensaver.dir/screensaver.cpp.o.d -o CMakeFiles/screensaver.dir/screensaver.cpp.o -c "/Users/hiddensharp429/Code/C/C++/Computer Graphics/project 1/screensaver.cpp"

CMakeFiles/screensaver.dir/screensaver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/screensaver.dir/screensaver.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/hiddensharp429/Code/C/C++/Computer Graphics/project 1/screensaver.cpp" > CMakeFiles/screensaver.dir/screensaver.cpp.i

CMakeFiles/screensaver.dir/screensaver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/screensaver.dir/screensaver.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/hiddensharp429/Code/C/C++/Computer Graphics/project 1/screensaver.cpp" -o CMakeFiles/screensaver.dir/screensaver.cpp.s

# Object files for target screensaver
screensaver_OBJECTS = \
"CMakeFiles/screensaver.dir/screensaver.cpp.o"

# External object files for target screensaver
screensaver_EXTERNAL_OBJECTS =

screensaver: CMakeFiles/screensaver.dir/screensaver.cpp.o
screensaver: CMakeFiles/screensaver.dir/build.make
screensaver: /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.1.sdk/System/Library/Frameworks/OpenGL.framework
screensaver: /opt/homebrew/lib/libglfw.3.4.dylib
screensaver: CMakeFiles/screensaver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/Users/hiddensharp429/Code/C/C++/Computer Graphics/project 1/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable screensaver"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/screensaver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/screensaver.dir/build: screensaver
.PHONY : CMakeFiles/screensaver.dir/build

CMakeFiles/screensaver.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/screensaver.dir/cmake_clean.cmake
.PHONY : CMakeFiles/screensaver.dir/clean

CMakeFiles/screensaver.dir/depend:
	cd "/Users/hiddensharp429/Code/C/C++/Computer Graphics/project 1/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/hiddensharp429/Code/C/C++/Computer Graphics/project 1" "/Users/hiddensharp429/Code/C/C++/Computer Graphics/project 1" "/Users/hiddensharp429/Code/C/C++/Computer Graphics/project 1/build" "/Users/hiddensharp429/Code/C/C++/Computer Graphics/project 1/build" "/Users/hiddensharp429/Code/C/C++/Computer Graphics/project 1/build/CMakeFiles/screensaver.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/screensaver.dir/depend

