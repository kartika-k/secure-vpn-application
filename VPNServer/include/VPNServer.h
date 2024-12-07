#pragma once
#include "Tunnel.h"
#include "Encryption.h"
#include <Poco/Net/SecureServerSocket.h>
#include <string>
#include <thread>
#include <atomic>

class VPNServer {
public:
    VPNServer(int port);
    ~VPNServer();

    bool start();
    void stop();

private:
    void handleClient(Poco::Net::StreamSocket clientSocket);
    bool authenticateClient(Poco::Net::StreamSocket& clientSocket);

    int port_;
    Poco::Net::SecureServerSocket* serverSocket_;
    std::atomic<bool> running_;
    std::string encryptionKey_;
};