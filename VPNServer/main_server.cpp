#include "VPNServer.h"
#include <iostream>

int main() {
    try {
        VPNServer server(8443);
        
        std::cout << "Starting VPN Server on port 8443..." << std::endl;
        if (server.start()) {
            std::cout << "Server started successfully. Press Enter to stop." << std::endl;
            std::cin.get();
            server.stop();
        }
        else {
            std::cout << "Failed to start server." << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
