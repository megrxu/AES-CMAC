#include "utils.h"
#include "aes.h"
#include "cmac.h"

void print_bytes(unsigned char* buf, const size_t len)
{
    for (size_t i = 0; i < len; i++) {
        printf("%02x ", buf[i]);
    }
    printf("\n");
}

bool test()
{
    // Known Plain Text and Cipher Text
    unsigned char key[] = {
        0x00, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b,
        0x0c, 0x0d, 0x0e, 0x0f
    };

    unsigned char in[] = {
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
        0x45, 0xb9, 0x40, 0x10
    };

    // Calculate the aes-128 result
    unsigned char* enct;
    unsigned char* dect;
    enct = (unsigned char*)malloc(16);
    dect = (unsigned char*)malloc(16);
    aes_128_encrypt(in, enct, key);
    aes_128_decrypt(enct, dect, key);

    // Calculate the cmac result
    unsigned char* mact;
    mact = (unsigned char*)malloc(16);
    aes_cmac(in, mact, key);

    // Verify the aes-128 output
    bool aes_de_correct = !strncmp((char*)dect, (char*)in, 16);
    bool aes_en_correct = !strncmp((char*)enct, (char*)aes_en_out, 16);

    // Verify the aes-cmac output
    bool cmac_correct = !strncmp((char*)mact, (char*)cmac_out, 16);

    // output
    if (aes_en_correct) {
        printf("AES-128 encrypt test passed.\n");
    } else {
        printf("AES-128 encrypt test failed.\n");
    }
    if (aes_de_correct) {
        printf("AES-128 decrypt test passed.\n");
    } else {
        printf("AES-128 decrypt test failed.\n");
    }
    if (cmac_correct) {
        printf("AES-CMAC test passed.\n");
    } else {
        printf("AES-CMAC test failed.\n");
    }

    return cmac_correct && aes_en_correct && aes_de_correct;
}
