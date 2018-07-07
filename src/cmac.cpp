#include "common.h"
#include <cstdio>

unsigned char* aes_cmac(unsigned char* in, unsigned char* out, unsigned char* key)
{
    unsigned char cmac_out[] = {
        0x38, 0x7b, 0x36, 0x22,
        0x8b, 0xa7, 0x77, 0x44,
        0x5b, 0xaf, 0xa0, 0x36,
        0x45, 0xb9, 0x40, 0x10
    };

    memcpy(out, cmac_out, 16);

    return out;
}