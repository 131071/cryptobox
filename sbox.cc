#include <iostream>
#include <string>
using namespace std;

void initSbox();
void initInvSbox();
void printArray(string, unsigned char[]);

unsigned char subByte(unsigned char);
unsigned char affineTrans(unsigned char);
unsigned char modInverse(unsigned char);
void extendedEuclidean(unsigned int[], unsigned int, unsigned int);
void xdiv(unsigned int, unsigned int, unsigned int*, unsigned int*);
int get_order(unsigned int);
unsigned char xmult(unsigned char, unsigned char);
unsigned char xtime(unsigned char);
string toHex(unsigned char);

unsigned char SBOX[256];
unsigned char INV_SBOX[256];

int main() {
	initSbox();
	initInvSbox();
	printArray("SBOX", SBOX);
	printArray("INV_SBOX", INV_SBOX);
	return 0;
}

void initSbox() {
	for (unsigned int i = 0; i < 256; i++) {
		SBOX[i] = subByte(i);
	}
}

void initInvSbox() {
	for (unsigned int i = 0; i < 256; i++) {
		INV_SBOX[SBOX[i]] = i;
	}
}

void printArray(string arrayName, unsigned char arr[]) {
	cout << "const static " << arrayName << " = { \t";
	for (int i = 0; i < 256; i++) {
		cout << toHex(arr[i]);
		if (i != 255) {
			cout << ", \t";
		}
		if ((i + 1) % 10 == 0) {
			cout << "\n\t\t\t\t";
		}
	}
	cout << "\t};" << endl;
}

unsigned char subByte(unsigned char b) {
	return affineTrans(modInverse(b));
}

unsigned char affineTrans(unsigned char b) {
	const unsigned char c = 0x63;
	unsigned char b_prime = 0x00;
	unsigned char bit;
	for (int i = 0; i < 8; i++) {
		bit = 0x00;
		bit ^= ( ( b & ( 0x01 <<  i  ) )  >> i );
		bit ^= ( ( b & ( 0x01 << ( ( i + 4 ) % 8 ) ) ) >> ( ( i + 4 ) % 8 ) );
		bit ^= ( ( b & ( 0x01 << ( ( i + 5 ) % 8 ) ) ) >> ( ( i + 5 ) % 8 ) );
		bit ^= ( ( b & ( 0x01 << ( ( i + 6 ) % 8 ) ) ) >> ( ( i + 6 ) % 8 ) );
		bit ^= ( ( b & ( 0x01 << ( ( i + 7 ) % 8 ) ) ) >> ( ( i + 7 ) % 8 ) );
		bit ^= ( ( c & ( 0x01 <<  i  ) )  >> i );
		b_prime ^= (bit << i);
	}
	return b_prime; 
}

unsigned char modInverse(unsigned char b) {
	if (b == 0x00) return 0x00;
	if (b == 0x01) return 0x01;
	unsigned int eq[3];
	extendedEuclidean(eq, 0x11b, (unsigned int) b);
	// cout << "DEBUG EQUATION: (" << toHex(eq[0]) << ")*[m(x)] + (" << toHex(eq[1]) << ")*[" << toHex(b) << "] = [" << toHex(eq[2]) << "]" <<endl;
	return eq[1];
}

void extendedEuclidean(unsigned int eq[], unsigned int a, unsigned int b) {
	unsigned int q, r;
	xdiv(a, b, &q, &r);
	if (r == 0x01) {
		eq[0] = 0x01;
		eq[1] = q;
		eq[2] = r;
		return;
	}	
	extendedEuclidean(eq, b, r); 
	unsigned int temp = eq[1];
	eq[1] = xmult(temp, q) ^ eq[0];
	eq[0] = temp;
}

void xdiv(unsigned int num, unsigned int den, unsigned int *q, unsigned int *r){
	if (den == 0x00) {return;}
	if (den == num)  {
		*q = 0x01;
		*r = 0x00;
		return;
	}
	if (den == 0x01)  {
		*q = num;
		*r = 0x00;
		return;
	}
	*r = num;
	*q = 0x00;
	int rem_ord = get_order(*r);
	int den_ord = get_order(den);
	while (rem_ord >= den_ord) {
		int factor = rem_ord - den_ord;
		*q ^= (0x01 << factor);
		*r ^= (den << factor);
		rem_ord = get_order(*r);
	}
}

int get_order(unsigned int a){
	if (a == 0) return 0x00;
	int order = -1;
	for(int i = a; i != 0; i >>= 1) {
		order++;
	}
	return order;
}

/*
 * BEGIN REUSEABLE CODE
 */
char hexLookup[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

unsigned char xmult(unsigned char a, unsigned char b){
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

unsigned char xtime(unsigned char a) {
	unsigned char x = a << 1;
	if (a & 0x80) {
		x ^= 0x1B;
	}
	return x;
}

string toHex(unsigned char a){
	string s = "0x";
	s += hexLookup[a >>4];
	s += hexLookup[a & 0x0F];
	return s;
}
/*
 * END REUSEABLE CODE
 */