# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Denis\MAI\CP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Denis\MAI\CP\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/cp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cp.dir/flags.make

CMakeFiles/cp.dir/src/logger/logger.cpp.obj: CMakeFiles/cp.dir/flags.make
CMakeFiles/cp.dir/src/logger/logger.cpp.obj: CMakeFiles/cp.dir/includes_CXX.rsp
CMakeFiles/cp.dir/src/logger/logger.cpp.obj: ../src/logger/logger.cpp
CMakeFiles/cp.dir/src/logger/logger.cpp.obj: CMakeFiles/cp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Denis\MAI\CP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cp.dir/src/logger/logger.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cp.dir/src/logger/logger.cpp.obj -MF CMakeFiles\cp.dir\src\logger\logger.cpp.obj.d -o CMakeFiles\cp.dir\src\logger\logger.cpp.obj -c C:\Users\Denis\MAI\CP\src\logger\logger.cpp

CMakeFiles/cp.dir/src/logger/logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cp.dir/src/logger/logger.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Denis\MAI\CP\src\logger\logger.cpp > CMakeFiles\cp.dir\src\logger\logger.cpp.i

CMakeFiles/cp.dir/src/logger/logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cp.dir/src/logger/logger.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Denis\MAI\CP\src\logger\logger.cpp -o CMakeFiles\cp.dir\src\logger\logger.cpp.s

CMakeFiles/cp.dir/src/logger/logger_holder.cpp.obj: CMakeFiles/cp.dir/flags.make
CMakeFiles/cp.dir/src/logger/logger_holder.cpp.obj: CMakeFiles/cp.dir/includes_CXX.rsp
CMakeFiles/cp.dir/src/logger/logger_holder.cpp.obj: ../src/logger/logger_holder.cpp
CMakeFiles/cp.dir/src/logger/logger_holder.cpp.obj: CMakeFiles/cp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Denis\MAI\CP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/cp.dir/src/logger/logger_holder.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cp.dir/src/logger/logger_holder.cpp.obj -MF CMakeFiles\cp.dir\src\logger\logger_holder.cpp.obj.d -o CMakeFiles\cp.dir\src\logger\logger_holder.cpp.obj -c C:\Users\Denis\MAI\CP\src\logger\logger_holder.cpp

CMakeFiles/cp.dir/src/logger/logger_holder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cp.dir/src/logger/logger_holder.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Denis\MAI\CP\src\logger\logger_holder.cpp > CMakeFiles\cp.dir\src\logger\logger_holder.cpp.i

CMakeFiles/cp.dir/src/logger/logger_holder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cp.dir/src/logger/logger_holder.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Denis\MAI\CP\src\logger\logger_holder.cpp -o CMakeFiles\cp.dir\src\logger\logger_holder.cpp.s

CMakeFiles/cp.dir/src/logger/logger_builder.cpp.obj: CMakeFiles/cp.dir/flags.make
CMakeFiles/cp.dir/src/logger/logger_builder.cpp.obj: CMakeFiles/cp.dir/includes_CXX.rsp
CMakeFiles/cp.dir/src/logger/logger_builder.cpp.obj: ../src/logger/logger_builder.cpp
CMakeFiles/cp.dir/src/logger/logger_builder.cpp.obj: CMakeFiles/cp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Denis\MAI\CP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/cp.dir/src/logger/logger_builder.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cp.dir/src/logger/logger_builder.cpp.obj -MF CMakeFiles\cp.dir\src\logger\logger_builder.cpp.obj.d -o CMakeFiles\cp.dir\src\logger\logger_builder.cpp.obj -c C:\Users\Denis\MAI\CP\src\logger\logger_builder.cpp

CMakeFiles/cp.dir/src/logger/logger_builder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cp.dir/src/logger/logger_builder.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Denis\MAI\CP\src\logger\logger_builder.cpp > CMakeFiles\cp.dir\src\logger\logger_builder.cpp.i

CMakeFiles/cp.dir/src/logger/logger_builder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cp.dir/src/logger/logger_builder.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Denis\MAI\CP\src\logger\logger_builder.cpp -o CMakeFiles\cp.dir\src\logger\logger_builder.cpp.s

