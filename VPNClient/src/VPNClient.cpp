#include <Poco/Net/SecureStreamSocket.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/Net/Context.h>
#include <Poco/Net/NetException.h>
#include <Poco/Util/Application.h>
#include <Poco/Thread.h>
#include <iostream>
#include <vector>
#include <string>

class VPNClient {
private:
    Poco::Net::SecureStreamSocket socket;
    std::string serverAddress;
    uint16_t serverPort;
    bool isConnected;
    std::vector<uint8_t> buffer;
    static const size_t BUFFER_SIZE = 4096;

    // SSL Context
    Poco::Net::Context::Ptr getSSLContext() {
        return new Poco::Net::Context(
            Poco::Net::Context::CLIENT_USE,
            "",  // certificatePath
            "",  // privateKeyPath
            "",  // caLocation
            Poco::Net::Context::VERIFY_RELAXED,
            9,   // verificationDepth
            true // loadDefaultCAs
        );
    }

public:
    VPNClient(const std::string& address, uint16_t port) 
        : serverAddress(address)
        , serverPort(port)
        , isConnected(false)
        , buffer(BUFFER_SIZE) {
        
        // Initialize SSL
        Poco::Net::initializeSSL();
    }

    ~VPNClient() {
        disconnect();
        Poco::Net::uninitializeSSL();
    }

    bool connect() {
        try {
            // Create SSL context and socket
            Poco::Net::Context::Ptr context = getSSLContext();
            socket = Poco::Net::SecureStreamSocket(context);
            
            // Connect to server
            Poco::Net::SocketAddress addr(serverAddress, serverPort);
            socket.connect(addr);
            
            // Perform SSL handshake
            socket.completeHandshake();
            
            isConnected = true;
            std::cout << "Successfully connected to VPN server" << std::endl;
            return true;
        }
        catch (Poco::Net::NetException& e) {
            std::cerr << "Connection error: " << e.what() << std::endl;
            isConnected = false;
            return false;
        }
    }

    void disconnect() {
        if (isConnected) {
            try {
                socket.shutdown();
                socket.close();
                isConnected = false;
                std::cout << "Disconnected from VPN server" << std::endl;
            }
            catch (Poco::Exception& e) {
                std::cerr << "Error during disconnect: " << e.what() << std::endl;
            }
        }
    }

    bool sendData(const std::vector<uint8_t>& data) {
        if (!isConnected) {
            std::cerr << "Not connected to server" << std::endl;
            return false;
        }

        try {
            socket.sendBytes(data.data(), data.size());
            return true;
        }
        catch (Poco::Exception& e) {
            std::cerr << "Error sending data: " << e.what() << std::endl;
            return false;
        }
    }

    std::vector<uint8_t> receiveData() {
        if (!isConnected) {
            std::cerr << "Not connected to server" << std::endl;
            return std::vector<uint8_t>();
        }

        try {
            int received = socket.receiveBytes(buffer.data(), BUFFER_SIZE);
            if (received > 0) {
                return std::vector<uint8_t>(buffer.begin(), buffer.begin() + received);
            }
        }
        catch (Poco::Exception& e) {
            std::cerr << "Error receiving data: " << e.what() << std::endl;
        }

        return std::vector<uint8_t>();
    }

    bool isActive() const {
        return isConnected;
    }

    // Implement ping to keep connection alive
    void keepAlive() {
        while (isConnected) {
            try {
                std::vector<uint8_t> pingData = {0x01}; // Simple ping packet
                sendData(pingData);
                Poco::Thread::sleep(30000); // Sleep for 30 seconds
            }
            catch (Poco::Exception& e) {
                std::cerr << "Keep-alive error: " << e.what() << std::endl;
                break;
            }
        }
    }
};
