AEStest: main.o aes.o HexHelper.o AESConstants.o
	g++ main.o aes.o HexHelper.o AESConstants.o -o AES

aes.o: aes.cc aes.h HexHelper.h
	g++ -c -g aes.cc

main.o: main.cc aes.h AESConstants.h
	g++ -c -g main.cc

HexHelper.o: HexHelper.cc HexHelper.h
	g++ -c -g HexHelper.cc

AESConstants.o: AESConstants.cc AESConstants.h
	g++ -c -g AESConstants.cc



