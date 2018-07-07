#include "aes.h"
#include "cmac.h"
#include "utils.h"

int main(int argc, char* argv[])
{
    test();
    unsigned char key[] = {
        0x2b, 0x7e, 0x15, 0x16,
        0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x15, 0x88,
        0x09, 0xcf, 0x4f, 0x3c
    };

    unsigned char in[] = {
        0x32, 0x43, 0xf6, 0xa8,
        0x88, 0x5a, 0x30, 0x8d,
        0x31, 0x31, 0x98, 0xa2,
        0xe0, 0x37, 0x07, 0x34
    };

    unsigned char* out = (unsigned char*)malloc(16);
    print_bytes(in, 16);
    aes_128_encrypt(in, out, key);
    print_bytes(out, 16);
    aes_128_decrypt(out, out, key);
    print_bytes(out, 16);

    return 0;
}
