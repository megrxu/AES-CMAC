#include <cstdio>
#include <openssl/cmac.h>
#include "utils.h"

int main(int argc, char *argv[])
{
	// K, M and T from 
	// D.1 AES-128
	// K: 2b7e1516 28aed2a6 abf71588 09cf4f3c
	unsigned char key[] = { 0x2b,0x7e,0x15,0x16,
		0x28,0xae,0xd2,0xa6,
		0xab,0xf7,0x15,0x88,
		0x09,0xcf,0x4f,0x3c };

	// M: 6bc1bee2 2e409f96 e93d7e11 7393172a Mlen: 128
	unsigned char message[] = { 0x6b,0xc1,0xbe,0xe2,
		0x2e,0x40,0x9f,0x96,
		0xe9,0x3d,0x7e,0x11,
		0x73,0x93,0x17,0x2a };

	unsigned char mact[16] = { 0 };
	size_t mactlen;

	const auto ctx = CMAC_CTX_new();
	CMAC_Init(ctx, key, 16, EVP_aes_128_cbc(), nullptr);
	printf("message length = %lu bytes (%lu bits)\n", sizeof(message), sizeof(message) * 8);

	CMAC_Update(ctx, message, sizeof(message));
	CMAC_Final(ctx, mact, &mactlen);

	print_bytes(mact, mactlen);
	/* expected result T = 070a16b4 6b4d4144 f79bdd9d d04a287c */

	CMAC_CTX_free(ctx);
	return 0;
}