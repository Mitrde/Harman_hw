# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "E:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "E:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "E:\Users\mitrd\source\repos\Harman Tasks\cpp_task_01\sum_gorner_program"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "E:\Users\mitrd\source\repos\Harman Tasks\cpp_task_01\build"

# Include any dependencies generated for this target.
include main_program/CMakeFiles/main_program.dir/depend.make

# Include the progress variables for this target.
include main_program/CMakeFiles/main_program.dir/progress.make

# Include the compile flags for this target's objects.
include main_program/CMakeFiles/main_program.dir/flags.make

main_program/CMakeFiles/main_program.dir/main.cpp.obj: main_program/CMakeFiles/main_program.dir/flags.make
main_program/CMakeFiles/main_program.dir/main.cpp.obj: main_program/CMakeFiles/main_program.dir/includes_CXX.rsp
main_program/CMakeFiles/main_program.dir/main.cpp.obj: E:/Users/mitrd/source/repos/Harman\ Tasks/cpp_task_01/sum_gorner_program/main_program/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="E:\Users\mitrd\source\repos\Harman Tasks\cpp_task_01\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object main_program/CMakeFiles/main_program.dir/main.cpp.obj"
	cd /d E:\Users\mitrd\source\repos\HARMAN~1\CPP_TA~1\build\MAIN_P~1 && E:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\main_program.dir\main.cpp.obj -c "E:\Users\mitrd\source\repos\Harman Tasks\cpp_task_01\sum_gorner_program\main_program\main.cpp"

main_program/CMakeFiles/main_program.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main_program.dir/main.cpp.i"
	cd /d E:\Users\mitrd\source\repos\HARMAN~1\CPP_TA~1\build\MAIN_P~1 && E:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "E:\Users\mitrd\source\repos\Harman Tasks\cpp_task_01\sum_gorner_program\main_program\main.cpp" > CMakeFiles\main_program.dir\main.cpp.i

main_program/CMakeFiles/main_program.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main_program.dir/main.cpp.s"
	cd /d E:\Users\mitrd\source\repos\HARMAN~1\CPP_TA~1\build\MAIN_P~1 && E:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "E:\Users\mitrd\source\repos\Harman Tasks\cpp_task_01\sum_gorner_program\main_program\main.cpp" -o CMakeFiles\main_program.dir\main.cpp.s

# Object files for target main_program
main_program_OBJECTS = \
"CMakeFiles/main_program.dir/main.cpp.obj"

# External object files for target main_program
main_program_EXTERNAL_OBJECTS =

main_program/main_program.exe: main_program/CMakeFiles/main_program.dir/main.cpp.obj
main_program/main_program.exe: main_program/CMakeFiles/main_program.dir/build.make
main_program/main_program.exe: rationals_lib/librationals_lib.a
main_program/main_program.exe: main_program/CMakeFiles/main_program.dir/linklibs.rsp
main_program/main_program.exe: main_program/CMakeFiles/main_program.dir/objects1.rsp
main_program/main_program.exe: main_program/CMakeFiles/main_program.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="E:\Users\mitrd\source\repos\Harman Tasks\cpp_task_01\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable main_program.exe"
	cd /d E:\Users\mitrd\source\repos\HARMAN~1\CPP_TA~1\build\MAIN_P~1 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\main_program.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
main_program/CMakeFiles/main_program.dir/build: main_program/main_program.exe

.PHONY : main_program/CMakeFiles/main_program.dir/build

main_program/CMakeFiles/main_program.dir/clean:
	cd /d E:\Users\mitrd\source\repos\HARMAN~1\CPP_TA~1\build\MAIN_P~1 && $(CMAKE_COMMAND) -P CMakeFiles\main_program.dir\cmake_clean.cmake
.PHONY : main_program/CMakeFiles/main_program.dir/clean

main_program/CMakeFiles/main_program.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "E:\Users\mitrd\source\repos\Harman Tasks\cpp_task_01\sum_gorner_program" "E:\Users\mitrd\source\repos\Harman Tasks\cpp_task_01\sum_gorner_program\main_program" "E:\Users\mitrd\source\repos\Harman Tasks\cpp_task_01\build" "E:\Users\mitrd\source\repos\Harman Tasks\cpp_task_01\build\main_program" "E:\Users\mitrd\source\repos\Harman Tasks\cpp_task_01\build\main_program\CMakeFiles\main_program.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : main_program/CMakeFiles/main_program.dir/depend

