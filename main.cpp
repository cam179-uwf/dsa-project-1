#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <iomanip>

#include "vigenere-cipher.hpp"
#include "hashtable.hpp"

int main(int argc, char** argv)
{
    std::ifstream ifs("names.txt");

    if (!ifs.is_open())
    {
        std::cout << "The file names.txt could not be opened!" << std::endl;
        return EXIT_FAILURE;
    }

    // raw data out file stream
    std::ofstream rawdataOfs("rawdata.txt");

    // set up our random number generator
    std::random_device rd;
    std::mt19937 eng(rd());
    // lowercase ASCII is in the range of 97 to 122
    std::uniform_int_distribution<int> dist(97, 122);

    // set up our initial variables
    std::string word;
    int columnIndex = 3;

    // read the names.txt file
    while (ifs >> word)
    {
        if (columnIndex == 3)
        {
            columnIndex = 0;

            // now generate the userid's password
            std::string password;

            for (int i = 0; i < 9; ++i)
            {
                password += dist(eng);
            }

            // write our userid and new password to the rawdata.txt file
            rawdataOfs << std::left << std::setw(15) << word << std::setw(15) << password << '\n';
            continue;
        }

        ++columnIndex;
    }

    // raw data in file stream
    std::ifstream rawdataIfs("rawdata.txt");

    if (!ifs.is_open())
    {
        std::cout << "The file rawdata.txt could not be opened!" << std::endl;
        return EXIT_FAILURE;
    }

    // encrypted data out file stream
    std::ofstream edataOfs("encrypteddata.txt");

    VigenereCipher vc;
    HashTable<std::string> hashTable(40);

    std::cout << "Creating encrypted passwords file and hash table. This make take a few seconds..." << std::endl;

    while (!rawdataIfs.eof())
    {
        rawdataIfs >> word;
        std::string userid = word;

        rawdataIfs >> word;
        std::string password = word;

        std::string encryptedPwd = vc.get_encrypted(password);

        hashTable.push(userid, encryptedPwd);

        edataOfs << std::left << std::setw(15) << userid << std::setw(15) << encryptedPwd << '\n';
    }

    std::cout << "Found SMITH: " << *hashTable.find("SMITH") << std::endl;

    ifs.close();
    rawdataOfs.close();
    rawdataIfs.close();
    edataOfs.close();
    return EXIT_SUCCESS;
}