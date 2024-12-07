# cmake_minimum_required(VERSION 3.28)
# project(VPNServer)

# # Correct the path to your source files
# set(SERVER_SOURCES
#     src/Encryption.cpp
#     src/main_server.cpp
#     src/Tunnel.cpp
#     src/VPNServer.cpp
# )

# set(SERVER_HEADERS
#     include/Encryption.h
#     include/Tunnel.h
#     include/VPNServer.h
# )

# # Add executable for the server
# add_executable(VPNServer ${SERVER_SOURCES} ${SERVER_HEADERS})

# # Include the header files for the server project
# target_include_directories(VPNServer PUBLIC include)

# # Find and link Poco libraries
# find_package(Poco REQUIRED Net Util)

# # Link Poco libraries to the project
# target_link_libraries(VPNServer PRIVATE Poco::Net Poco::Util)


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
