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

VigenereCipher::~VigenereCipher()
{
    
}

VigenereCipher::VigenereCipher(const VigenereCipher& other)
{
    
}

VigenereCipher& VigenereCipher::operator=(const VigenereCipher& other)
{
    return *this;
}

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
        result += (((c - 97) + offset) % 25) + 97;

        indexInKey = (indexInKey + 1) % _key.size();
    }

    return result;
}

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
    int offsetAdded;

    for (auto c : value)
    {
        offset = _key[indexInKey] - 97;

        offsetAdded = (c - 97) - offset;

        if (offsetAdded < 0)
        {
            offsetAdded = offsetAdded + 25;
        }

        result += ((offsetAdded) % 25) + 97;

        indexInKey = (indexInKey + 1) % _key.size();
    }

    return result;
}