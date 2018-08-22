#include "aes.h"
#include "cmac.h"
#include "encrypt.h"
#include "utils.h"

#define ACCENTCOLOR "\033[1;36m"
#define DEFAULT "\033[0m"

void perform(char* argv[]);
void run(char* argv[]);

int main(int argc, char* argv[])
{
    if (argc == 1) {
        printf("\033[1;35m");
        printf("TEST CASES\n");
        printf("\033[0m");
        test();
        printf("\n");
        run(argv);
    } else if (argc == 3) {
        perform(argv);
    } else {
        printf("Usage: %s MESSAGE KEY\n", argv[0]);
    }

    return 0;
}

void run(char* argv[])
{
    unsigned char key[] = {
        0x31, 0x50, 0x10, 0x47,
        0x17, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };

    unsigned char message[] = {
        "Information Security is a multidisciplinary area of study and professional activity which is concerned with the development and implementation of security mechanisms of all available types (technical, organizational, human-oriented and legal) to keep information in all its locations (within and outside the organization's perimeter) and, consequently, information systems, where information is created, processed, stored, transmitted and destroyed, free from threats. This project is finished by GUORUI XU."
    };

    unsigned char out[16];

    printf("%sInput message%s\n", ACCENTCOLOR, DEFAULT);
    printf("\"%s\"\n", message);
    printf("%sKey%s\n", ACCENTCOLOR, DEFAULT);
    print_bytes(key, 16);
    aes_cmac(message, strlen((char*)message) + 1, (unsigned char*)out, key);
    printf("%sAES-128-CMAC Result%s\n", ACCENTCOLOR, DEFAULT);
    print_bytes(out, 16);

    unsigned int n = 0;
    unsigned char* C;

    C = ecb_encrypt(message, key, aes_128_encrypt, &n);
    printf("%sAES-128-ECB Encrypt Result%s\n", ACCENTCOLOR, DEFAULT);
    for (auto i = 0; i < n; i++) {
        print_bytes(C + i * 16, 16);
    }

    C = ecb_decrypt(C, key, aes_128_decrypt, &n);
    printf("%sAES-128-ECB Decrypt Result%s\n", ACCENTCOLOR, DEFAULT);
    printf("\"%s\"\n", C);

    printf("\nUsage: %s MESSAGE KEY\n", argv[0]);
}

void perform(char* argv[])
{
    printf("%sInput message%s\n", ACCENTCOLOR, DEFAULT);
    printf("\"%s\"\n", argv[1]);
    unsigned char key[16];
    unsigned char out[16];
    memset(out, 0x00, 16);
    memset(key, 0x00, 16);
    if (strlen(argv[2]) > 16) {
        memcpy(key, argv[2], 16);
    } else {
        memcpy(key, argv[2], strlen(argv[2]));
    }
    printf("%sKey%s\n", ACCENTCOLOR, DEFAULT);
    print_bytes(key, 16);
    aes_cmac((unsigned char*)(argv[1]), strlen(argv[1]) + 1, (unsigned char*)out, key);
    printf("%sAES-128-CMAC Result%s\n", ACCENTCOLOR, DEFAULT);
    print_bytes(out, 16);

    unsigned int n = 0;
    unsigned char* C;

    C = ecb_encrypt((unsigned char*)argv[1], (unsigned char*)argv[2], aes_128_encrypt, &n);
    printf("%sAES-128-ECB Encrypt Result%s\n", ACCENTCOLOR, DEFAULT);
    for (auto i = 0; i < n; i++) {
        print_bytes(C + i * 16, 16);
    }

    C = ecb_decrypt(C, (unsigned char*)argv[2], aes_128_decrypt, &n);
    printf("%sAES-128-ECB Decrypt Result%s\n", ACCENTCOLOR, DEFAULT);
    printf("\"%s\"", C);
}
