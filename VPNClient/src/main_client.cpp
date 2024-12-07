#include "include/VPNClient.h" //Includes the class denition for managing the VPN client.
#include <iostream>    // Used for console input/output operations.

int main() {
    try {
        VPNClient client; //Creating VPNClient Object
        
        std::cout << "Connecting to VPN Server..." << std::endl;
        if (client.connect("localhost", 8443)) {
            std::cout << "Connected successfully!" << std::endl;
            
            // Example data transmission - Send Encrypted Data
            //Converts a string message (`"Hello, VPN Server!"`) to a `std::vector<uint8_t>` for encryption and secure transmission.
            std::string message = "Hello, VPN Server!";
            std::vector<uint8_t> data(message.begin(), message.end());
            
            if (client.sendSecureData(data)) {
                std::cout << "Data sent successfully!" << std::endl;
                //Waits for a response from the VPN server.
                auto response = client.receiveSecureData();
                if (!response.empty()) {
                    std::string responseStr(response.begin(), response.end());
                    std::cout << "Received: " << responseStr << std::endl;
                }
            }
            //terminates the connection to the VPN server after the operation is complete
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
