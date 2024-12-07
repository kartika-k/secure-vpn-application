#include "Encryption.h"
#include <Poco/Crypto/Cipher.h>
#include <Poco/Crypto/CipherFactory.h>
#include <Poco/Crypto/CipherKey.h>

std::vector<uint8_t> Encryption::encrypt(const std::vector<uint8_t>& data, const std::string& key) {
    try {
        Poco::Crypto::CipherFactory& factory = Poco::Crypto::CipherFactory::defaultFactory();
        Poco::Crypto::Cipher::Ptr cipher = factory.createCipher(
            Poco::Crypto::CipherKey("aes-256-cbc", key)
        );
        
        std::string encrypted = cipher->encryptString(
            std::string(reinterpret_cast<const char*>(data.data()), data.size())
        );
        
        return std::vector<uint8_t>(encrypted.begin(), encrypted.end());
    }
    catch (...) {
        return std::vector<uint8_t>();
    }
}

std::vector<uint8_t> Encryption::decrypt(const std::vector<uint8_t>& data, const std::string& key) {
    try {
        Poco::Crypto::CipherFactory& factory = Poco::Crypto::CipherFactory::defaultFactory();
        Poco::Crypto::Cipher::Ptr cipher = factory.createCipher(
            Poco::Crypto::CipherKey("aes-256-cbc", key)
        );
        
        std::string decrypted = cipher->decryptString(
            std::string(reinterpret_cast<const char*>(data.data()), data.size())
        );
        
        return std::vector<uint8_t>(decrypted.begin(), decrypted.end());
    }
    catch (...) {
        return std::vector<uint8_t>();
    }
}