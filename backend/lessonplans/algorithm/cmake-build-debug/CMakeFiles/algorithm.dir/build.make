# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.14

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\Dawid\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\192.6262.62\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\Dawid\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\192.6262.62\bin\cmake\win\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\LessonplanScheduler\backend\lessonplans\algorithm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\LessonplanScheduler\backend\lessonplans\algorithm\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/algorithm.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/algorithm.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/algorithm.dir/flags.make

CMakeFiles/algorithm.dir/src/LessonplanScheduler.cpp.obj: CMakeFiles/algorithm.dir/flags.make
CMakeFiles/algorithm.dir/src/LessonplanScheduler.cpp.obj: ../src/LessonplanScheduler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\LessonplanScheduler\backend\lessonplans\algorithm\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/algorithm.dir/src/LessonplanScheduler.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\algorithm.dir\src\LessonplanScheduler.cpp.obj -c D:\LessonplanScheduler\backend\lessonplans\algorithm\src\LessonplanScheduler.cpp

CMakeFiles/algorithm.dir/src/LessonplanScheduler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/algorithm.dir/src/LessonplanScheduler.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\LessonplanScheduler\backend\lessonplans\algorithm\src\LessonplanScheduler.cpp > CMakeFiles\algorithm.dir\src\LessonplanScheduler.cpp.i

CMakeFiles/algorithm.dir/src/LessonplanScheduler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/algorithm.dir/src/LessonplanScheduler.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\LessonplanScheduler\backend\lessonplans\algorithm\src\LessonplanScheduler.cpp -o CMakeFiles\algorithm.dir\src\LessonplanScheduler.cpp.s

CMakeFiles/algorithm.dir/src/GenAlgorithm.cpp.obj: CMakeFiles/algorithm.dir/flags.make
CMakeFiles/algorithm.dir/src/GenAlgorithm.cpp.obj: ../src/GenAlgorithm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\LessonplanScheduler\backend\lessonplans\algorithm\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/algorithm.dir/src/GenAlgorithm.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\algorithm.dir\src\GenAlgorithm.cpp.obj -c D:\LessonplanScheduler\backend\lessonplans\algorithm\src\GenAlgorithm.cpp

CMakeFiles/algorithm.dir/src/GenAlgorithm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/algorithm.dir/src/GenAlgorithm.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\LessonplanScheduler\backend\lessonplans\algorithm\src\GenAlgorithm.cpp > CMakeFiles\algorithm.dir\src\GenAlgorithm.cpp.i

CMakeFiles/algorithm.dir/src/GenAlgorithm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/algorithm.dir/src/GenAlgorithm.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\LessonplanScheduler\backend\lessonplans\algorithm\src\GenAlgorithm.cpp -o CMakeFiles\algorithm.dir\src\GenAlgorithm.cpp.s

CMakeFiles/algorithm.dir/src/LessonplanGenAlgorithm.cpp.obj: CMakeFiles/algorithm.dir/flags.make
CMakeFiles/algorithm.dir/src/LessonplanGenAlgorithm.cpp.obj: ../src/LessonplanGenAlgorithm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\LessonplanScheduler\backend\lessonplans\algorithm\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/algorithm.dir/src/LessonplanGenAlgorithm.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\algorithm.dir\src\LessonplanGenAlgorithm.cpp.obj -c D:\LessonplanScheduler\backend\lessonplans\algorithm\src\LessonplanGenAlgorithm.cpp

CMakeFiles/algorithm.dir/src/LessonplanGenAlgorithm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/algorithm.dir/src/LessonplanGenAlgorithm.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\LessonplanScheduler\backend\lessonplans\algorithm\src\LessonplanGenAlgorithm.cpp > CMakeFiles\algorithm.dir\src\LessonplanGenAlgorithm.cpp.i

CMakeFiles/algorithm.dir/src/LessonplanGenAlgorithm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/algorithm.dir/src/LessonplanGenAlgorithm.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\LessonplanScheduler\backend\lessonplans\algorithm\src\LessonplanGenAlgorithm.cpp -o CMakeFiles\algorithm.dir\src\LessonplanGenAlgorithm.cpp.s

# Object files for target algorithm
algorithm_OBJECTS = \
"CMakeFiles/algorithm.dir/src/LessonplanScheduler.cpp.obj" \
"CMakeFiles/algorithm.dir/src/GenAlgorithm.cpp.obj" \
"CMakeFiles/algorithm.dir/src/LessonplanGenAlgorithm.cpp.obj"

# External object files for target algorithm
algorithm_EXTERNAL_OBJECTS =

algorithm.exe: CMakeFiles/algorithm.dir/src/LessonplanScheduler.cpp.obj
algorithm.exe: CMakeFiles/algorithm.dir/src/GenAlgorithm.cpp.obj
algorithm.exe: CMakeFiles/algorithm.dir/src/LessonplanGenAlgorithm.cpp.obj
algorithm.exe: CMakeFiles/algorithm.dir/build.make
algorithm.exe: CMakeFiles/algorithm.dir/linklibs.rsp
algorithm.exe: CMakeFiles/algorithm.dir/objects1.rsp
algorithm.exe: CMakeFiles/algorithm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\LessonplanScheduler\backend\lessonplans\algorithm\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable algorithm.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\algorithm.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/algorithm.dir/build: algorithm.exe

.PHONY : CMakeFiles/algorithm.dir/build

CMakeFiles/algorithm.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\algorithm.dir\cmake_clean.cmake
.PHONY : CMakeFiles/algorithm.dir/clean

CMakeFiles/algorithm.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\LessonplanScheduler\backend\lessonplans\algorithm D:\LessonplanScheduler\backend\lessonplans\algorithm D:\LessonplanScheduler\backend\lessonplans\algorithm\cmake-build-debug D:\LessonplanScheduler\backend\lessonplans\algorithm\cmake-build-debug D:\LessonplanScheduler\backend\lessonplans\algorithm\cmake-build-debug\CMakeFiles\algorithm.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/algorithm.dir/depend

