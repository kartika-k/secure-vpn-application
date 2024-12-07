// Ensures that the file is included only once in a single compilation cycle
#pragma once
#include <vector>
#include <string> //string class to manage and represent the encryption/decryption key as a sequence of characters.
#include <cstdint>

// Encapsulates encryption and decryption functionality
class Encryption {
public:
    // Encrypt the data using the given key - used to store binary data for encryption and decryption
    // Static: Allows the method to be called on the class itself without creating an object.
    // string &key -  Represents the encryption key, ensuring secure encryption.
    static std::vector<uint8_t> encrypt(const std::vector<uint8_t>& data, const std::string& key);
    
    // Decrypt the data using the given key
    static std::vector<uint8_t> decrypt(const std::vector<uint8_t>& data, const std::string& key);

private:
    static const int KEY_SIZE = 32;  // 256 bits - , suitable for AES-256 encryption algorithm
};
