# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/berke/PAES-QT/onnx_pose

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/berke/PAES-QT/onnx_pose/build

# Include any dependencies generated for this target.
include src/CMakeFiles/src.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/src.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/src.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/src.dir/flags.make

src/CMakeFiles/src.dir/MPPose.cpp.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/MPPose.cpp.o: /home/berke/PAES-QT/onnx_pose/src/MPPose.cpp
src/CMakeFiles/src.dir/MPPose.cpp.o: src/CMakeFiles/src.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/berke/PAES-QT/onnx_pose/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/src.dir/MPPose.cpp.o"
	cd /home/berke/PAES-QT/onnx_pose/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/src.dir/MPPose.cpp.o -MF CMakeFiles/src.dir/MPPose.cpp.o.d -o CMakeFiles/src.dir/MPPose.cpp.o -c /home/berke/PAES-QT/onnx_pose/src/MPPose.cpp

src/CMakeFiles/src.dir/MPPose.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/src.dir/MPPose.cpp.i"
	cd /home/berke/PAES-QT/onnx_pose/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/berke/PAES-QT/onnx_pose/src/MPPose.cpp > CMakeFiles/src.dir/MPPose.cpp.i

src/CMakeFiles/src.dir/MPPose.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/src.dir/MPPose.cpp.s"
	cd /home/berke/PAES-QT/onnx_pose/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/berke/PAES-QT/onnx_pose/src/MPPose.cpp -o CMakeFiles/src.dir/MPPose.cpp.s

src/CMakeFiles/src.dir/MPPersonDet.cpp.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/MPPersonDet.cpp.o: /home/berke/PAES-QT/onnx_pose/src/MPPersonDet.cpp
src/CMakeFiles/src.dir/MPPersonDet.cpp.o: src/CMakeFiles/src.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/berke/PAES-QT/onnx_pose/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/src.dir/MPPersonDet.cpp.o"
	cd /home/berke/PAES-QT/onnx_pose/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/src.dir/MPPersonDet.cpp.o -MF CMakeFiles/src.dir/MPPersonDet.cpp.o.d -o CMakeFiles/src.dir/MPPersonDet.cpp.o -c /home/berke/PAES-QT/onnx_pose/src/MPPersonDet.cpp

src/CMakeFiles/src.dir/MPPersonDet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/src.dir/MPPersonDet.cpp.i"
	cd /home/berke/PAES-QT/onnx_pose/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/berke/PAES-QT/onnx_pose/src/MPPersonDet.cpp > CMakeFiles/src.dir/MPPersonDet.cpp.i

src/CMakeFiles/src.dir/MPPersonDet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/src.dir/MPPersonDet.cpp.s"
	cd /home/berke/PAES-QT/onnx_pose/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/berke/PAES-QT/onnx_pose/src/MPPersonDet.cpp -o CMakeFiles/src.dir/MPPersonDet.cpp.s

src/CMakeFiles/src.dir/processFrame.cpp.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/processFrame.cpp.o: /home/berke/PAES-QT/onnx_pose/src/processFrame.cpp
src/CMakeFiles/src.dir/processFrame.cpp.o: src/CMakeFiles/src.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/berke/PAES-QT/onnx_pose/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/src.dir/processFrame.cpp.o"
	cd /home/berke/PAES-QT/onnx_pose/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/src.dir/processFrame.cpp.o -MF CMakeFiles/src.dir/processFrame.cpp.o.d -o CMakeFiles/src.dir/processFrame.cpp.o -c /home/berke/PAES-QT/onnx_pose/src/processFrame.cpp

src/CMakeFiles/src.dir/processFrame.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/src.dir/processFrame.cpp.i"
	cd /home/berke/PAES-QT/onnx_pose/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/berke/PAES-QT/onnx_pose/src/processFrame.cpp > CMakeFiles/src.dir/processFrame.cpp.i

src/CMakeFiles/src.dir/processFrame.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/src.dir/processFrame.cpp.s"
	cd /home/berke/PAES-QT/onnx_pose/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/berke/PAES-QT/onnx_pose/src/processFrame.cpp -o CMakeFiles/src.dir/processFrame.cpp.s

# Object files for target src
src_OBJECTS = \
"CMakeFiles/src.dir/MPPose.cpp.o" \
"CMakeFiles/src.dir/MPPersonDet.cpp.o" \
"CMakeFiles/src.dir/processFrame.cpp.o"

# External object files for target src
src_EXTERNAL_OBJECTS =

src/libsrc.a: src/CMakeFiles/src.dir/MPPose.cpp.o
src/libsrc.a: src/CMakeFiles/src.dir/MPPersonDet.cpp.o
src/libsrc.a: src/CMakeFiles/src.dir/processFrame.cpp.o
src/libsrc.a: src/CMakeFiles/src.dir/build.make
src/libsrc.a: src/CMakeFiles/src.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/berke/PAES-QT/onnx_pose/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libsrc.a"
	cd /home/berke/PAES-QT/onnx_pose/build/src && $(CMAKE_COMMAND) -P CMakeFiles/src.dir/cmake_clean_target.cmake
	cd /home/berke/PAES-QT/onnx_pose/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/src.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/src.dir/build: src/libsrc.a
.PHONY : src/CMakeFiles/src.dir/build

src/CMakeFiles/src.dir/clean:
	cd /home/berke/PAES-QT/onnx_pose/build/src && $(CMAKE_COMMAND) -P CMakeFiles/src.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/src.dir/clean

src/CMakeFiles/src.dir/depend:
	cd /home/berke/PAES-QT/onnx_pose/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/berke/PAES-QT/onnx_pose /home/berke/PAES-QT/onnx_pose/src /home/berke/PAES-QT/onnx_pose/build /home/berke/PAES-QT/onnx_pose/build/src /home/berke/PAES-QT/onnx_pose/build/src/CMakeFiles/src.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/CMakeFiles/src.dir/depend

