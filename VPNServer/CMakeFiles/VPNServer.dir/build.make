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
CMAKE_SOURCE_DIR = /mnt/c/Users/karti/OneDrive/Desktop/VPN_Application/secure-vpn-application/VPNServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/karti/OneDrive/Desktop/VPN_Application/secure-vpn-application/VPNServer

# Include any dependencies generated for this target.
include CMakeFiles/VPNServer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/VPNServer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/VPNServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/VPNServer.dir/flags.make

CMakeFiles/VPNServer.dir/src/Encryption.cpp.o: CMakeFiles/VPNServer.dir/flags.make
CMakeFiles/VPNServer.dir/src/Encryption.cpp.o: src/Encryption.cpp
CMakeFiles/VPNServer.dir/src/Encryption.cpp.o: CMakeFiles/VPNServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Users/karti/OneDrive/Desktop/VPN_Application/secure-vpn-application/VPNServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/VPNServer.dir/src/Encryption.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/VPNServer.dir/src/Encryption.cpp.o -MF CMakeFiles/VPNServer.dir/src/Encryption.cpp.o.d -o CMakeFiles/VPNServer.dir/src/Encryption.cpp.o -c /mnt/c/Users/karti/OneDrive/Desktop/VPN_Application/secure-vpn-application/VPNServer/src/Encryption.cpp

CMakeFiles/VPNServer.dir/src/Encryption.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/VPNServer.dir/src/Encryption.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/karti/OneDrive/Desktop/VPN_Application/secure-vpn-application/VPNServer/src/Encryption.cpp > CMakeFiles/VPNServer.dir/src/Encryption.cpp.i

CMakeFiles/VPNServer.dir/src/Encryption.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/VPNServer.dir/src/Encryption.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/karti/OneDrive/Desktop/VPN_Application/secure-vpn-application/VPNServer/src/Encryption.cpp -o CMakeFiles/VPNServer.dir/src/Encryption.cpp.s

CMakeFiles/VPNServer.dir/src/main_server.cpp.o: CMakeFiles/VPNServer.dir/flags.make
CMakeFiles/VPNServer.dir/src/main_server.cpp.o: src/main_server.cpp
CMakeFiles/VPNServer.dir/src/main_server.cpp.o: CMakeFiles/VPNServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Users/karti/OneDrive/Desktop/VPN_Application/secure-vpn-application/VPNServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/VPNServer.dir/src/main_server.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/VPNServer.dir/src/main_server.cpp.o -MF CMakeFiles/VPNServer.dir/src/main_server.cpp.o.d -o CMakeFiles/VPNServer.dir/src/main_server.cpp.o -c /mnt/c/Users/karti/OneDrive/Desktop/VPN_Application/secure-vpn-application/VPNServer/src/main_server.cpp

CMakeFiles/VPNServer.dir/src/main_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/VPNServer.dir/src/main_server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/karti/OneDrive/Desktop/VPN_Application/secure-vpn-application/VPNServer/src/main_server.cpp > CMakeFiles/VPNServer.dir/src/main_server.cpp.i

CMakeFiles/VPNServer.dir/src/main_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/VPNServer.dir/src/main_server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/karti/OneDrive/Desktop/VPN_Application/secure-vpn-application/VPNServer/src/main_server.cpp -o CMakeFiles/VPNServer.dir/src/main_server.cpp.s

CMakeFiles/VPNServer.dir/src/Tunnel.cpp.o: CMakeFiles/VPNServer.dir/flags.make
CMakeFiles/VPNServer.dir/src/Tunnel.cpp.o: src/Tunnel.cpp
CMakeFiles/VPNServer.dir/src/Tunnel.cpp.o: CMakeFiles/VPNServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Users/karti/OneDrive/Desktop/VPN_Application/secure-vpn-application/VPNServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/VPNServer.dir/src/Tunnel.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/VPNServer.dir/src/Tunnel.cpp.o -MF CMakeFiles/VPNServer.dir/src/Tunnel.cpp.o.d -o CMakeFiles/VPNServer.dir/src/Tunnel.cpp.o -c /mnt/c/Users/karti/OneDrive/Desktop/VPN_Application/secure-vpn-application/VPNServer/src/Tunnel.cpp

