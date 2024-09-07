main: main.cpp vigenere-cipher.o
	g++ $^ -o main

vigenere-cipher.o: vigenere-cipher.cpp
	g++ -c $<

clean-win: 
	del *.o main *.exe rawdata.txt