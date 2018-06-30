#include "utils.h"
#include <openssl/aes.h>

void print_bytes(unsigned char* buf, const size_t len)
{
	for (auto i = 0; i < len; i++)
	{
		printf("%02x ", buf[i]);
	}
	printf("\n");
}

bool test()
{
	unsigned char key[] = {
		0x00, 0x01, 0x02, 0x03,
		0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0a, 0x0b,
		0x0c, 0x0d, 0x0e, 0x0f
	};

	unsigned char message[] = {
		0x00, 0x11, 0x22, 0x33,
		0x44, 0x55, 0x66, 0x77,
		0x88, 0x99, 0xaa, 0xbb,
		0xcc, 0xdd, 0xee, 0xff
	};

	unsigned char aes_en_out[] = {
		0x69, 0xc4, 0xe0, 0xd8,
		0x6a, 0x7b, 0x04, 0x30,
		0xd8, 0xcd, 0xb7, 0x80,
		0x70, 0xb4, 0xc5, 0x5a
	};

	unsigned char cmac_out[] = {
		0x38, 0x7b, 0x36, 0x22,
		0x8b, 0xa7, 0x77, 0x44,
		0x5b, 0xaf, 0xa0, 0x36,
		0x45, 0xb9, 0x40, 0x10,
	};

	//calculate the aes-128
	unsigned char iv[AES_BLOCK_SIZE];
	memset(iv, 0x00, AES_BLOCK_SIZE);
	unsigned char enct[sizeof(message)];
	unsigned char dect[sizeof(message)];

	AES_KEY enc_key, dec_key;
	AES_set_encrypt_key(key, sizeof(key) * 8, &enc_key);
	AES_cbc_encrypt(message, enct, sizeof(key), &enc_key, iv, AES_ENCRYPT);
	memset(iv, 0x00, AES_BLOCK_SIZE);
	AES_set_decrypt_key(key, sizeof(key) * 8, &dec_key); // Size of key is in bits
	AES_cbc_encrypt(enct, dect, sizeof(message), &dec_key, iv, AES_DECRYPT);

	// calculate the cmac
	unsigned char mact[16] = {0};
	size_t mactlen;
	const auto ctx = CMAC_CTX_new();
	CMAC_Init(ctx, key, 16, EVP_aes_128_cbc(), nullptr);
	CMAC_Update(ctx, message, sizeof(message));
	CMAC_Final(ctx, mact, &mactlen);
	CMAC_CTX_free(ctx);

	// verify the aes-128 output
	const auto aes_de_correct = !strncmp(reinterpret_cast<char *>(dect), reinterpret_cast<char *>(message), 16);
	const auto aes_en_correct = !strncmp(reinterpret_cast<char *>(enct), reinterpret_cast<char *>(aes_en_out), 16);
	// verify the aes-cmac output
	const auto cmac_correct = !strncmp(reinterpret_cast<char *>(mact), reinterpret_cast<char *>(cmac_out), mactlen);

	// output
	if (aes_en_correct)
	{
		printf("AES-128 encrypt test passed.\n");
	}
	else
	{
		printf("AES-128 encrypt test failed.\n");
	}
	if (aes_de_correct)
	{
		printf("AES-128 decrypt test passed.\n");
	}
	else
	{
		printf("AES-128 decrypt test failed.\n");
	}
	if (cmac_correct)
	{
		printf("AES-CMAC test passed.\n");
	}
	else
	{
		printf("AES-CMAC test failed.\n");
	}

	return cmac_correct && aes_en_correct && aes_de_correct;
}
