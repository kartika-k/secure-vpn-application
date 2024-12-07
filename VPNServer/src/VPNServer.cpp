#include <Poco/Net/SecureServerSocket.h>    //Provides a server socket class for secure SSL/TLS connections.
#include <Poco/Net/SecureStreamSocket.h>    //Provides a stream socket class for secure SSL/TLS connections.
#include <Poco/Net/Context.h>               //Represents the SSL context, managing certificates, keys.
#include <Poco/Net/SSLManager.h>            //Handles the initialization and cleanup of the SSL/TLS subsystem.
#include <Poco/Thread.h>                    //Provide thread management classes.
#include <Poco/ThreadPool.h>
#include <Poco/Logger.h>
#include <Poco/FileChannel.h>                //Provide logging utilities for file-based logging with formatted log messages.(Logger.h,PatternFormatter.h,FormattingChannel.h)
#include <Poco/PatternFormatter.h>
#include <Poco/FormattingChannel.h>
#include <Poco/AutoPtr.h>                    //Provides smart pointer functionality for automatic memory management.
#include <iostream>
#include <vector>
#include <map>                               //Key-value pair container for managing client connections.
#include <mutex>                             // Provides thread-safety for shared resources.
#include <memory>                            //Provides smart pointers like std::shared_ptr.
#include <functional>                        //For using std::function and lambda expressions.

// Helper class to wrap lambdas for Poco::Runnable
// This allows using lambda functions as tasks in Poco thread pools.
class RunnableWrapper : public Poco::Runnable {
private:
    std::function<void()> task;

public:
    explicit RunnableWrapper(std::function<void()> func) : task(std::move(func)) {}

    void run() override {
        task();
    }
};

class VPNServer {
private:
    //Secure server socket for handling incoming SSL/TLS connections.
    Poco::Net::SecureServerSocket serverSocket;
    Poco::ThreadPool threadPool;    // Thread pool for managing client handling threads.
    bool isRunning;                //Flag to indicate if the server is running.
    mutable std::mutex clientsMutex; // Use mutable to allow modification in const methods
    std::map<std::string, Poco::Net::SecureStreamSocket> clients; // Active client connections.
    Poco::Logger& logger;    //// Logger for logging server events.
    static const size_t BUFFER_SIZE = 4096;    // Buffer size for receiving data.

    // Initializes the SSL context for secure connections.
    Poco::Net::Context::Ptr getSSLContext() {
        return new Poco::Net::Context(
            Poco::Net::Context::SERVER_USE,    // Context for server-side SSL.
            "server.crt",     // Certificate path
            "server.key",     // Private key path
            "cafile.pem",     // CA certificates file
            Poco::Net::Context::VERIFY_RELAXED,
            9,                // Verification mode
            true,             // Load default CA certificates
            "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH" // Cipher list
        );
    }

    // Initializes the logger with a file output channel and formatted messages.
    static Poco::Logger& initLogger() {
        Poco::AutoPtr<Poco::FileChannel> fileChannel(new Poco::FileChannel("vpn_server.log"));
        Poco::AutoPtr<Poco::PatternFormatter> formatter(new Poco::PatternFormatter);
        formatter->setProperty("pattern", "%Y-%m-%d %H:%M:%S.%i [%p] %s: %t");    // Log message format.
        Poco::AutoPtr<Poco::FormattingChannel> formattingChannel(
            new Poco::FormattingChannel(formatter, fileChannel));
        Poco::Logger::root().setChannel(formattingChannel);
        return Poco::Logger::get("VPNServer");
    }
    // Handles communication with a connected client.
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

                    // Process received data
                    handleReceivedData(clientId, buffer, received);
                }
                catch (Poco::TimeoutException&) {
                    // Timeout is normal, continue listening for data
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
    // Processes received data from a client.
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
        logger.information("Received " + std::to_string(received) + 
                         " bytes from client " + clientId);
    }

public:
    // Constructor to initialize the server.
    VPNServer(uint16_t port)
        : threadPool(4, 32)   // Thread pool with a minimum of 4 and a maximum of 32 threads.
        , isRunning(false)
        , logger(initLogger()) {
        
        // Initialize SSL
        Poco::Net::initializeSSL();    // Initialize the SSL subsystem.
        
        // Create SSL context and server socket
        Poco::Net::Context::Ptr context = getSSLContext();     // Create SSL context.
        serverSocket = Poco::Net::SecureServerSocket(
            Poco::Net::SocketAddress("0.0.0.0", port),  // Bind to all network interfaces on the specified port.
            64,     // Connection backlog.
            context    // SSL context for secure connections.
        );

        serverSocket.setReceiveTimeout(Poco::Timespan(5, 0)); // Set a 5-second timeout for receiving data.
        logger.information("VPN Server initialized on port " + std::to_string(port));
    }

    ~VPNServer() {
        stop();    // Stop the server and clean up resources.
        Poco::Net::uninitializeSSL();    // Uninitialize the SSL subsystem.
    }
    // Starts the server to accept client connections.
    void start() {
        if (isRunning) return;

        isRunning = true;
        logger.information("VPN Server starting...");

        while (isRunning) {
            try {
                Poco::Net::SecureStreamSocket clientSocket = serverSocket.acceptConnection();

                // Handle client in thread pool using RunnableWrapper
                std::shared_ptr<RunnableWrapper> runnable = std::make_shared<RunnableWrapper>([this, clientSocket]() mutable {
                    handleClient(clientSocket);
                });
                threadPool.start(*runnable);
            }
            catch (Poco::TimeoutException&) {
                continue;
            }
            catch (Poco::Exception& e) {
                logger.error("Error accepting connection: " + e.displayText());
                Poco::Thread::sleep(1000); // Wait before retry
            }
        }
    }
// Stops the server and cleans up resources.
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
