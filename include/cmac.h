#ifndef CMAC_H
#define CMAC_H

#define const_Bsize 16

unsigned char* aes_cmac(unsigned char* in, unsigned int length, unsigned char* out, unsigned char* key);
bool verify_mac(unsigned char* in, unsigned int length, unsigned char* out, unsigned char* key);

void GenerateSubkey(unsigned char* key, unsigned char* K1, unsigned char* K2);

#endif // !CMAC_H
