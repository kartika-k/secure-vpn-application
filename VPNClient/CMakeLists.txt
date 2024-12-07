cmake_minimum_required(VERSION 3.10)
project(VPNClient)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Source files
set(SOURCE_FILES
    src/Encryption.cpp
    src/Tunnel.cpp
    src/VPNClient.cpp
    src/main_client.cpp
)

# Create executable
add_executable(VPNClient ${SOURCE_FILES})

# Link PocoCrypto and other necessary libraries
find_package(Poco REQUIRED Crypto Net)
target_link_libraries(VPNClient Poco::Crypto Poco::Net)
