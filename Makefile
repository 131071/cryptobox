AEStest: main.o aes.o HexHelper.o
	g++ main.o aes.o HexHelper.o -o AES

aes.o: aes.cc aes.h
	g++ -c -g aes.cc

main.o: main.cc aes.h
	g++ -c -g main.cc

HexHelper.o: HexHelper.cc HexHelper.h
	g++ -c -g HexHelper.cc
