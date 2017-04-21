#include "HexHelper.h"

const char HexHelper::hexLookup[16] = { '0', '1', '2', '3', '4', '5', '6', '7', 
                                    '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

std::string HexHelper::printArray(std::string arrayName, const unsigned char* arr
                                                    , int arrayLength) {
	std::string output = arrayName + " = { \t";
	for (int i = 0; i < arrayLength; i++) {
		output = output + toHex(arr[i]);
		if (i != arrayLength) {
			output = output + ", \t";
		}
		if ((i + 1) % 10 == 0) {
			output = output + "\n\t\t\t\t";
		}
	}
	output = output + "\t}\n";
	return output;
}

unsigned char HexHelper::xmult(unsigned char a, unsigned char b){
	unsigned char x = a;
	unsigned char prod = 0x00;
	for (int i = 0; i < 8; i++){
		if (b & (0x01 << i)) {
			prod ^= x;
		}
		x = xtime(x);
	}
	return prod;
}

unsigned char HexHelper::xtime(unsigned char a) {
	unsigned char x = a << 1;
	if (a & 0x80) {
		x ^= 0x1B;
	}
	return x;
}

std::string HexHelper::toHex(unsigned char a){
	std::string s = "0x";
	s += hexLookup[a >>4];
	s += hexLookup[a & 0x0F];
	return s;
}

