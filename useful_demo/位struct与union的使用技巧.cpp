#include<iostream>

typedef unsigned int UINT32;
struct SUINT_BIT32
{
	UINT32 byte1:1;
	UINT32 byte2:1;
	UINT32 byte3:1;
	UINT32 byte4:1;
	UINT32 byte5:1;
	UINT32 byte6:1;
	UINT32 byte7:1;
	UINT32 byte8:1;
	UINT32 byte9:1;
	UINT32 byte10:1;
	UINT32 byte11:1;
	UINT32 byte12:1;
	UINT32 byte13:1;
	UINT32 byte14:1;
	UINT32 byte15:1;
	UINT32 byte16:1;
	UINT32 byte17:1;
	UINT32 byte18:1;
	UINT32 byte19:1;
	UINT32 byte20:1;
	UINT32 byte21:1;
	UINT32 byte22:1;
	UINT32 byte23:1;
	UINT32 byte24:1;
	UINT32 byte25:1;
	UINT32 byte26:1;
	UINT32 byte27:1;
	UINT32 byte28:1;
	UINT32 byte29:1;
	UINT32 byte30:1;
	UINT32 byte31:1;
	UINT32 byte32:1;
};

union UUINT_BIT32
{
	SUINT_BIT32 bits;
	UINT32 val;
};

#define BTRUE 01
#define BFALSE 00

void print_bytes(const UUINT_BIT32 &bit){
	std::cout << bit.bits.byte32 <<bit.bits.byte31 << bit.bits.byte30 << bit.bits.byte29 << " "
			<< bit.bits.byte28 <<bit.bits.byte27 << bit.bits.byte26 << bit.bits.byte25 << " "
			<< bit.bits.byte24 <<bit.bits.byte23 << bit.bits.byte22 << bit.bits.byte21 << " "
			<< bit.bits.byte20 <<bit.bits.byte19 << bit.bits.byte18 << bit.bits.byte17 << " "
			<< bit.bits.byte16 <<bit.bits.byte15 << bit.bits.byte14 << bit.bits.byte13 << " "
			<< bit.bits.byte12 <<bit.bits.byte11 << bit.bits.byte10 << bit.bits.byte9 << " "
			<< bit.bits.byte8  <<bit.bits.byte7 << bit.bits.byte6 << bit.bits.byte5 << " "
			<< bit.bits.byte4 <<bit.bits.byte3 << bit.bits.byte2 << bit.bits.byte1 << "\n";
}

int main(){
	int number;
	UUINT_BIT32 bit;
	puts("Enter a number otherwise terminate:");
	while(scanf("%d", &number) == 1){
		bit.val = number;
		std::cout << "number: " << bit.val << std::endl;
		print_bytes(bit);
		bit.bits.byte2 &= BFALSE;
		print_bytes(bit);
		puts("Enter a number otherwise terminate:");
	}
	return 0;
}