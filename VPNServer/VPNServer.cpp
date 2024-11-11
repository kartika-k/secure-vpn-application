#include <Poco/Net/SecureServerSocket.h>
#include <Poco/Net/SecureStreamSocket.h>
#include <Poco/Net/Context.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/Thread.h>
#include <Poco/ThreadPool.h>
#include <Poco/Logger.h>
#include <Poco/FileChannel.h>
#include <Poco/PatternFormatter.h>
#include <Poco/FormattingChannel.h>
#include <Poco/AutoPtr.h>
#include <iostream>
#include <vector>
#include <map>
#include <mutex>

class VPNServer {
private:
    Poco::Net::SecureServerSocket serverSocket;
    Poco::ThreadPool threadPool;
    bool isRunning;
    std::mutex clientsMutex;
    std::map<std::string, Poco::Net::SecureStreamSocket> clients;
    Poco::Logger& logger;
    static const size_t BUFFER_SIZE = 4096;

    // SSL Context initialization
    Poco::Net::Context::Ptr getSSLContext() {
        return new Poco::Net::Context(
            Poco::Net::Context::SERVER_USE,
            "server.crt",     // Certificate path
            "server.key",     // Private key path
            "cafile.pem",     // CA certificates file
            Poco::Net::Context::VERIFY_RELAXED,
            9,                // Verification depth
            true,            // Load default CA certificates
            "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH" // Cipher list
        );
    }

    // Initialize logger
    static Poco::Logger& initLogger() {
        Poco::AutoPtr<Poco::FileChannel> fileChannel(new Poco::FileChannel("vpn_server.log"));
        Poco::AutoPtr<Poco::PatternFormatter> formatter(new Poco::PatternFormatter);
        formatter->setProperty("pattern", "%Y-%m-%d %H:%M:%S.%i [%p] %s: %t");
        Poco::AutoPtr<Poco::FormattingChannel> formattingChannel(
            new Poco::FormattingChannel(formatter, fileChannel));
        Poco::Logger::root().setChannel(formattingChannel);
        return Poco::Logger::get("VPNServer");
    }

    void handleClient(Poco::Net::SecureStreamSocket& clientSocket) {
        std::string clientId = clientSocket.peerAddress().toString();
        logger.information("New client connected: " + clientId);

        try {
            // Add client to active connections
            {
                std::lock_guard<std::mutex> lock(clientsMutex);
                clients[clientId] = clientSocket;
            }

            std::vector<uint8_t> buffer(BUFFER_SIZE);
            bool clientConnected = true;

            while (clientConnected && isRunning) {
                try {
                    int received = clientSocket.receiveBytes(buffer.data(), BUFFER_SIZE);
                    
                    if (received <= 0) {
                        logger.warning("Client disconnected: " + clientId);
                        break;
                    }

                    // Handle received data
                    handleReceivedData(clientId, buffer, received);
                }
                catch (Poco::TimeoutException&) {
                    // Timeout is normal, continue listening
                    continue;
                }
                catch (Poco::Exception& e) {
                    logger.error("Error handling client " + clientId + ": " + e.displayText());
                    clientConnected = false;
                }
            }
        }
        catch (Poco::Exception& e) {
            logger.error("Fatal error handling client " + clientId + ": " + e.displayText());
        }

        // Remove client from active connections
        {
            std::lock_guard<std::mutex> lock(clientsMutex);
            clients.erase(clientId);
        }

        try {
            clientSocket.shutdown();
            clientSocket.close();
        }
        catch (...) {
            // Ignore shutdown errors
        }

        logger.information("Client disconnected and cleaned up: " + clientId);
    }

    void handleReceivedData(const std::string& clientId, 
                           const std::vector<uint8_t>& buffer, 
                           int received) {
        // Check if it's a keep-alive ping (0x01)
        if (received == 1 && buffer[0] == 0x01) {
            // Respond to keep-alive
            std::vector<uint8_t> pong = {0x02};
            try {
                std::lock_guard<std::mutex> lock(clientsMutex);
                if (clients.find(clientId) != clients.end()) {
                    clients[clientId].sendBytes(pong.data(), pong.size());
                }
            }
            catch (Poco::Exception& e) {
                logger.error("Error sending keep-alive response to " + 
                           clientId + ": " + e.displayText());
            }
            return;
        }

        // Process other data packets
        // Add your custom packet handling logic here
        logger.information("Received " + std::to_string(received) + 
                         " bytes from client " + clientId);
    }

public:
    VPNServer(uint16_t port)
        : threadPool(4, 32)  // min 4, max 32 threads
        , isRunning(false)
        , logger(initLogger()) {
        
        // Initialize SSL
        Poco::Net::initializeSSL();
        
        // Create SSL context and server socket
        Poco::Net::Context::Ptr context = getSSLContext();
        serverSocket = Poco::Net::SecureServerSocket(
            Poco::Net::SocketAddress("0.0.0.0", port), 
            64,     // Backlog
            context
        );

        serverSocket.setReceiveTimeout(Poco::Timespan(5, 0)); // 5 seconds timeout
        logger.information("VPN Server initialized on port " + std::to_string(port));
    }

    ~VPNServer() {
        stop();
        Poco::Net::uninitializeSSL();
    }

    void start() {
        if (isRunning) return;

        isRunning = true;
        logger.information("VPN Server starting...");

        while (isRunning) {
            try {
                // Wait for client connection
                Poco::Net::SecureStreamSocket clientSocket = serverSocket.acceptConnection();
                
                // Handle client in thread pool
                threadPool.start([this, clientSocket]() mutable {
                    handleClient(clientSocket);
                });
            }
            catch (Poco::TimeoutException&) {
                // Timeout is normal, continue accepting
                continue;
            }
            catch (Poco::Exception& e) {
                logger.error("Error accepting connection: " + e.displayText());
                Poco::Thread::sleep(1000); // Wait before retry
            }
        }
    }

    void stop() {
        if (!isRunning) return;

        logger.information("VPN Server stopping...");
        isRunning = false;

        // Close all client connections
        std::lock_guard<std::mutex> lock(clientsMutex);
        for (auto& client : clients) {
            try {
                client.second.shutdown();
                client.second.close();
            }
            catch (...) {
                // Ignore shutdown errors
            }
        }
        clients.clear();

        // Close server socket
        try {
            serverSocket.close();
        }
        catch (...) {
            // Ignore close errors
        }

        // Wait for all threads to complete
        threadPool.joinAll();
        logger.information("VPN Server stopped");
    }

    bool isActive() const {
        return isRunning;
    }

    size_t getConnectedClientsCount() const {
        std::lock_guard<std::mutex> lock(clientsMutex);
        return clients.size();
    }
};
