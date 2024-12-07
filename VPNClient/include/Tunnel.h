#pragma once
#include <string> //Used for handling text data like the remote address of the server
#include <vector> //Used for transmitting and receiving binary data as a dynamic array
//Poco's Secure Stream Socket, which provides secure, encrypted communication over a network.
#include <Poco/Net/SecureServerSocket.h>

// Declares the `Tunnel` class, which encapsulates the logic for creating, managing, and closing a secure tunnel using SSL/TLS.
class Tunnel {
public:
    Tunnel();
    ~Tunnel();

    bool initializeSSL(); // Declares a method to initialize SSL for secure communication.Returns `true` if SSL initialization succeeds; otherwise, `false`
   
    //Declares a method to establish a secure tunnel with a remote server.
    //remoteAddress - Represents the server's address to which the tunnel connects.
    // port - Species the port number for communication.
    bool createTunnel(const std::string& remoteAddress, int port); 

    //Returns `true` if the data is successfully sent; otherwise, `false`
    bool sendData(const std::vector<uint8_t>& data);

    // Declares a method for receiving data through the secure tunnel
    std::vector<uint8_t> receiveData();
    void closeTunnel();

private:
    Poco::Net::SecureStreamSocket* socket_; //Represents the socket used for encrypted communication.
    bool isConnected_; //: Declares a ag to track the connection state of the tunnel.
   //`true`: The tunnel is active and connected. `false`: The tunnel is closed or not connected.
};
