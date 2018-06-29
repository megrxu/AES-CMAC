#include "utils.h"

void print_bytes(unsigned char *buf, const size_t len) {
	for (auto i = 0; i<len; i++) {
		printf("%02x ", buf[i]);
	}
	printf("\n");
}