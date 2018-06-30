#include "utils.h"
#include "cmac.h"

int main(int argc, char* argv[])
{
	test();
	unsigned char key[] = {
		0x2b, 0x7e, 0x15, 0x16,
		0x28, 0xae, 0xd2, 0xa6,
		0xab, 0xf7, 0x15, 0x88,
		0x09, 0xcf, 0x4f, 0x3c
	};
	print_bytes(key, 16);

	// CTX ctx((unsigned char*)key);
	// print_bytes(ctx.key, 16);

	return 0;
}
