# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.23

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2022.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2022.2.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\dasha\CLionProjects\codeBase_2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\dasha\CLionProjects\codeBase_2\cmake-build-debug-mingw

# Utility rule file for schaken_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/schaken_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/schaken_autogen.dir/progress.make

CMakeFiles/schaken_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=C:\Users\dasha\CLionProjects\codeBase_2\cmake-build-debug-mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC for target schaken"
	"C:\Program Files\JetBrains\CLion 2022.2.4\bin\cmake\win\bin\cmake.exe" -E cmake_autogen C:/Users/dasha/CLionProjects/codeBase_2/cmake-build-debug-mingw/CMakeFiles/schaken_autogen.dir/AutogenInfo.json Debug

schaken_autogen: CMakeFiles/schaken_autogen
schaken_autogen: CMakeFiles/schaken_autogen.dir/build.make
.PHONY : schaken_autogen

# Rule to build all files generated by this target.
CMakeFiles/schaken_autogen.dir/build: schaken_autogen
.PHONY : CMakeFiles/schaken_autogen.dir/build

CMakeFiles/schaken_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\schaken_autogen.dir\cmake_clean.cmake
.PHONY : CMakeFiles/schaken_autogen.dir/clean

CMakeFiles/schaken_autogen.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\dasha\CLionProjects\codeBase_2 C:\Users\dasha\CLionProjects\codeBase_2 C:\Users\dasha\CLionProjects\codeBase_2\cmake-build-debug-mingw C:\Users\dasha\CLionProjects\codeBase_2\cmake-build-debug-mingw C:\Users\dasha\CLionProjects\codeBase_2\cmake-build-debug-mingw\CMakeFiles\schaken_autogen.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/schaken_autogen.dir/depend

