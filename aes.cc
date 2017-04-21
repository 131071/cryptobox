#include "aes.h"
#include "HexHelper.h"
#include "AESConstants.h"

AES::AES() {
}

AES::~AES() {
}

void AES::loadState(const unsigned char* input_state) {
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			state[j][i] = input_state[ (4 * i) + j];
		}
	}
}

void AES::getState(unsigned char* output_state) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			output_state[ (4 * i) + j ] = state[j][i];
		}
	}
}

std::string AES::printState() {
	std::string output_state = "\n";
	for (int i = 0; i < 4; i++) {
		output_state = output_state + "[\t";
		for (int j = 0; j < 4; j++) {
			output_state = output_state + HexHelper::toHex(state[i][j]) + "\t";
		}
		output_state = output_state + "]\n";	
	}
	return output_state + "\n";	
}

void AES::subBytes() {
	subBytes(AESConstants::SBOX);
}

void AES::invSubBytes() {
	subBytes(AESConstants::INV_SBOX);
}

void AES::subBytes(const unsigned char sbox[256]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			state[j][i] = sbox[ state[j][i] ];
		}
	}
}

void AES::shiftRows() {
	unsigned char t;
	for (int a = 0; a < 4; a++) {
		for (int i = 0; i < a; i++) {
			t = state[a][0];
			state[a][0] = state[a][1];
			state[a][1] = state[a][2];
			state[a][2] = state[a][3];
			state[a][3] = t;
		}
	}
}

void AES::invShiftRows() {
	unsigned char t;
	for (int a = 0; a < 4; a++) {
		for (int i = 0; i < a; i++) {
			t = state[a][3];
			state[a][3] = state[a][2];
			state[a][2] = state[a][1];
			state[a][1] = state[a][0];
			state[a][0] = t;
		}
	}
}

void AES::mixColumns() {
	mixColumns(AESConstants::MIXER);
}

void AES::invMixColumns() {
	mixColumns(AESConstants::INV_MIXER);
}

void AES::mixColumns(const unsigned char mixer[4][4]) {
	unsigned char temp[4];
	unsigned char x, mb;
	int i,j,k;

	for (i = 0; i < 4; i++) {
		temp[0] = state[0][i];
		temp[1] = state[1][i];
		temp[2] = state[2][i];
		temp[3] = state[3][i];

		for (j = 0; j < 4; j++) {
			mb = 0x00;
			for (k = 0; k < 4; k++) {
				x = HexHelper::xmult(temp[k], mixer[j][k]);
				mb ^= x;
			}
			state[j][i] = mb;
		}
	}
}


