#include "Tunnel.h" // Declares the `Tunnel` class.
#include <Poco/Net/SSLManager.h> //From Poco library; handle SSL/TLS setup 
#include <Poco/Net/Context.h> //and context conguration.
#include <Poco/Net/NetException.h> // For catching Poco-specic network errors.

// Initializes `socket_` to `nullptr` and `isConnected_` to `false`.
//Ensures the object starts in a clean state.
Tunnel::Tunnel() : socket_(nullptr), isConnected_(false) {
}

Tunnel::~Tunnel() {
    closeTunnel();    // Ensure the connection is closed safely.
    delete socket_;    // Free allocated resources for the socket.
}

bool Tunnel::initializeSSL() {
    try {
        Poco::Net::initializeSSL();    //Initializes SSL for the application for secure communication..
        return true;
    }
    catch (const Poco::Exception& exc) {
        return false; // Returns false on failure.
    }
}

bool Tunnel::createTunnel(const std::string& remoteAddress, int port) {
    try {
        // Congures an SSL context for client use.
        Poco::Net::Context::Ptr context = new Poco::Net::Context(
            Poco::Net::Context::CLIENT_USE,
            "",
            "",
            "", // No certificates (for testing or simple use cases).

            Poco::Net::Context::VERIFY_RELAXED, // Relaxed SSL certificate verification.
            9,
            true,
            "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH"  // Strong encryption preferences.
        );
        // Creates a `SecureStreamSocket` for encrypted communication
        socket_ = new Poco::Net::SecureStreamSocket(context); ; // Create an SSL socket.
        // Attempts to connect to the server using the provided `remoteAddress` and `port`
        socket_->connect(Poco::Net::SocketAddress(remoteAddress, port)); // Connect to the server.
        // Sets `isConnected_` to `true` if successful.
        isConnected_ = true;
        return true;
    }
    catch (const Poco::Exception& exc) {
        return false; // Return false if an exception occurs (e.g., connection failure).
    }
}
// Sends raw data through the secure tunnel.
bool Tunnel::sendData(const std::vector<uint8_t>& data) {
    try {
        // Ensures the connection is active before attempting to send data.
        if (!isConnected_) return false;  // Ensure the tunnel is active.
        socket_->sendBytes(data.data(), data.size());  // Send the data over the tunnel.
        return true; 
    }
    catch (const Poco::Exception& exc) {
        return false;  // Handle transmission failure.
    }
}
// Reads data from the secure tunnel into a buffer.
std::vector<uint8_t> Tunnel::receiveData() {
    try {
        if (!isConnected_) return std::vector<uint8_t>(); // Return empty if not connected.
        
        std::vector<uint8_t> buffer(4096); // Create a buffer to store incoming data.
        int received = socket_->receiveBytes(buffer.data(), buffer.size()); // Receive data.
        
        if (received > 0) {
            buffer.resize(received); // Resize the buffer to the actual received data size.
            return buffer;
        }
        return std::vector<uint8_t>();  // Return empty if no data is received.
    }
    catch (const Poco::Exception& exc) {
        return std::vector<uint8_t>();     // Handle reception failure.
    }
}
// Ensures the secure tunnel is closed properly when no longer needed.
void Tunnel::closeTunnel() {
    if (isConnected_ && socket_) {    // Check if a connection is active.
        socket_->close();    //  close the socket.
        isConnected_ = false;    // Mark the tunnel as disconnected.
    }
}
