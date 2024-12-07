#include "VPNClient.h"
#include <iostream>

int main() {
    try {
        VPNClient client;
        
        std::cout << "Connecting to VPN Server..." << std::endl;
        if (client.connect("localhost", 8443)) {
            std::cout << "Connected successfully!" << std::endl;
            
            // Example data transmission
            std::string message = "Hello, VPN Server!";
            std::vector<uint8_t> data(message.begin(), message.end());
            
            if (client.sendSecureData(data)) {
                std::cout << "Data sent successfully!" << std::endl;
                
                auto response = client.receiveSecureData();
                if (!response.empty()) {
                    std::string responseStr(response.begin(), response.end());
                    std::cout << "Received: " << responseStr << std::endl;
                }
            }
            
            client.disconnect();
        }
        else {
            std::cout << "Failed to connect to server." << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Client error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}