#pragma once

class AESConstants {
public:
	static const unsigned char SBOX[256];
	static const unsigned char INV_SBOX[256];
	static const unsigned char MIXER[4][4];
	static const unsigned char INV_MIXER[4][4];
};


