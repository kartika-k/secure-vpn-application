#include "Tunnel.h"
#include <Poco/Net/SSLManager.h>
#include <Poco/Net/Context.h>
#include <Poco/Net/NetException.h>

Tunnel::Tunnel() : socket_(nullptr), isConnected_(false) {
}

Tunnel::~Tunnel() {
    closeTunnel();
    delete socket_;
}

bool Tunnel::initializeSSL() {
    try {
        Poco::Net::initializeSSL();
        return true;
    }
    catch (const Poco::Exception& exc) {
        return false;
    }
}

bool Tunnel::createTunnel(const std::string& remoteAddress, int port) {
    try {
        Poco::Net::Context::Ptr context = new Poco::Net::Context(
            Poco::Net::Context::CLIENT_USE,
            "",
            "",
            "",
            Poco::Net::Context::VERIFY_RELAXED,
            9,
            true,
            "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH"
        );

        socket_ = new Poco::Net::SecureStreamSocket(context);
        socket_->connect(Poco::Net::SocketAddress(remoteAddress, port));
        isConnected_ = true;
        return true;
    }
    catch (const Poco::Exception& exc) {
        return false;
    }
}

bool Tunnel::sendData(const std::vector<uint8_t>& data) {
    try {
        if (!isConnected_) return false;
        socket_->sendBytes(data.data(), data.size());
        return true;
    }
    catch (const Poco::Exception& exc) {
        return false;
    }
}

std::vector<uint8_t> Tunnel::receiveData() {
    try {
        if (!isConnected_) return std::vector<uint8_t>();
        
        std::vector<uint8_t> buffer(4096);
        int received = socket_->receiveBytes(buffer.data(), buffer.size());
        
        if (received > 0) {
            buffer.resize(received);
            return buffer;
        }
        return std::vector<uint8_t>();
    }
    catch (const Poco::Exception& exc) {
        return std::vector<uint8_t>();
    }
}

void Tunnel::closeTunnel() {
    if (isConnected_ && socket_) {
        socket_->close();
        isConnected_ = false;
    }
}