CMakeFiles/cp.dir/src/logger/logger_builder_concrete.cpp.obj: CMakeFiles/cp.dir/flags.make
CMakeFiles/cp.dir/src/logger/logger_builder_concrete.cpp.obj: CMakeFiles/cp.dir/includes_CXX.rsp
CMakeFiles/cp.dir/src/logger/logger_builder_concrete.cpp.obj: ../src/logger/logger_builder_concrete.cpp
CMakeFiles/cp.dir/src/logger/logger_builder_concrete.cpp.obj: CMakeFiles/cp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Denis\MAI\CP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/cp.dir/src/logger/logger_builder_concrete.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cp.dir/src/logger/logger_builder_concrete.cpp.obj -MF CMakeFiles\cp.dir\src\logger\logger_builder_concrete.cpp.obj.d -o CMakeFiles\cp.dir\src\logger\logger_builder_concrete.cpp.obj -c C:\Users\Denis\MAI\CP\src\logger\logger_builder_concrete.cpp

CMakeFiles/cp.dir/src/logger/logger_builder_concrete.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cp.dir/src/logger/logger_builder_concrete.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Denis\MAI\CP\src\logger\logger_builder_concrete.cpp > CMakeFiles\cp.dir\src\logger\logger_builder_concrete.cpp.i

CMakeFiles/cp.dir/src/logger/logger_builder_concrete.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cp.dir/src/logger/logger_builder_concrete.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Denis\MAI\CP\src\logger\logger_builder_concrete.cpp -o CMakeFiles\cp.dir\src\logger\logger_builder_concrete.cpp.s

CMakeFiles/cp.dir/src/logger/logger_concrete.cpp.obj: CMakeFiles/cp.dir/flags.make
CMakeFiles/cp.dir/src/logger/logger_concrete.cpp.obj: CMakeFiles/cp.dir/includes_CXX.rsp
CMakeFiles/cp.dir/src/logger/logger_concrete.cpp.obj: ../src/logger/logger_concrete.cpp
CMakeFiles/cp.dir/src/logger/logger_concrete.cpp.obj: CMakeFiles/cp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Denis\MAI\CP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/cp.dir/src/logger/logger_concrete.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cp.dir/src/logger/logger_concrete.cpp.obj -MF CMakeFiles\cp.dir\src\logger\logger_concrete.cpp.obj.d -o CMakeFiles\cp.dir\src\logger\logger_concrete.cpp.obj -c C:\Users\Denis\MAI\CP\src\logger\logger_concrete.cpp

CMakeFiles/cp.dir/src/logger/logger_concrete.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cp.dir/src/logger/logger_concrete.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Denis\MAI\CP\src\logger\logger_concrete.cpp > CMakeFiles\cp.dir\src\logger\logger_concrete.cpp.i

CMakeFiles/cp.dir/src/logger/logger_concrete.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cp.dir/src/logger/logger_concrete.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Denis\MAI\CP\src\logger\logger_concrete.cpp -o CMakeFiles\cp.dir\src\logger\logger_concrete.cpp.s

CMakeFiles/cp.dir/src/memory/memory_holder.cpp.obj: CMakeFiles/cp.dir/flags.make
CMakeFiles/cp.dir/src/memory/memory_holder.cpp.obj: CMakeFiles/cp.dir/includes_CXX.rsp
CMakeFiles/cp.dir/src/memory/memory_holder.cpp.obj: ../src/memory/memory_holder.cpp
CMakeFiles/cp.dir/src/memory/memory_holder.cpp.obj: CMakeFiles/cp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Denis\MAI\CP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/cp.dir/src/memory/memory_holder.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cp.dir/src/memory/memory_holder.cpp.obj -MF CMakeFiles\cp.dir\src\memory\memory_holder.cpp.obj.d -o CMakeFiles\cp.dir\src\memory\memory_holder.cpp.obj -c C:\Users\Denis\MAI\CP\src\memory\memory_holder.cpp

CMakeFiles/cp.dir/src/memory/memory_holder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cp.dir/src/memory/memory_holder.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Denis\MAI\CP\src\memory\memory_holder.cpp > CMakeFiles\cp.dir\src\memory\memory_holder.cpp.i

CMakeFiles/cp.dir/src/memory/memory_holder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cp.dir/src/memory/memory_holder.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Denis\MAI\CP\src\memory\memory_holder.cpp -o CMakeFiles\cp.dir\src\memory\memory_holder.cpp.s

CMakeFiles/cp.dir/src/memory/memory.cpp.obj: CMakeFiles/cp.dir/flags.make
CMakeFiles/cp.dir/src/memory/memory.cpp.obj: CMakeFiles/cp.dir/includes_CXX.rsp
CMakeFiles/cp.dir/src/memory/memory.cpp.obj: ../src/memory/memory.cpp
CMakeFiles/cp.dir/src/memory/memory.cpp.obj: CMakeFiles/cp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Denis\MAI\CP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/cp.dir/src/memory/memory.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cp.dir/src/memory/memory.cpp.obj -MF CMakeFiles\cp.dir\src\memory\memory.cpp.obj.d -o CMakeFiles\cp.dir\src\memory\memory.cpp.obj -c C:\Users\Denis\MAI\CP\src\memory\memory.cpp

