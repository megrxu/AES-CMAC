#pragma once
#define AES_BLOCK_SIZE 16
#include <openssl/evp.h>
#include <openssl/cmac.h>
#include <cstring>

// Print functions

void print_bytes(unsigned char* buf, const size_t len);

bool test();
int aes_init(unsigned char* key_data, int key_data_len, unsigned char* salt, EVP_CIPHER_CTX* e_ctx,
             EVP_CIPHER_CTX* d_ctx);

unsigned char* aes_encrypt(EVP_CIPHER_CTX* e, unsigned char* plaintext, int* len);
