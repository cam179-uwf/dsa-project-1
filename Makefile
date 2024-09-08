main: main.cpp vigenere-cipher.o
	g++ $^ -Wall -std=c++11 -o main

vigenere-cipher.o: vigenere-cipher.cpp
	g++ -c $<

clean-win: 
	del *.o main *.exe rawdata.txt encrypteddata.txt

clean: 
	rm *.o main *.exe rawdata.txt encrypteddata.txt