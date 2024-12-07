#include "Encryption.h" //Declares the `Encryption` class with `encrypt` and `decrypt` methods.
//Provides cryptographic utilities for encryption and decryption.
#include <Poco/Crypto/Cipher.h> 
#include <Poco/Crypto/CipherFactory.h>
#include <Poco/Crypto/CipherKey.h>
#include <stdexcept> //to report errors or exception

//Encrypts the input data using AES-256-CBC with the provided key.
std::vector<uint8_t> Encryption::encrypt(const std::vector<uint8_t>& data, const std::string& key) {
    try {
            // Obtains a reference to the default cipher factory:
        Poco::Crypto::CipherFactory& factory = Poco::Crypto::CipherFactory::defaultFactory();
        // Creates an AES-256-CBC cipher using the provided key:
        Poco::Crypto::Cipher::Ptr cipher = factory.createCipher(
            Poco::Crypto::CipherKey("aes-256-cbc", key)
        );
        // Encrypts the input data as a string
        std::string encrypted = cipher->encryptString(
            // `reinterpret_cast` - Converts binary data to a string
            std::string(reinterpret_cast<const char*>(data.data()), data.size())
        );
        // Converts the encrypted string back to a `std::vector<uint8_t>` and returns it.
        return std::vector<uint8_t>(encrypted.begin(), encrypted.end());
    }
    // Catches any exceptions and returns an empty vector if encryption fails.
    catch (const std::exception& e) {
        throw std::runtime_error(std::string("Encryption failed: ") + e.what());
    }
}
// Decrypts the encrypted data using AES-256-CBC with the provided key.
std::vector<uint8_t> Encryption::decrypt(const std::vector<uint8_t>& data, const std::string& key) {
    try {
        Poco::Crypto::CipherFactory& factory = Poco::Crypto::CipherFactory::defaultFactory();
        Poco::Crypto::Cipher::Ptr cipher = factory.createCipher(
            Poco::Crypto::CipherKey("aes-256-cbc", key)
        );

        std::string decrypted = cipher->decryptString(
            std::string(reinterpret_cast<const char*>(data.data()), data.size())
        );
        // Converts the decrypted string back to a `std::vector<uint8_t>` and returns it.
        return std::vector<uint8_t>(decrypted.begin(), decrypted.end());
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Decryption failed: ") + e.what());
    }
}
