#include "utils.h"
#include "aes.h"
#include "cmac.h"
#include <cstring>
#include <cstdio>


CTX::CTX(unsigned char*key)
{
	strncpy((char*)this->key, (char*)key, 16);
	generate_subkey();
}

CTX::~CTX()
{
	
}

void CTX::generate_subkey()
{
	const char const_Zero[] = {
		0x00, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x00};
	unsigned char const_Rb[] = {
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x87 };

	// auto L = aes_128(this->key, (unsigned char*)const_Zero);

	// if(L[0] < 0x70)
	// {
	// 	this->key_1 = L << 1;
	// }else
	// {
	// 	this->key_1 = (L << 1) ^ (const_Rb);
	// }
 //
	// if (this->key_1 < 0x70)
	// {
	// 	this->key_2 = this->key_1 << 1;
	// }
	// else
	// {
	// 	this->key_2 = (this->key_1 << 1) ^ (const_Rb);
	// }
}
