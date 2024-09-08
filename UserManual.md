# Project 1
COP4534<br>
Christian Marcellino<br>
9/8/2024<br>

**Setup and Compilation**
1. Download and unzip the submission from eLearning on a Linux box in the multi-platform lab.
2. The submission includes:
    * hashTable.hpp
    * main.cpp
    * vigenere-cipher.hpp
    * vigenere-cipher.cpp
    * Makefile
    * names.txt
    * UserManual.md
3. Environment: This program has been tested on Windows, Linux and the multi-platform lab and will run on all three.
4. Compiling. This program includes a Makefile. At the command line in Linux, type `make`. Make will produce an executable file.

**Running the program**. Once the executable file has been produced, ensure the `names.txt` file is within the same folder as the executable file. Then simply run `./main` to execute the program. There are no command line arguments required.

*User input*: no user input is required.

**Output**: All output will be displayed in the terminal and should look like the following:

```
Creating encrypted passwords file and hash table. This make take a few seconds...

Legal:

Userid         Password(file)      Password(table/un)  Result
SMITH          osjxapwny           osjxapwny           match
WILLIAMS       oiipgaeyz           oiipgaeyz           match
BROWN          vxhqxowao           vxhqxowao           match
MILLER         ywmszxtis           ywmszxtis           match
MOORE          wdnahmick           wdnahmick           match

Illegal:

Userid         Password(mod)       Password(table/un)  Result
SMITH          zsjxapwny           osjxapwny           no match
WILLIAMS       ziipgaeyz           oiipgaeyz           no match
BROWN          zxhqxowao           vxhqxowao           no match
MILLER         zwmszxtis           ywmszxtis           no match
MOORE          zdnahmick           wdnahmick           no match
```