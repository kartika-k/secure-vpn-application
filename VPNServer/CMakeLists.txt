cmake_minimum_required(VERSION 3.10)
project(VPNServer)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Source files
set(SOURCE_FILES
    src/Encryption.cpp
    src/Tunnel.cpp
    src/VPNServer.cpp
    src/main_server.cpp
)

# Create executable
add_executable(VPNServer ${SOURCE_FILES})

# Link PocoCrypto and other necessary libraries
find_package(Poco REQUIRED Crypto Net)
target_link_libraries(VPNServer Poco::Crypto Poco::Net)

