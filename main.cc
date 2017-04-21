#include "aes.h"
#include "HexHelper.h"
#include "AESConstants.h"
#include <iostream>

using namespace std;

const unsigned char test_state[16] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 
                                        0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 
                                        0x0c, 0x0d, 0x0e, 0x0f };

int main() {
    string test_state_string = HexHelper::printArray("test_state", 
                                                    test_state, 16);
    cout << test_state_string << endl;

    AES t_aes;
    t_aes.loadState(test_state);
    cout << t_aes.printState();

    unsigned char post_state[16];
    t_aes.getState(post_state);
    cout << HexHelper::printArray("post_state", post_state, 16);

    cout << HexHelper::printArray("sbox", AESConstants::SBOX, 256);
    cout << HexHelper::printArray("inv_sbox", AESConstants::INV_SBOX, 256) << endl;

    cout << "SUB_BYTES!!!: ";
    t_aes.subBytes();
    cout << t_aes.printState();

    cout << "SHIFT ROWS!!!: ";
    t_aes.shiftRows();
    cout << t_aes.printState();

    cout << "MIX COLUMNS!!!: ";
    t_aes.mixColumns();
    cout << t_aes.printState();

    cout << "INV MIX COLUMNS!!!: ";
    t_aes.invMixColumns();
    cout << t_aes.printState();

    cout << "INV SHIFT ROWS!!!: ";
    t_aes.invShiftRows();
    cout << t_aes.printState();

    cout << "INV_SUB_BYTES!!!: ";
    t_aes.invSubBytes();
    cout << t_aes.printState();

    cin.get();
    return 0;
}
