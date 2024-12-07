#pragma once
#include "Tunnel.h"
#include "VPNClient.h"
#include "Encryption.h"
#include <string>

class VPNClient {
public:
    VPNClient();
    ~VPNClient();

    bool connect(const std::string& serverAddress, int port);
    void disconnect();
    bool sendSecureData(const std::vector<uint8_t>& data);
    std::vector<uint8_t> receiveSecureData();

private:
    Tunnel tunnel_;
    std::string encryptionKey_;
    bool isConnected_;
    bool authenticate();
};
