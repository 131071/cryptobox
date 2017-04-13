#pragma once
#include <string>

class AES {
unsigned char state[4][4];
public:
	AES();
	~AES();
	void loadState(const unsigned char*);
	std::string printState();
};
