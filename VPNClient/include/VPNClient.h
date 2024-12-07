#pragma once
#include "Tunnel.h" //For secure tunneling functionality.
#include "VPNClient.h"    
#include "Encryption.h" //For data encryption and decryption
#include <string> //To handle text data (server address, encryption key).

class VPNClient {
public:
    VPNClient();
    ~VPNClient();

    bool connect(const std::string& serverAddress, int port); //Establishes a secure connection to the server.Returns `true` if successful.
    void disconnect(); //Closes the connection and releases resources.
    bool sendSecureData(const std::vector<uint8_t>& data); //Encrypts and sends data through the secure tunnel. Returns `true` on success.
    std::vector<uint8_t> receiveSecureData(); //Receives encrypted data, decrypts it, and returns the result.

private:
    Tunnel tunnel_; //Manages the secure tunnel for communication.
    std::string encryptionKey_; //Stores the encryption key for secure data transmission.
    bool isConnected_; //Tracks the connection state of the client.
    bool authenticate(); //Handles user authentication before establishing a connection.
};
