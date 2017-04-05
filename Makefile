# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.5.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.5.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/sho/udp-image-streaming

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/sho/udp-image-streaming

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/local/Cellar/cmake/3.5.2/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/local/Cellar/cmake/3.5.2/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/sho/udp-image-streaming/CMakeFiles /Users/sho/udp-image-streaming/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/sho/udp-image-streaming/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named client

# Build rule for target.
client: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 client
.PHONY : client

# fast build rule for target.
client/fast:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/build
.PHONY : client/fast

#=============================================================================
# Target rules for targets named server

# Build rule for target.
server: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 server
.PHONY : server

# fast build rule for target.
server/fast:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/build
.PHONY : server/fast

Client.o: Client.cpp.o

.PHONY : Client.o

# target to build an object file
Client.cpp.o:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/Client.cpp.o
.PHONY : Client.cpp.o

Client.i: Client.cpp.i

.PHONY : Client.i

# target to preprocess a source file
Client.cpp.i:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/Client.cpp.i
.PHONY : Client.cpp.i

Client.s: Client.cpp.s

.PHONY : Client.s

# target to generate assembly for a file
Client.cpp.s:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/Client.cpp.s
.PHONY : Client.cpp.s

PracticalSocket.o: PracticalSocket.cpp.o

.PHONY : PracticalSocket.o

# target to build an object file
PracticalSocket.cpp.o:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/PracticalSocket.cpp.o
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/PracticalSocket.cpp.o
.PHONY : PracticalSocket.cpp.o

PracticalSocket.i: PracticalSocket.cpp.i

.PHONY : PracticalSocket.i

# target to preprocess a source file
PracticalSocket.cpp.i:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/PracticalSocket.cpp.i
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/PracticalSocket.cpp.i
.PHONY : PracticalSocket.cpp.i

PracticalSocket.s: PracticalSocket.cpp.s

.PHONY : PracticalSocket.s

# target to generate assembly for a file
PracticalSocket.cpp.s:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/PracticalSocket.cpp.s
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/PracticalSocket.cpp.s
.PHONY : PracticalSocket.cpp.s

Server.o: Server.cpp.o

.PHONY : Server.o

# target to build an object file
Server.cpp.o:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/Server.cpp.o
.PHONY : Server.cpp.o

Server.i: Server.cpp.i

.PHONY : Server.i

# target to preprocess a source file
Server.cpp.i:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/Server.cpp.i
.PHONY : Server.cpp.i

Server.s: Server.cpp.s

.PHONY : Server.s

# target to generate assembly for a file
Server.cpp.s:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/Server.cpp.s
.PHONY : Server.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... client"
	@echo "... server"
	@echo "... Client.o"
	@echo "... Client.i"
	@echo "... Client.s"
	@echo "... PracticalSocket.o"
	@echo "... PracticalSocket.i"
	@echo "... PracticalSocket.s"
	@echo "... Server.o"
	@echo "... Server.i"
	@echo "... Server.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