CMakeFiles/cp.dir/src/memory/memory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cp.dir/src/memory/memory.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Denis\MAI\CP\src\memory\memory.cpp > CMakeFiles\cp.dir\src\memory\memory.cpp.i

CMakeFiles/cp.dir/src/memory/memory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cp.dir/src/memory/memory.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Denis\MAI\CP\src\memory\memory.cpp -o CMakeFiles\cp.dir\src\memory\memory.cpp.s

CMakeFiles/cp.dir/src/allocators/list_memory.cpp.obj: CMakeFiles/cp.dir/flags.make
CMakeFiles/cp.dir/src/allocators/list_memory.cpp.obj: CMakeFiles/cp.dir/includes_CXX.rsp
CMakeFiles/cp.dir/src/allocators/list_memory.cpp.obj: ../src/allocators/list_memory.cpp
CMakeFiles/cp.dir/src/allocators/list_memory.cpp.obj: CMakeFiles/cp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Denis\MAI\CP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/cp.dir/src/allocators/list_memory.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cp.dir/src/allocators/list_memory.cpp.obj -MF CMakeFiles\cp.dir\src\allocators\list_memory.cpp.obj.d -o CMakeFiles\cp.dir\src\allocators\list_memory.cpp.obj -c C:\Users\Denis\MAI\CP\src\allocators\list_memory.cpp

CMakeFiles/cp.dir/src/allocators/list_memory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cp.dir/src/allocators/list_memory.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Denis\MAI\CP\src\allocators\list_memory.cpp > CMakeFiles\cp.dir\src\allocators\list_memory.cpp.i

CMakeFiles/cp.dir/src/allocators/list_memory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cp.dir/src/allocators/list_memory.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Denis\MAI\CP\src\allocators\list_memory.cpp -o CMakeFiles\cp.dir\src\allocators\list_memory.cpp.s

CMakeFiles/cp.dir/src/allocators/boundary_tags_allocator.cpp.obj: CMakeFiles/cp.dir/flags.make
CMakeFiles/cp.dir/src/allocators/boundary_tags_allocator.cpp.obj: CMakeFiles/cp.dir/includes_CXX.rsp
CMakeFiles/cp.dir/src/allocators/boundary_tags_allocator.cpp.obj: ../src/allocators/boundary_tags_allocator.cpp
CMakeFiles/cp.dir/src/allocators/boundary_tags_allocator.cpp.obj: CMakeFiles/cp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Denis\MAI\CP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/cp.dir/src/allocators/boundary_tags_allocator.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cp.dir/src/allocators/boundary_tags_allocator.cpp.obj -MF CMakeFiles\cp.dir\src\allocators\boundary_tags_allocator.cpp.obj.d -o CMakeFiles\cp.dir\src\allocators\boundary_tags_allocator.cpp.obj -c C:\Users\Denis\MAI\CP\src\allocators\boundary_tags_allocator.cpp

CMakeFiles/cp.dir/src/allocators/boundary_tags_allocator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cp.dir/src/allocators/boundary_tags_allocator.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Denis\MAI\CP\src\allocators\boundary_tags_allocator.cpp > CMakeFiles\cp.dir\src\allocators\boundary_tags_allocator.cpp.i

CMakeFiles/cp.dir/src/allocators/boundary_tags_allocator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cp.dir/src/allocators/boundary_tags_allocator.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Denis\MAI\CP\src\allocators\boundary_tags_allocator.cpp -o CMakeFiles\cp.dir\src\allocators\boundary_tags_allocator.cpp.s

CMakeFiles/cp.dir/src/allocators/memory_buddy_system.cpp.obj: CMakeFiles/cp.dir/flags.make
CMakeFiles/cp.dir/src/allocators/memory_buddy_system.cpp.obj: CMakeFiles/cp.dir/includes_CXX.rsp
CMakeFiles/cp.dir/src/allocators/memory_buddy_system.cpp.obj: ../src/allocators/memory_buddy_system.cpp
CMakeFiles/cp.dir/src/allocators/memory_buddy_system.cpp.obj: CMakeFiles/cp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Denis\MAI\CP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/cp.dir/src/allocators/memory_buddy_system.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cp.dir/src/allocators/memory_buddy_system.cpp.obj -MF CMakeFiles\cp.dir\src\allocators\memory_buddy_system.cpp.obj.d -o CMakeFiles\cp.dir\src\allocators\memory_buddy_system.cpp.obj -c C:\Users\Denis\MAI\CP\src\allocators\memory_buddy_system.cpp

