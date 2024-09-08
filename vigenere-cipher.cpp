#include "vigenere-cipher.hpp"

VigenereCipher::VigenereCipher()
{
    _key = "jones";
}

VigenereCipher::VigenereCipher(const std::string& key)
{
    _key = key;

    if (_key.size() < 2)
    {
        std::__throw_length_error("The cipher key must have a size greater than 2.");
    }

    for (auto c : key)
    {
        if (c < 'a' || c > 'z')
        {
            std::__throw_runtime_error("The cipher key should only contain lowercase letters.");
        }
    }
}

VigenereCipher::~VigenereCipher() { }

/**
 * Used for encrypting lowercase character strings.
 * @returns The encrypted lowercase character string.
 */
std::string VigenereCipher::get_encrypted(const std::string& value)
{
    for (auto c : value)
    {
        if (c < 'a' || c > 'z')
        {
            std::__throw_runtime_error("The value trying to be encrypted should only contain lowercase letters.");
        }
    }

    std::string result;
    int indexInKey = 0;
    int offset;

    for (auto c : value)
    {
        offset = _key[indexInKey] - 97;
        int original = (c - 97);
        int modified = original + offset;

        if (modified > 25)
        {
            modified %= 26;
        }

        result += modified + 97;

        indexInKey = (indexInKey + 1) % _key.size();
    }

    return result;
}

/**
 * Used for decrypting lowercase character strings.
 * @returns The decrypted lowercase character string.
 */
std::string VigenereCipher::get_decrypted(const std::string& value)
{
    for (auto c : value)
    {
        if (c < 'a' || c > 'z')
        {
            std::__throw_runtime_error("The value trying to be decrypted should only contain lowercase letters.");
        }
    }

    std::string result;
    int indexInKey = 0;
    int offset;

    for (auto c : value)
    {
        offset = _key[indexInKey] - 97;
        int original = (c - 97);
        int modified = original - offset;
        
        if (modified < 0)
        {
            modified = 25 - (-1 * modified - 1) % 26;
        }

        result += modified + 97;

        indexInKey = (indexInKey + 1) % _key.size();
    }

    return result;
}