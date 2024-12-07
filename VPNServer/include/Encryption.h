#pragma once
#include <vector>
#include <string>
#include <cstdint>

class Encryption {
public:
    static std::vector<uint8_t> encrypt(const std::vector<uint8_t>& data, const std::string& key);
    static std::vector<uint8_t> decrypt(const std::vector<uint8_t>& data, const std::string& key);
private:
    static const int KEY_SIZE = 32;  // 256 bits
};
