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
    VigenereCipher(const VigenereCipher& other) = delete;
    VigenereCipher& operator=(const VigenereCipher& other) = delete;

    /**
     * Used for encrypting lowercase character strings.
     * @returns The encrypted lowercase character string.
     */
    std::string get_encrypted(const std::string& value);

    /**
     * Used for decrypting lowercase character strings.
     * @returns The decrypted lowercase character string.
     */
    std::string get_decrypted(const std::string& value);
};

#endif