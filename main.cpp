#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <iomanip>

int main(int argc, char** argv)
{
    std::ifstream ifs("names.txt");

    if (!ifs.is_open())
    {
        std::cout << "The file names.txt could not be opened!" << std::endl;
        return EXIT_FAILURE;
    }

    std::ofstream ofs("rawdata.txt");

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
            ofs << std::left << std::setw(15) << word << std::setw(15) << password << '\n';
            continue;
        }

        ++columnIndex;
    }

    ifs.close();
    ofs.close();
    return EXIT_SUCCESS;
}