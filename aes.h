#pragma once
#include <string>

class AES {
unsigned char state[4][4];
public:
	AES();
	~AES();
	void loadState(const unsigned char*);
	void getState(unsigned char*);
	std::string printState();

// private:
	void subBytes();
	void invSubBytes();
	void shiftRows();
	void invShiftRows();
	void mixColumns();
	void invMixColumns();

private:
	void subBytes(const unsigned char[256]);
	void mixColumns(const unsigned char[4][4]);
};


