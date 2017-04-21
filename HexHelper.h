#pragma once
#include <string>

class HexHelper {
static const char hexLookup[];
public:
  static std::string printArray(std::string, const unsigned char*, int);
  static std::string toHex(unsigned char);
  static unsigned char xmult(unsigned char, unsigned char);
  static unsigned char xtime(unsigned char);
};


