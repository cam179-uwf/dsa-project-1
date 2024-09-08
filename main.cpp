#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <iomanip>

#include "vigenere-cipher.hpp"
#include "hashtable.hpp"

struct Entry 
{
    std::string userid;
    std::string password;
};

void createRawDataFile()
{
    std::ifstream ifs("names.txt");

    if (!ifs.is_open())
    {
        std::cout << "The file names.txt could not be opened!" << std::endl;
        exit(EXIT_FAILURE);
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

    ifs.close();
    rawdataOfs.close();
}

void createEncryptedDataFile(VigenereCipher& cipher, HashTable<std::string>& hashTable)
{
    // raw data in file stream
    std::ifstream rawdataIfs("rawdata.txt");

    if (!rawdataIfs.is_open())
    {
        std::cout << "The file rawdata.txt could not be opened!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // encrypted data out file stream
    std::ofstream edataOfs("encrypteddata.txt");
    std::string userid;
    std::string password;

    while (!rawdataIfs.eof())
    {
        rawdataIfs >> userid;
        rawdataIfs >> password;

        std::string encryptedPwd = cipher.get_encrypted(password);

        hashTable.push(userid, encryptedPwd);

        edataOfs << std::left << std::setw(15) << userid << std::setw(15) << encryptedPwd << '\n';
    }

    rawdataIfs.close();
    edataOfs.close();
}

int main(int argc, char** argv)
{
    HashTable<std::string> hashTable(40);
    VigenereCipher cipher;

    std::cout << "Creating encrypted passwords file and hash table. This make take a few seconds..." << std::endl;

    createRawDataFile();
    createEncryptedDataFile(cipher, hashTable);

    std::ifstream ifs("rawdata.txt");

    if (!ifs.is_open())
    {
        std::cout << "The file encrypteddata.txt could not be opened!" << std::endl;
        return EXIT_FAILURE;
    }

    int row = 0;
    Entry fileEntries[5];
    std::string userid;
    std::string password;

    while (!ifs.eof())
    {
        ifs >> userid;
        ifs >> password;

        switch (row)
        {
            case 0:
                fileEntries[0].userid = userid;
                fileEntries[0].password = password;
                break;
            case 2:
                fileEntries[1].userid = userid;
                fileEntries[1].password = password;
                break;
            case 4:
                fileEntries[2].userid = userid;
                fileEntries[2].password = password;
                break;
            case 6:
                fileEntries[3].userid = userid;
                fileEntries[3].password = password;
                break;
            case 8:
                fileEntries[4].userid = userid;
                fileEntries[4].password = password;
                break;
        }

        ++row;

        if (row > 8)
            break;
    }

    std::cout << std::endl;
    std::cout << "Legal:\n" << std::endl;
    std::cout << std::left << std::setw(15) << "Userid";
    std::cout << std::left << std::setw(20) << "Password(file)";
    std::cout << std::left << std::setw(20) << "Password(table/un)";
    std::cout << std::left << std::setw(15) << "Result";
    std::cout << std::endl;

    for (int i = 0; i < 5; ++i)
    {
        std::string decryptedHashPassword = cipher.get_decrypted(*hashTable.find(fileEntries[i].userid));

        std::cout << std::left << std::setw(15) << fileEntries[i].userid;
        std::cout << std::left << std::setw(20) << fileEntries[i].password;
        std::cout << std::left << std::setw(20) << decryptedHashPassword;
        std::cout << std::left << std::setw(15) << (fileEntries[i].password == decryptedHashPassword ? "match" : "no match");
        std::cout << std::endl; 
    }

    std::cout << std::endl;
    std::cout << "Illegal:\n" << std::endl;
    std::cout << std::left << std::setw(15) << "Userid";
    std::cout << std::left << std::setw(20) << "Password(mod)";
    std::cout << std::left << std::setw(20) << "Password(table/un)";
    std::cout << std::left << std::setw(15) << "Result";
    std::cout << std::endl;

    for (int i = 0; i < 5; ++i)
    {
        if (fileEntries[i].password[0] != 'z')
            fileEntries[i].password[0] = 'z';
        else
            fileEntries[i].password[0] = 'a';

        std::string decryptedHashPassword = cipher.get_decrypted(*hashTable.find(fileEntries[i].userid));

        std::cout << std::left << std::setw(15) << fileEntries[i].userid;
        std::cout << std::left << std::setw(20) << fileEntries[i].password;
        std::cout << std::left << std::setw(20) << decryptedHashPassword;
        std::cout << std::left << std::setw(15) << (fileEntries[i].password == decryptedHashPassword ? "match" : "no match");
        std::cout << std::endl; 
    }

    return EXIT_SUCCESS;
}