CMakeFiles/VPNServer.dir/src/Tunnel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/VPNServer.dir/src/Tunnel.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/karti/OneDrive/Desktop/VPN_Application/secure-vpn-application/VPNServer/src/Tunnel.cpp > CMakeFiles/VPNServer.dir/src/Tunnel.cpp.i

CMakeFiles/VPNServer.dir/src/Tunnel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/VPNServer.dir/src/Tunnel.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/karti/OneDrive/Desktop/VPN_Application/secure-vpn-application/VPNServer/src/Tunnel.cpp -o CMakeFiles/VPNServer.dir/src/Tunnel.cpp.s

CMakeFiles/VPNServer.dir/src/VPNServer.cpp.o: CMakeFiles/VPNServer.dir/flags.make
CMakeFiles/VPNServer.dir/src/VPNServer.cpp.o: src/VPNServer.cpp
CMakeFiles/VPNServer.dir/src/VPNServer.cpp.o: CMakeFiles/VPNServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Users/karti/OneDrive/Desktop/VPN_Application/secure-vpn-application/VPNServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/VPNServer.dir/src/VPNServer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/VPNServer.dir/src/VPNServer.cpp.o -MF CMakeFiles/VPNServer.dir/src/VPNServer.cpp.o.d -o CMakeFiles/VPNServer.dir/src/VPNServer.cpp.o -c /mnt/c/Users/karti/OneDrive/Desktop/VPN_Application/secure-vpn-application/VPNServer/src/VPNServer.cpp

CMakeFiles/VPNServer.dir/src/VPNServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/VPNServer.dir/src/VPNServer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/karti/OneDrive/Desktop/VPN_Application/secure-vpn-application/VPNServer/src/VPNServer.cpp > CMakeFiles/VPNServer.dir/src/VPNServer.cpp.i

CMakeFiles/VPNServer.dir/src/VPNServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/VPNServer.dir/src/VPNServer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/karti/OneDrive/Desktop/VPN_Application/secure-vpn-application/VPNServer/src/VPNServer.cpp -o CMakeFiles/VPNServer.dir/src/VPNServer.cpp.s

# Object files for target VPNServer
VPNServer_OBJECTS = \
"CMakeFiles/VPNServer.dir/src/Encryption.cpp.o" \
"CMakeFiles/VPNServer.dir/src/main_server.cpp.o" \
"CMakeFiles/VPNServer.dir/src/Tunnel.cpp.o" \
"CMakeFiles/VPNServer.dir/src/VPNServer.cpp.o"

# External object files for target VPNServer
VPNServer_EXTERNAL_OBJECTS =

VPNServer: CMakeFiles/VPNServer.dir/src/Encryption.cpp.o
VPNServer: CMakeFiles/VPNServer.dir/src/main_server.cpp.o
VPNServer: CMakeFiles/VPNServer.dir/src/Tunnel.cpp.o
VPNServer: CMakeFiles/VPNServer.dir/src/VPNServer.cpp.o
VPNServer: CMakeFiles/VPNServer.dir/build.make
VPNServer: CMakeFiles/VPNServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/mnt/c/Users/karti/OneDrive/Desktop/VPN_Application/secure-vpn-application/VPNServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable VPNServer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/VPNServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/VPNServer.dir/build: VPNServer
.PHONY : CMakeFiles/VPNServer.dir/build

CMakeFiles/VPNServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/VPNServer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/VPNServer.dir/clean

CMakeFiles/VPNServer.dir/depend:
	cd /mnt/c/Users/karti/OneDrive/Desktop/VPN_Application/secure-vpn-application/VPNServer && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/karti/OneDrive/Desktop/VPN_Application/secure-vpn-application/VPNServer /mnt/c/Users/karti/OneDrive/Desktop/VPN_Application/secure-vpn-application/VPNServer /mnt/c/Users/karti/OneDrive/Desktop/VPN_Application/secure-vpn-application/VPNServer /mnt/c/Users/karti/OneDrive/Desktop/VPN_Application/secure-vpn-application/VPNServer /mnt/c/Users/karti/OneDrive/Desktop/VPN_Application/secure-vpn-application/VPNServer/CMakeFiles/VPNServer.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/VPNServer.dir/depend
