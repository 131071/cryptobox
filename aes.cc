#include "aes.h"
#include "HexHelper.h"

AES::AES() {
}

AES::~AES() {
}

void AES::loadState(const unsigned char* input_state) {
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			state[j][i] = input_state[4 * i + j];
		}
	}
}

std::string AES::printState() {
	std::string output_state = "\n";
	for (int i = 0; i < 4; i++) {
		output_state += "[\t";
		for (int j = 0; j < 4; j++) {
			output_state += HexHelper::toHex(state[i][j]) + "\t";
		}
		output_state += "]\n";	
	}	
	return output_state;
}
