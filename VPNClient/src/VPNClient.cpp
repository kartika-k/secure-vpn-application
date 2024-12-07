#include <Poco/Net/SecureStreamSocket.h> //Handles encrypted communication.
#include <Poco/Net/SSLManager.h> // Initializes and manages SSL/TLS
#include <Poco/Net/Context.h>    //Congures SSL context for secure connections.
#include <Poco/Net/NetException.h>    //Manages exceptions for network errors
#include <Poco/Util/Application.h> //implements the main subsystem in a process. The application class is responsible for initializing all its subsystems.
#include <Poco/Thread.h>
#include <iostream>
#include <vector>
#include <string>

class VPNClient {     //`VPNClient` class manages a secure VPN connection using SSL/TLS
private:
    Poco::Net::SecureStreamSocket socket; // The secure socket for communication.
    std::string serverAddress;    // Server's IP or hostname.
    uint16_t serverPort;          // Server's port number.
    bool isConnected;             // Connection status.
    std::vector<uint8_t> buffer;  // Buffer for receiving data.
    static const size_t BUFFER_SIZE = 4096; // Default buffer size for data transmission.

    // SSL Context
    Poco::Net::Context::Ptr getSSLContext() {
        return new Poco::Net::Context(
            Poco::Net::Context::CLIENT_USE,    // SSL client mode.
            "",  // certificatePath
            "",  // privateKeyPath
            "",  // caLocation
            Poco::Net::Context::VERIFY_RELAXED,
            9,   // verificationDepth
            true // loadDefaultCAs
        );
    }

public:
    VPNClient(const std::string& address, uint16_t port) //Takes server address and port as input.
        : serverAddress(address)
        , serverPort(port)
        , isConnected(false)
        , buffer(BUFFER_SIZE) {
        
        // Initialize SSL
        Poco::Net::initializeSSL(); //Initializes SSL  using `initializeSSL`.
    }

    ~VPNClient() {
        disconnect();    // Ensure the connection is closed.
        Poco::Net::uninitializeSSL(); // Clean up SSL resources.
    }
    //Establishes a secure connection with the server , Completes the SSL handshake for authentication
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
            
            isConnected = true; // Mark as connected.
            std::cout << "Successfully connected to VPN server" << std::endl;
            return true;
        }
        catch (Poco::Net::NetException& e) {
            std::cerr << "Connection error: " << e.what() << std::endl;
            isConnected = false;
            return false;
        }
    }
    // Safely terminates the connection and cleans up resources.
    void disconnect() {
        if (isConnected) {
            try {
                socket.shutdown();    // shut down the connection.
                socket.close();    // Close the socket.
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
            socket.sendBytes(data.data(), data.size());     // Send data over the secure socket.
            return true;
        }
        catch (Poco::Exception& e) {
            std::cerr << "Error sending data: " << e.what() << std::endl;
            return false;
        }
    }
    // Reads data securely from the server into a buer.
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

        return std::vector<uint8_t>();    // Return empty vector on failure.
    }

    bool isActive() const {
        return isConnected;
    }

    // Implement ping to keep connection alive
    void keepAlive() {
        while (isConnected) {
            try {
                std::vector<uint8_t> pingData = {0x01}; // Simple ping packet
                sendData(pingData);    // Send a ping packet.
                Poco::Thread::sleep(30000); // Sleep for 30 seconds
            }
            catch (Poco::Exception& e) {
                std::cerr << "Keep-alive error: " << e.what() << std::endl;
                break;
            }
        }
    }
};