CMakeFiles/cp.dir/src/allocators/memory_buddy_system.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cp.dir/src/allocators/memory_buddy_system.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Denis\MAI\CP\src\allocators\memory_buddy_system.cpp > CMakeFiles\cp.dir\src\allocators\memory_buddy_system.cpp.i

CMakeFiles/cp.dir/src/allocators/memory_buddy_system.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cp.dir/src/allocators/memory_buddy_system.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Denis\MAI\CP\src\allocators\memory_buddy_system.cpp -o CMakeFiles\cp.dir\src\allocators\memory_buddy_system.cpp.s

CMakeFiles/cp.dir/src/main.cpp.obj: CMakeFiles/cp.dir/flags.make
CMakeFiles/cp.dir/src/main.cpp.obj: CMakeFiles/cp.dir/includes_CXX.rsp
CMakeFiles/cp.dir/src/main.cpp.obj: ../src/main.cpp
CMakeFiles/cp.dir/src/main.cpp.obj: CMakeFiles/cp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Denis\MAI\CP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/cp.dir/src/main.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cp.dir/src/main.cpp.obj -MF CMakeFiles\cp.dir\src\main.cpp.obj.d -o CMakeFiles\cp.dir\src\main.cpp.obj -c C:\Users\Denis\MAI\CP\src\main.cpp

CMakeFiles/cp.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cp.dir/src/main.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Denis\MAI\CP\src\main.cpp > CMakeFiles\cp.dir\src\main.cpp.i

CMakeFiles/cp.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cp.dir/src/main.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Denis\MAI\CP\src\main.cpp -o CMakeFiles\cp.dir\src\main.cpp.s

# Object files for target cp
cp_OBJECTS = \
"CMakeFiles/cp.dir/src/logger/logger.cpp.obj" \
"CMakeFiles/cp.dir/src/logger/logger_holder.cpp.obj" \
"CMakeFiles/cp.dir/src/logger/logger_builder.cpp.obj" \
"CMakeFiles/cp.dir/src/logger/logger_builder_concrete.cpp.obj" \
"CMakeFiles/cp.dir/src/logger/logger_concrete.cpp.obj" \
"CMakeFiles/cp.dir/src/memory/memory_holder.cpp.obj" \
"CMakeFiles/cp.dir/src/memory/memory.cpp.obj" \
"CMakeFiles/cp.dir/src/allocators/list_memory.cpp.obj" \
"CMakeFiles/cp.dir/src/allocators/boundary_tags_allocator.cpp.obj" \
"CMakeFiles/cp.dir/src/allocators/memory_buddy_system.cpp.obj" \
"CMakeFiles/cp.dir/src/main.cpp.obj"

# External object files for target cp
cp_EXTERNAL_OBJECTS =

cp.exe: CMakeFiles/cp.dir/src/logger/logger.cpp.obj
cp.exe: CMakeFiles/cp.dir/src/logger/logger_holder.cpp.obj
cp.exe: CMakeFiles/cp.dir/src/logger/logger_builder.cpp.obj
cp.exe: CMakeFiles/cp.dir/src/logger/logger_builder_concrete.cpp.obj
cp.exe: CMakeFiles/cp.dir/src/logger/logger_concrete.cpp.obj
cp.exe: CMakeFiles/cp.dir/src/memory/memory_holder.cpp.obj
cp.exe: CMakeFiles/cp.dir/src/memory/memory.cpp.obj
cp.exe: CMakeFiles/cp.dir/src/allocators/list_memory.cpp.obj
cp.exe: CMakeFiles/cp.dir/src/allocators/boundary_tags_allocator.cpp.obj
cp.exe: CMakeFiles/cp.dir/src/allocators/memory_buddy_system.cpp.obj
cp.exe: CMakeFiles/cp.dir/src/main.cpp.obj
cp.exe: CMakeFiles/cp.dir/build.make
cp.exe: CMakeFiles/cp.dir/linklibs.rsp
cp.exe: CMakeFiles/cp.dir/objects1.rsp
cp.exe: CMakeFiles/cp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Denis\MAI\CP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable cp.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\cp.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cp.dir/build: cp.exe
.PHONY : CMakeFiles/cp.dir/build

CMakeFiles/cp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\cp.dir\cmake_clean.cmake
.PHONY : CMakeFiles/cp.dir/clean

CMakeFiles/cp.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Denis\MAI\CP C:\Users\Denis\MAI\CP C:\Users\Denis\MAI\CP\cmake-build-debug C:\Users\Denis\MAI\CP\cmake-build-debug C:\Users\Denis\MAI\CP\cmake-build-debug\CMakeFiles\cp.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cp.dir/depend

