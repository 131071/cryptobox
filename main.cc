#include "aes.h"
#include "HexHelper.h"
#include <iostream>

using namespace std;

unsigned char test_state[16] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 
                                        0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 
                                        0x0c, 0x0d, 0x0e, 0x0f };

int main() {
    string test_state_string = HexHelper::printArray("test_state", 
                                                    test_state, 16);
                                                    
    cout << test_state_string << endl;
    cin.get();
    return 0;
}