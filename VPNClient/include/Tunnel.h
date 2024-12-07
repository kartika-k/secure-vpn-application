#pragma once
#include <string>
#include <vector>
// #include <Poco/Net/SecureStreamSocket.h>
#include <Poco/Net/SecureServerSocket.h>

class Tunnel {
public:
    Tunnel();
    ~Tunnel();

    bool initializeSSL();
    bool createTunnel(const std::string& remoteAddress, int port);
    bool sendData(const std::vector<uint8_t>& data);
    std::vector<uint8_t> receiveData();
    void closeTunnel();

private:
    Poco::Net::SecureStreamSocket* socket_;
    bool isConnected_;
};