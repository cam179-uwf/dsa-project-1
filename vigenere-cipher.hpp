#ifndef VIGENERE_CIPHER
#define VIGENERE_CIPHER

#include <string>

class VigenereCipher 
{
    std::string _key;

public:
    VigenereCipher();
    VigenereCipher(const std::string& key);
    ~VigenereCipher();
    VigenereCipher(const VigenereCipher& other);
    VigenereCipher& operator=(const VigenereCipher& other);

    std::string get_encrypted(const std::string& value);
    std::string get_decrypted(const std::string& value);
};

#endif