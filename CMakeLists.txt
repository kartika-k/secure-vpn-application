cmake_minimum_required(VERSION 3.28)  # You can adjust the version as necessary.
project(VPNServer)  # Set your project's name here.

# Set the source files for the server
set(SERVER_SOURCES
    src/Encryption.cpp        # Corrected path to Encryption.cpp
    src/main_server.cpp
    src/Tunnel.cpp
    src/VPNServer.cpp
)

# Set the header files for the server
set(SERVER_HEADERS
    include/Encryption.h
    include/Tunnel.h
    include/VPNServer.h
)

# Add executable for the server
add_executable(VPNServer ${SERVER_SOURCES} ${SERVER_HEADERS})

# Include the header files for the server project
target_include_directories(VPNServer PUBLIC include)

# Add Poco include directory for the server
include_directories(/usr/include)  # Corrected for Ubuntu

# Add Poco library directory for the server
link_directories(/usr/lib/x86_64-linux-gnu)  # Corrected for Ubuntu

# Link external libraries like Poco (if needed)
target_link_libraries(VPNServer PRIVATE Poco::Net Poco::Util)
