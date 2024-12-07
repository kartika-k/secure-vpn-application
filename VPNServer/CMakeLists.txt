# cmake_minimum_required(VERSION 3.10)
# project(VPNServer)

# # Find Poco library
# find_package(Poco REQUIRED Net)

# # Set the include directory for the project
# target_include_directories(VPNServer PRIVATE ${CMAKE_SOURCE_DIR}/include)
# target_include_directories(VPNServer PRIVATE ${Poco_INCLUDE_DIRS})

# # Add source files
# set(SERVER_SOURCES
#     src/Encryption.cpp
#     src/main_server.cpp
#     src/Tunnel.cpp
#     src/VPNServer.cpp
# )

# # Create executable
# add_executable(VPNServer ${SERVER_SOURCES})

# # Link Poco libraries
# target_link_libraries(VPNServer PRIVATE Poco::Net)

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

